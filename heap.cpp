#include "heap.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

pHEAP createHeap(int capacity) {
    pHEAP heap = (pHEAP)malloc(sizeof(HEAP));
    heap->capacity = capacity;
    heap->size = 0;
    heap->H = (int*)malloc((capacity + 1) * sizeof(int));
    return heap;
}

void destroyHeap(pHEAP heap) {
    if (heap != nullptr) {
        free(heap->H);
        free(heap);
    }
}

void Heapify(pHEAP heap, ELEMENT** V, int i) {
    int smallest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left <= heap->size && V[heap->H[left]]->key < V[heap->H[smallest]]->key)
        smallest = left;

    if (right <= heap->size && V[heap->H[right]]->key < V[heap->H[smallest]]->key)
        smallest = right;

    if (smallest != i) {
        swap(heap->H[i], heap->H[smallest]);
        V[heap->H[i]]->position = i;
        V[heap->H[smallest]]->position = smallest;
        Heapify(heap, V, smallest);
    }
}

void BuildHeap(pHEAP heap, ELEMENT** V, int n) {
    heap->size = n;
    for (int i = 1; i <= n; i++) {
        heap->H[i] = i;
        V[i]->position = i;
    }

    for (int i = n / 2; i >= 1; i--) {
        Heapify(heap, V, i);
    }
}

void Insert(pHEAP heap, ELEMENT** V, int index) {
    if (V[index]->position != 0) {
        cerr << "Error: V[" << index << "] already in the heap" << endl;
        return;
    }

    heap->size++;
    int i = heap->size;
    heap->H[i] = index;
    V[index]->position = i;

    while (i > 1 && V[heap->H[i]]->key < V[heap->H[i / 2]]->key) {
        swap(heap->H[i], heap->H[i / 2]);
        V[heap->H[i]]->position = i;
        V[heap->H[i / 2]]->position = i / 2;
        i /= 2;
    }
}

ELEMENT* ExtractMin(pHEAP heap, ELEMENT** V) {
    if (heap == nullptr || heap->size == 0) {
        cerr << "Error: heap is empty or null" << endl;
        return nullptr;
    }

    int minIndex = heap->H[1];
    ELEMENT* minElement = V[minIndex];
    minElement->position = 0;

    heap->H[1] = heap->H[heap->size];
    V[heap->H[1]]->position = 1;

    heap->size--;

    if (heap->size > 0) {
        Heapify(heap, V, 1);
    }

    return minElement;
}

void DecreaseKey(pHEAP heap, ELEMENT** V, int index, double newKey) {
    if (V[index]->position == 0 || V[index]->key <= newKey) {
        cerr << "Error: invalid call to decreaseKey" << endl;
        return;
    }

    V[index]->key = newKey;
    int i = V[index]->position;

    while (i > 1 && V[heap->H[i]]->key < V[heap->H[i / 2]]->key) {
        swap(heap->H[i], heap->H[i / 2]);
        V[heap->H[i]]->position = i;
        V[heap->H[i / 2]]->position = i / 2;
        i /= 2;
    }
}

void PrintHeap(pHEAP heap) {
    if (heap == nullptr) {
        cerr << "Error: heap is NULL" << endl;
        return;
    }

    cout << "Capacity = " << heap->capacity << ", size = " << heap->size << endl;

    for (int i = 1; i <= heap->size; i++) {
        cout << "H[" << i << "] = " << heap->H[i] << endl;
    }
}

void PrintArray(ELEMENT** V, int n) {
    if (V == nullptr) {
        cerr << "Error: array is NULL" << endl;
        return;
    }

    for (int i = 1; i <= n; i++) {
        cout << i << " " << fixed << setprecision(6) << V[i]->key << " " << V[i]->position << endl;
    }
}
