#include <stdio.h>
#include <stdlib.h>

void print_spaces(int num);
void print_bt(bin_tree *bt);
void remove_min(bin_tree *bt);
void swap_up(bin_tree *bt, int cindex);
void swap_down(bin_tree *bt, int pindex);


typedef struct bin_tree {
    int *tree;
    int size;
    int count;
} bin_tree;


bin_tree *plant_bt(int rval) {
    bin_tree *new = (bin_tree *)malloc(sizeof(bin_tree));
    new->tree = (int *)malloc(sizeof(int));
    new->tree[0] = rval;
    new->size = 1;
    new->count = 1;
    return new;
}


void insert(bin_tree *bt, int val) {
    if (bt->size == bt->count) {
        bt->tree = realloc(bt->tree, bt->size*2*sizeof(int));
        bt->size *= 2;
    }

    bt->tree[bt->count] = val;
    swap_up(bt, bt->count);
    bt->count += 1;
}


void swap_up(bin_tree *bt, int cindex) {
    if (cindex == 0) {
        // no parent index
        return;
    }
    int pindex = (cindex - 1)/2;
    if (bt->tree[pindex] > bt->tree[cindex]) {
        int temp = bt->tree[cindex];
        bt->tree[cindex] = bt->tree[pindex];
        bt->tree[pindex] = temp;
        swap_up(bt, pindex);
    }
    return;
}


void remove_min(bin_tree *bt) {
    if (bt->count == 0) {
        return;
    }

    int min = bt->tree[0];
    bt->count -= 1;
    bt->tree[0] = bt->tree[bt->count];
    swap_down(bt, 0);
}


void swap_down(bin_tree *bt, int pindex) {
    int cindex_l = 2*pindex + 1;
    int cindex_r = 2*pindex + 2;

    if (cindex_l <= bt->count && bt->tree[cindex_l] < bt->tree[pindex]) {
        int temp = bt->tree[pindex];
        bt->tree[pindex] = bt->tree[cindex_l];
        bt->tree[cindex_l] = temp;
        swap_down(bt, cindex_l);
    }
    else if (cindex_r <= bt->count && bt->tree[cindex_r] < bt->tree[pindex]) {
        int temp = bt->tree[pindex];
        bt->tree[pindex] = bt->tree[cindex_r];
        bt->tree[cindex_r] = temp;
        swap_down(bt, cindex_r);
    }

    return;
}


void free_bt(bin_tree *bt) {
    free(bt->tree);
    free(bt);
}


void heapify(bin_tree *bt) {
    for (int i = bt->count-1; i >= 0; i--) {
        swap_down(bt, i);
    }
}

int main(void) {

    return 0;