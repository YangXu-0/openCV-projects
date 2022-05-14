#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};


struct node *link_array(int arr[], int n) {
    struct node *new = NULL;
    struct node *prev = NULL;

    for (int i = 0; i < (n/sizeof(int)); i++) {
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        temp->value = arr[i];
        temp->next = NULL;
        
        if (new == NULL) {
            new = temp;
            prev = temp;
        }
        else {
            prev->next = temp;
            prev = temp;
        }
    }

    return new;
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


void dequeue(struct node **arr, int n) {
    if (arr == NULL || *arr == NULL) {
        printf("List does not exist or is not passed in properly\n");
        return;
    }

    struct node *iter = *arr;
    struct node *prev = NULL;
    while (iter != NULL) {
        if (iter->value == n) {
            break;
        }

        prev = iter;
        iter = iter->next;
    }

    if (iter == NULL) {
        printf("Node not found\n");
    }
    else if (prev == NULL) {
        (*arr) = iter->next;
        free(iter);
    }
    else {
        prev->next = iter->next;
        free(iter);
    }

    return;
}


struct node *find(struct node *arr, int n) {
    if (arr == NULL) {
        printf("Node not found\n");
        return arr;
    }
    else if (arr->value == n) {
        return arr;
    }

    return find(arr->next, n);

}

int main() {
    int test[] = {1, 2, 3, 4, 5};
    struct node *linked_test = link_array(test, sizeof(test));
    printf("Original list:\n");
    print_link(linked_test);

    for (int i = 1; i < 6; i++) {
        struct node *index = find(linked_test, i);
        printf("%d at %p before %p\n", index->value, index, index->next);
    }

    struct node *index = find(linked_test, 7);

    free_link(&linked_test);
    printf("Freed list:\n");
    print_link(linked_test);

    return 0;
}