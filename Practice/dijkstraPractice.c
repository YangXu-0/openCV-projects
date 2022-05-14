#include <stdio.h>
#include <stdlib.h>

typedef struct Enode {
    char *station_name;
    int weight;
    struct Enode *next;
} Enode;


typedef struct Vnode {
    char *station_name;
    Enode *edges;
    int visited;
    int cost;
    struct Vnode *prev;
} Vnode;


typedef struct Graph {
    Vnode **stations;
    int count;
} Graph;


int main(void) {

    return 0;
}