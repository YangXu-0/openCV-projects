#include <stdio.h>
#include <stdlib.h>

// Question 3
int *create_array(int n, int initial_value) {
    int* array = (int *)malloc(sizeof(int)*n);
    if (array == NULL) {
        return NULL;
    }

    for (int i = 0; i<n; i++) {
        array[i] = initial_value;
    }
    return array;
}


// Question 4
// Givens:
struct point {
    int x, y;
};
struct rectangle {
    struct point upper_left, lower_right;
};


// Question 11
// Given:
struct node {
    int value;
    struct node *next;
};

int count_occurences(struct node *list, int n) {
    if (list == NULL) {
        return 0;
    }

    int counter = 0;
    while (list != NULL) {
        if (list->value == n) {
            counter += 1;
        }

        list = list->next;
    }

    return counter;
}

struct node* link_array(int arr[], int len_arr) {
    int size = len_arr / sizeof(int);
    printf("Size is: %d\n", size);
    struct node *head = NULL;
    struct node *prev = NULL;
    for (int i = 0; i<size; i++) {
        struct node *temp = (struct node*)malloc(sizeof(struct node));
        temp->value = arr[i];
        temp->next = NULL;

        if (head == NULL) {
            head = temp;
            prev = temp;
        }
        else {
            prev->next = temp;
            prev = temp;
        }
    }

    // if wanted a tail, it would be "tail = prev;"

    return head;
}

struct node* free_link(struct node** arr) {
    while ((*arr)->next != NULL) {
        struct node* temp = (*arr)->next;
        free(*arr);
        *arr = temp;
    }

    free(*arr);

    *arr = NULL;
    return *arr;
}

void print_link(struct node* arr) {
    if (arr == NULL) {
        printf("This linked list does not exist");
    }

    while (arr->next != NULL) {
        printf("The value of this node is: %d\n", arr->value);
        arr = arr->next;
    }
    printf("The value of this node is: %d\n", arr->value);

    return;
}


// Question 12
struct node *find_last(struct node *list, int n) {
    struct node *temp = NULL;
    while (list != NULL) {
        if (list->value == n) {
            temp = list;
        }

        list = list->next;
    }

    return temp;
}


int main(void) {
    // #3, 4, 11, 12
    
    // Question 3
    /*
    int* test1 = create_array(5, 3);
    int i = 0;
    while (test1[i] == 3) {
        printf("The value of the array at %d is: %d\n", i, test1[i]);
        i++;
    }
    free(test1);
    printf("%d", test1[0]);
    */

    // Question 4
    /*
    struct rectangle *p;
    p = (struct rectangle *)malloc(sizeof(struct rectangle));
    (p->upper_left).x = 10;
    (p->upper_left).y = 25;
    (p->lower_right).x = 20;
    (p->lower_right).y = 15;

    printf("The upper left corner of rectangle is: (%d, %d)\n", (p->upper_left).x, (p->upper_left).y);
    printf("The lower right corner of rectangle is: (%d, %d)\n", (p->lower_right).x, (p->lower_right).y);
    free(p);
    printf("%d\n", (p->upper_left).x);
    */

    // Question 11
    /*
    int test2[] = {5, 2, 3, 4, 5, 5, 5, 5};
    struct node* test2_linked = link_array(test2, sizeof(test2));
    print_link(test2_linked);
    int occurances = count_occurences(test2_linked, 5);
    printf("The number of occurances is: %d\n", occurances);
    test2_linked = free_link(&test2_linked);
    print_link(test2_linked);
    */
    /*
    int occurances = count_occurences(NULL, 5);
    printf("The number of occurances is: %d\n", occurances);
    */

    // Question 12
    int test3[] = {1, 2, 3, 4, 5};
    struct node* test3_linked = link_array(test3, sizeof(test3));
    print_link(test3_linked);
    struct node *last_occ = find_last(test3_linked, 5);
    if (last_occ == NULL) {
        printf("Null was returned\n");
    }
    else {
        printf("The value %d was found before %d\n", last_occ->value, last_occ->next->value); 
    }
    test3_linked = free_link(&test3_linked);
    print_link(test3_linked);

    return 0;
}