#include "test.h"

int fib(int n) {
    if (n == 1) {
        return 1;
    }
    if (n == 0) {
        return 0;
    }

    return (fib(n-2) + fib(n-1));
}


int **initStructure(int r, int *a) {
    int **pt = (int **)malloc(r*sizeof(int*));
    for (int i = 0; i<r; i++) {
        pt[i] = (int *)calloc(a[i], sizeof(int));
    }
    return pt;
}


void print_and_free_structure(int   **stc) {
    int c[] = {3,4,2};
    int **s = initStructure(3, c);
    for (int i = 0; i<3; i++) {
        for (int j = 0; j<*(c+i); j++) {
            printf("%d ", *(*(s+i)+j));
        }
        printf("\n");
    }

    for (int i = 0; i<3; i++) {
        free(*(s+i));
    }
    free(s);
}


int findLargestSumBad(int * array, int n, int *a, int *b) {
    // go through array, add for all positive chains
    // if negative or end, store current as perma and reset current
    // start again at next positive
    // if next chain is larger, change perma
    // if all neg, return smallest neg

    int max_sum = 0;
    int max_index_start;
    int max_index_end;

    int cur_sum = 0;
    int cur_index_start = -1;
    int cur_index_end = -1;

    int smallest_neg;
    int smallest_neg_index;
    
    for (int i = 0; i<n; i++) {
        if (array[i] < 0) {
            
            if (cur_sum > max_sum) {
                max_sum = cur_sum;
                max_index_start = cur_index_start;
                max_index_end = cur_index_end;
            }

            cur_sum = 0;
            cur_index_start = -1;
            cur_index_end = -1;

            if (smallest_neg < array[i]) {
                smallest_neg = array[i];
                smallest_neg_index = i;
            }
        }
        else {
            if (cur_index_start == -1) {
                cur_index_start = i;
                cur_index_end = i;
            }
            else {
                cur_index_end += 1;
            }

            cur_sum += array[i];
        }
    }

    if (cur_sum > max_sum) {
        max_sum = cur_sum;
        max_index_start = cur_index_start;
        max_index_end = cur_index_end;
    }

    if (max_sum > smallest_neg) {
        *a = max_index_start;
        *b = max_index_end;
        return max_sum;
    }
    else {
        *a = smallest_neg_index;
        *b = smallest_neg_index;
        return smallest_neg;
    }

}

int findLargestSum(int * array, int n, int *a, int *b) {
    int max_sum = 0;
    int max_index;
}

int main() {
    int a;
    int b;
    int test_arr[] = { -2, -3, 4, -1, -2, 1, 5, -3 };
    int test = findLargestSum(test_arr, 8, &a, &b);
    printf("The max sum is: %d\n", test);
    printf("The subarray is from %d to %d\n", a, b);

    return 0;
}