#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) {
        key = k;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class AVL {
private:
    Node* root;

    int height(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int balanceFactor(Node* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* insertNode(Node* node, int key) {
        if (!node)
            return new Node(key);

        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = balanceFactor(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* node, int key) {
        if (!node)
            return node;

        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            else if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = balanceFactor(node);

        if (balance > 1 && balanceFactor(node->left) >= 0)
            return rightRotate(node);
        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && balanceFactor(node->right) <= 0)
            return leftRotate(node);
        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inOrderPrint(Node* node)
    {
        if (node != nullptr) {
            inOrderPrint(node->left);
            cout << node->key << " ";
            inOrderPrint(node->right);
        }
    }

    void preOrderPrint(Node* node) {
        if (node) {
            cout << node->key << " ";
            preOrderPrint(node->left);
            preOrderPrint(node->right);
        }
    }

    void postOrderPrint(Node* node)
    {
        if (node != nullptr) {
            postOrderPrint(node->left); 
            postOrderPrint(node->right);
            cout << node->key << " ";
        }
    }

    bool searchNode(Node* node, int key)
    {
        if (!node)
            return false;
        if (node->key == key)
            return true;
        if (key < node->key)
            return searchNode(node->left, key);
        else
            return searchNode(node->right, key);
    }

public:
    AVL() : root(nullptr) {}

    void insert(int key) {
        root = insertNode(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }
    
    void inOrder() {
        cout << "Inorder: ";
        inOrderPrint(root);
        cout << endl;
    }

    void preOrder() {
        cout << "Preorder: ";
        preOrderPrint(root);
        cout << endl;
    }

    void postOrder() {
        cout << "Postorder: ";
        postOrderPrint(root);
        cout << endl;
    }

    bool search(int key) {
        return searchNode(root,key);
    }

};

int main() {
    AVL tree;
    cout << "--- AVL TREE ---\n";
    tree.insert(33);
    tree.insert(13);
    tree.insert(56);
    tree.insert(10);
    tree.insert(23);
    tree.insert(43);
    tree.insert(61);
    tree.insert(5);

    tree.inOrder();
    tree.preOrder();
    tree.postOrder();
    
    tree.remove(13);
    cout << "--- After deleting 13 ---\n";
    tree.inOrder();
    tree.preOrder();
    tree.postOrder();
    
    tree.insert(11);
    cout << "--- After inserting 11 ---\n";
    tree.inOrder();
    tree.preOrder();
    tree.postOrder();
    
    cout << "--- Search ---\n";
    
    if (tree.search(33))
        cout << "33 is in the tree\n";
    else
        cout << "33 is NOT in the tree\n";
    
    if (tree.search(15))
        cout << "15 is in the tree\n";
    else
        cout << "15 is NOT in the tree\n";
    return 0;
}