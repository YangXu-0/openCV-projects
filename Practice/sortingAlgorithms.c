#include <stdio.h>
#include <stdlib.h>

// Prototypes
void print_arr(int *arr, int n);
int* merge(int *arr_1, int *arr_2, int n_1, int n_2);
int partition(int **arr, int low, int high);

// ######################## Sorting Algs. ########################
void insertion_sort(int *arr, int n) {
    // 3, 5, 8, 
    int leading_index = 0;
    for (int i = 1; i<n; i++) {
        if (arr[i] < arr[leading_index]) {
            int loc = i;
            for (int j = leading_index; j>= 0; j--) {
                if (arr[loc] < arr[j]) {
                    int temp = arr[loc];
                    arr[loc] = arr[j];
                    arr[j] = temp;
                    loc--;
                }
                else {
                    break;
                }
            }
        }
        leading_index += 1;
    }

    return;
}


void selection_sort(int *arr, int n) {
    for (int i = 0; i<n; i++) {
        int smallest_index = i;
        for (int j = i; j<n; j++) {
            if (arr[j] < arr[smallest_index]) {
                smallest_index = j;
            }
        }
        int temp = arr[smallest_index];
        arr[smallest_index] = arr[i];
        arr[i] = temp;
    }

    return;
}


void bubble_sort(int *arr, int n) {

    int n_copy = n;
    for (int i = 0; i<n; i++) {
        int flag = -1;
        for (int j = 0; j<(n_copy-1); j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                flag = 0;
            }
        }
        n_copy--;
        if (flag == -1) {
            break;
        }
    }
    
    return;
}


void merge_sort(int **arr, int n) {

    if (n == 1) {
        return;
    }

    int half = n/2;
    int *left_half = (int *)malloc(half*sizeof(int));
    int *right_half = (int *)malloc((n-half)*sizeof(int));

    int j = 0;
    for (int i = 0; i<n; i++) {
        if (i<half) {
            left_half[i] = (*arr)[i];
        }
        else {
            right_half[j] = (*arr)[i];
            j++;
        }
    }

    merge_sort(&left_half, half);
    merge_sort(&right_half, n-half);

    free(*arr);
    *arr = merge(left_half, right_half, half, n-half);

    return;
}

int* merge(int *arr_1, int *arr_2, int n_1, int n_2) {
    int *merged_arr = (int *)malloc((n_1 + n_2)*sizeof(int));

    int i = 0;
    int j = 0;
    int k = 0;
    while (i < n_1 && j < n_2) {
        if (arr_1[i] < arr_2[j]) {
            merged_arr[k] = arr_1[i];
            i++;
            k++;
        }
        else {
            merged_arr[k] = arr_2[j];
            j++;
            k++;
        }
    }
    
    for (i = i; i < n_1; i++) {
        merged_arr[k] = arr_1[i];
        k++;
    }
    for (j = j; j < n_2; j++) {
        merged_arr[k] = arr_2[j];
        k++;
    }

    free(arr_1);
    free(arr_2);

    return merged_arr;
}


void quick_sort_bad(int **arr, int a, int b) {
    if (b-a <= 1) {
        if (((*arr)[b] > (*arr)[a]) && b >= 0 && a >= 0) {
            int temp = (*arr)[b];
            (*arr)[b] = (*arr)[a];
            (*arr)[a] = temp;
            printf("end %d %d arr_b:%d arr_a:%d ", a, b, (*arr)[b], (*arr)[a]);
            print_arr(*arr, b+1);
        }

        return;
    }

    int i = a;
    int j = b-1;
    int flag_i = 0;
    int flag_j = 0;
    int pivot_index = b; // right-most element
    printf("The pivot is %d. a:%d j:%d i:%d b:%d ", (*arr)[pivot_index], a, j, i, b);
    print_arr(*arr, b+1);
    while (i <= j) {
        if ((*arr)[i] < (*arr)[pivot_index]) {
            i++;
        }
        else {
            flag_i = -1;
        }
        if ((*arr)[j] >= (*arr)[pivot_index]) {
            j--;
        }
        else {
            flag_j = -1;
        }

        if (flag_j*flag_i == 1) {
            int temp = (*arr)[j];
            (*arr)[j] = (*arr)[i];
            (*arr)[i] = temp;
            flag_i = 0;
            flag_j = 0;
        }
    }
    int temp = (*arr)[pivot_index];
    (*arr)[pivot_index] = (*arr)[i];
    (*arr)[i] = temp;

    print_arr(*arr, b+1);
    printf("a:%d j:%d i:%d b:%d\n", a, j, i, b);
    quick_sort_bad(arr, a, j);
    quick_sort_bad(arr, i, b);

    return;
}


