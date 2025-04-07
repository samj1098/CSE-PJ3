#ifndef GRAPH_H
#define GRAPH_H

#include "data_structures.h"
#include "heap.h"
#include "stack.h"

void readGraph(const char* filename, const char* graphType, int flag);
void printAdj();
void dijkstra(int source, int destination);
void printPath(int s, int t);
void printLength(int s, int t);

#endif
