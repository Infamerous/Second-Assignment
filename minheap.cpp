#include <iostream>
using namespace std;

class Node {
private:
    int iData;
public:
    Node(int key) {
        iData = key;
    }
    int getKey() {
        return iData;
    }
    void setKey(int id) {
        iData = id;
    }
};

class Heap {
private:
    Node** heapArray;
    int maxSize;
    int currentSize;

public:
    Heap(int mx) {
        maxSize = mx;
        currentSize = 0;
        heapArray = new Node*[maxSize + 1];
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    bool isFull() {
        return currentSize == maxSize;
    }

    bool insert(int key) {
        if (isFull()) {
            return false;
        }
        Node* newNode = new Node(key);
        heapArray[++currentSize] = newNode;
        trickleUp(currentSize);
        return true;
    }

    void trickleUp(int index) {
        int parent = index / 2;
        Node* bottom = heapArray[index];

        while (index > 1 && heapArray[parent]->getKey() > bottom->getKey()) {
            heapArray[index] = heapArray[parent];
            index = parent;
            parent = parent / 2;
        }
        heapArray[index] = bottom;
    }

    Node* remove() {
        if (isEmpty()) {
            return NULL;
        }
        Node* root = heapArray[1];
        heapArray[1] = heapArray[currentSize--];
        trickleDown(1);
        return root;
    }

    void trickleDown(int index) {
        int smallerChild;
        Node* top = heapArray[index];

        while (index <= currentSize / 2) {
            int leftChild = 2 * index;
            int rightChild = leftChild + 1;

            if (rightChild <= currentSize && heapArray[leftChild]->getKey() > heapArray[rightChild]->getKey()) {
                smallerChild = rightChild;
            } else {
                smallerChild = leftChild;
            }

            if (top->getKey() <= heapArray[smallerChild]->getKey()) {
                break;
            }

            heapArray[index] = heapArray[smallerChild];
            index = smallerChild;
        }
        heapArray[index] = top;
    }

    void displayHeap() {
        for (int i = 1; i <= currentSize; ++i) {
            cout << heapArray[i]->getKey() << " ";
        }
        cout << endl;
    }

    void heapSort(bool decreasing = false) {
        Heap tempHeap(maxSize);
        for (int i = 1; i <= currentSize; i++) {
            tempHeap.insert(heapArray[i]->getKey());
        }
    
        int size = tempHeap.currentSize;
        int* sortedArr = new int[size];
    
        for (int i = 0; i < size; i++) {
            sortedArr[i] = tempHeap.remove()->getKey(); 
        }
    
        if (decreasing) {
            cout << "Heap Sort in decreasing order: ";
            for (int i = size - 1; i >= 0; i--) {
                cout << sortedArr[i] << " ";
            }
        }
        else {
            cout << "Heap Sort in increasing order: ";
            for (int i = 0; i < size; i++) {
                cout << sortedArr[i] << " ";
            }
        }
    }
    
    void PriorityQueue() {
        Heap tempHeap(maxSize);
        for (int i = 1; i <= currentSize; i++) {
            tempHeap.insert(heapArray[i]->getKey());
        }
        while (!tempHeap.isEmpty()) {
            cout << tempHeap.remove()->getKey() << " ";
        }
        cout << endl;
    }

};

int main() {
    int arr[] = {12, 3, 5, 7, 19, 1, 8, 15, 4, 11, 6, 9, 14};

    cout << "Initial Array: ";
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    Heap heap(20);

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i) {
        heap.insert(arr[i]);
    }

    cout << "Min Heap: ";
    heap.displayHeap();

    heap.insert(2);
    cout << "Min Heap after inserting 2: ";
    heap.displayHeap();

    heap.heapSort(false); //decreasing
    cout << endl;
    heap.heapSort(true); //increasing
    cout << endl;
    
    cout << "Priority Queue 1: ";
    heap.PriorityQueue();
    
    heap.remove();
    cout << "Min-heap after the delete section: "; //smallest number 1 is gone
    heap.displayHeap();
    
    cout << "Priority Queue 2: ";
    heap.PriorityQueue();
    cout << endl;
    
    return 0;
}