void quick_sort(int **arr, int low, int high) {
    if (low < high) {
        int pt = partition(arr, low, high);

        quick_sort(arr, low, pt-1);
        quick_sort(arr, pt+1, high);
    }

    return;
}

int partition(int **arr, int low, int high) {
    int pivot = high;

    int i = low - 1;
    for (int j = low; j<(high); j++) {
        if ((*arr)[j] < (*arr)[pivot]) {
            i++;
            int temp = (*arr)[j];
            (*arr)[j] = (*arr)[i];
            (*arr)[i] = temp;
        }
    }

    int temp = (*arr)[pivot];
    (*arr)[pivot] = (*arr)[i+1];
    (*arr)[i+1] = temp;

    return i+1;
}


// ######################## Testing Code ########################
void print_arr(int *arr, int n) {
    printf("The array is currently: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return;
}


void verify_sort(int *arr, void (*f)(int*, int)) {

    int num_checks = 50;
    int size = 20;

    for (int i = 0; i<num_checks; i++) {
        int *test = (int *)malloc(size*sizeof(int));
        int *test_org = (int *)malloc(size*sizeof(int));
        for (int j = 0; j<size; j++) {
            int rand_num = (int) (rand() % 100);
            test[j] = rand_num;
            test_org[j] = rand_num;
        }
        f(test, size);
        for (int j = 1; j<size; j++) {
            if (test[j] < test[j-1]) {
                printf("Sorting Error.\nThe original array is:\n");
                print_arr(test_org, size);
                printf("The \"sorted\" array is:\n");
                print_arr(test, size);

                free(test);
                free(test_org);
                return;
            }
        }

        printf("Test %d passed: ", i+1);
        print_arr(test, size);
        free(test);
        free(test_org);
    }

    return;
}


void verify_sort_recursive(int *arr, void (*f)(int**, int, int)) {

    int num_checks = 50;
    int size = 20;

    for (int i = 0; i<num_checks; i++) {
        int *test = (int *)malloc(size*sizeof(int));
        int *test_org = (int *)malloc(size*sizeof(int));
        for (int j = 0; j<size; j++) {
            int rand_num = (int) (rand() % 100);
            test[j] = rand_num;
            test_org[j] = rand_num;
        }
        print_arr(test, size);
        f(&test, 0, size-1);
        printf("ran");
        for (int j = 1; j<size; j++) {
            if (test[j] < test[j-1]) {
                printf("Sorting Error.\nThe original array is:\n");
                print_arr(test_org, size);
                printf("The \"sorted\" array is:\n");
                print_arr(test, size);

                free(test);
                free(test_org);
                return;
            }
        }

        printf("Test %d passed: ", i+1);
        print_arr(test, size);
        free(test);
        free(test_org);
    }

    return;
}


int main() {

    // Goal: sort list from low to high

    // Setup

    /* Static array test
    int test[] = { 6, 5, 4, 3, 2, 1, 1, 1 };
    int len_test = sizeof(test)/sizeof(int);
    */

    /* Dynamic array test */
    int len_test = 20;
    int *test = (int *)malloc(len_test*sizeof(int));
    int test_static[20] = {3, 11, 22, 33, 73, 64, 41, 11, 53, 68, 47, 44, 62, 57, 37, 59, 23, 41, 29, 78};
    //41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 91, 95, 42, 27, 36
    for (int i = 0; i < len_test; i++) {
        test[i] = test_static[i];
    }
    print_arr(test, len_test);

    void (*sort)(int**, int, int) = &quick_sort;

    // Sorting
    sort(&test, 0, len_test-1);

    // Checking
    verify_sort_recursive(test, sort);
    print_arr(test, len_test);
    free(test);

    return 0;
}