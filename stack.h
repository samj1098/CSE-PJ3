#ifndef STACK_H
#define STACK_H

#include "data_structures.h"

typedef struct TAG_STACK {
    int top;
    int capacity;
    pVERTEX* items;
} STACK;

typedef STACK* pSTACK;

pSTACK createStack(int capacity);
void push(pSTACK stack, pVERTEX vertex);
pVERTEX pop(pSTACK stack);
bool isEmpty(pSTACK stack);
void destroyStack(pSTACK stack);

#endif
