#include <stdio.h>
#include <stdlib.h>


void initArray(int ** a, int n) {
    *a = (int *)calloc(n, sizeof(int));

    /*
    *a = (int *)malloc(n*sizeof(int));
    for (int i = 0; i<n; i++) {
        *a[i] = 0;
    }
    */
}


int factorial(int n) {
    if (n == 1) {
        return 1;
    }

    return (n * factorial(n-1));
}


int iIsPalindrome(int *a, int n) {
    for (int i = 0; i<(n/2); i++) {
        if (a[i] != a[n-1-i]) {
            return 0;
        }
    }
    return 1;
}


int rFindMin(int *a, int i, int n, int *index) {
    if (n == i) {
        *index = i;
        return a[i];
    }

    int smallest = rFindMin(a, i+1, n, index);
    if (a[i] < smallest) {
        *index = i;
        return a[i];
    }
    else {
        return smallest;
    }
}

/*
void pop(struct Stack * s, struct Data * d) {
    struct Queue * empty;
    struct Queue * full;

    if (s->count == 0) {
        d->data = -1;
        return;
    }

    if (isEmpty(s->q1)) {
        empty = s->q1;
        full = s->q2;
    }
    else {
        empty = s->q2;
        full = s->q1;
    }

    for (int i = 0; i<(s->count)-1; i++) {
        dequeue(full, d);
        enqueue(empty, *d);
    }

    dequeue(full);  
    s->count -= 1;

    return;
}

*/


int main() {
    /*
    int *a;
    initArray(&a, 5);
    for (int i = 0; i<5; i++) {
        printf("%d\n", a[i]);
    }
    free(a);
    printf("%d", a[0]);
    */

    /*
    int fact = factorial(4);
    printf("%d\n", fact);
    */

    int test[] = { 5, 4, 7, 1, 3 };
    int index;
    int smallest = rFindMin(test, 0, 4, &index);
    printf("The smallest int is %d found at index %d", smallest, index);

    return 0;
}