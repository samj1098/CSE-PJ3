#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef enum {WHITE, GRAY, BLACK} COLOR;

typedef struct TAG_VERTEX{
int index;
COLOR color;
double key;
int pi;
int position;
}VERTEX;

typedef VERTEX *pVERTEX;

typedef struct TAG_NODE{
int index;
int u;
int v;
double w;
TAG_NODE *next;
}NODE;

typedef NODE *pNODE;

#endif

