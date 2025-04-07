#include "graph.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cfloat>
#include <iomanip>

using namespace std;

int n, m;
pVERTEX* V = nullptr;
pNODE* ADJ = nullptr;
bool isDirected = true;

void readGraph(const char* filename, const char* graphType, int flag) {
    FILE* fp = fopen(filename, "r");
    if (fp == nullptr) {
        cerr << "Error: Cannot open file " << filename << endl;
        exit(1);
    }

    isDirected = strcmp(graphType, "DirectedGraph") == 0;

    fscanf(fp, "%d %d", &n, &m);

    V = (pVERTEX*) calloc(n + 1, sizeof(pVERTEX));
    ADJ = (pNODE*) calloc(n + 1, sizeof(pNODE));

    for (int i = 1; i <= n; i++) {
        V[i] = (pVERTEX) calloc(1, sizeof(VERTEX));
        V[i]->index = i;
        V[i]->key = DBL_MAX;
        V[i]->pi = -1;
        V[i]->position = 0;
        V[i]->color = WHITE;
    }

    for (int i = 0; i < m; i++) {
        int edgeIndex, u, v;
        double w;
        fscanf(fp, "%d %d %d %lf", &edgeIndex, &u, &v, &w);

        // Insert u → v at the front of ADJ[u]
        pNODE nodeUV = (pNODE) malloc(sizeof(NODE));
        nodeUV->index = edgeIndex;
        nodeUV->u = u;
        nodeUV->v = v;
        nodeUV->w = w;
        nodeUV->next = ADJ[u];
        ADJ[u] = nodeUV;

        // For undirected graphs, also insert v → u at front of ADJ[v]
        if (!isDirected) {
            pNODE nodeVU = (pNODE) malloc(sizeof(NODE));
            nodeVU->index = edgeIndex;
            nodeVU->u = v;
            nodeVU->v = u;
            nodeVU->w = w;
            nodeVU->next = ADJ[v];
            ADJ[v] = nodeVU;
        }
    }

    fclose(fp);
}

void printAdj() {
    for (int i = 1; i <= n; i++) {
        cout << "ADJ[" << i << "]:";
        pNODE curr = ADJ[i];
        while (curr != nullptr) {
            printf("-->[%d %d: %4.2lf]", curr->index, curr->v, curr->w);
            curr = curr->next;
        }
        cout << endl;
    }
}

void dijkstra(int source, int destination) {
    for (int i = 1; i <= n; i++) {
        V[i]->key = DBL_MAX;
        V[i]->pi = -1;
        V[i]->color = WHITE;
        V[i]->position = 0;
    }

    pHEAP heap = createHeap(n);
    V[source]->key = 0.0;
    V[source]->color = GRAY;
    Insert(heap, V, source);

    while (heap->size > 0) {
        pVERTEX u = ExtractMin(heap, V);
        u->color = BLACK;

        if (u->index == destination && destination != -1) break;

        pNODE neighbor = ADJ[u->index];
        while (neighbor != nullptr) {
            int vIndex = neighbor->v;
            pVERTEX v = V[vIndex];
            double newKey = u->key + neighbor->w;

            if (v->color == WHITE) {
                v->key = newKey;
                v->pi = u->index;
                v->color = GRAY;
                Insert(heap, V, vIndex);
            } else if (v->color == GRAY && newKey < v->key && v->position != 0) {
                v->key = newKey;
                v->pi = u->index;
                DecreaseKey(heap, V, vIndex, newKey);
            }

            neighbor = neighbor->next;
        }
    }

    destroyHeap(heap);
}

void printPath(int s, int t) {
    if (V[t]->pi == -1 || V[t]->key == DBL_MAX) {
        cout << "There is no path from " << s << " to " << t << "." << endl;
        return;
    }

    pSTACK stack = createStack(n);
    int current = t;

    while (current != -1) {
        push(stack, V[current]);
        current = V[current]->pi;
    }

    cout << "The shortest path from " << s << " to " << t << " is:" << endl;

    while (!isEmpty(stack)) {
        pVERTEX v = pop(stack);
        cout << "[" << v->index << ":" << fixed << setprecision(2) << setw(8) << v->key << "]";
        if (!isEmpty(stack)) cout << "-->";
    }

    cout << "." << endl;
    destroyStack(stack);
}

void printLength(int s, int t) {
    if (V[t]->pi == -1 || V[t]->key == DBL_MAX) {
        cout << "There is no path from " << s << " to " << t << "." << endl;
    } else {
        cout << "The length of the shortest path from " << s << " to " << t << " is: ";
        printf("%8.2lf\n", V[t]->key);
    }
}
