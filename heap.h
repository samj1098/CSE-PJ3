#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"

typedef VERTEX ELEMENT;
typedef ELEMENT* pELEMENT;

typedef struct TAG_HEAP {
    int capacity;
    int size;
    int* H;
} HEAP;

typedef HEAP* pHEAP;

pHEAP createHeap(int capacity);
void destroyHeap(pHEAP heap);
void Heapify(pHEAP heap, ELEMENT** V, int i);
void BuildHeap(pHEAP heap, ELEMENT** V, int n);
void Insert(pHEAP heap, ELEMENT** V, int index);
ELEMENT* ExtractMin(pHEAP heap, ELEMENT** V);
void DecreaseKey(pHEAP heap, ELEMENT** V, int index, double newKey);
void PrintHeap(pHEAP heap);
void PrintArray(ELEMENT** V, int n);

#endif
