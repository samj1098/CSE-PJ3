#include "stack.h"
#include <cstdlib>
#include <iostream>

using namespace std;

pSTACK createStack(int capacity) {
	pSTACK stack = (pSTACK)malloc(sizeof(STACK));
	stack->top = -1;
	stack ->capacity = capacity;
	stack->items = (pVERTEX*)malloc(capacity * sizeof(pVERTEX));
	return stack;
}

void push(pSTACK stack, pVERTEX vertex) {
	if(stack->top >= stack->capacity - 1) {
		cerr << "Stack overflow: can't push onto full stack." << endl;
		return;
	}
	stack->items[++stack->top] = vertex;
}

pVERTEX pop(pSTACK stack) {
	if(stack->top == -1) {
		cerr << "Stack underflow: can't pop from empty stack." << endl;
		return nullptr;
	}
	return stack->items[stack->top--];
}

bool isEmpty(pSTACK stack) {
	return (stack->top == -1);
}

void destroyStack(pSTACK stack) {
	free(stack->items);
	free(stack);
}
