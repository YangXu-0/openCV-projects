#include <stdio.h>
#include <stdlib.h>

/*
- Binary tree struct
- Insert
- Search
- Delete
- Free
*/

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;


Node *initialize_tree(int val) {
    Node *new = (Node *)malloc(sizeof(Node));
    new->value = val;
    new->left = NULL;
    new->right = NULL;
    return new;
}


void insert(Node **root, int val) {
    Node *temp = *root;
    Node *prev_temp = NULL;
    
    while (temp != NULL) {
        prev_temp = temp;
        if (temp->value < val) {
            temp = temp->right;
        }
        else {
            temp = temp->left;
        }
    }

    temp = (Node *)malloc(sizeof(Node));
    temp->value = val;
    temp->left = NULL;
    temp->right = NULL;

    if (*root == NULL) {
        *root = temp;
        return;
    }

    printf("The parent value is %d and the child value is %d\n", prev_temp->value, temp->value);
    if (prev_temp->value < val) {
        printf("Right\n");
        prev_temp->right = temp;
    }
    else {
        printf("Left\n");
        prev_temp->left = temp;
    }
    
    return;
}


int search(Node *root, int val) {
    Node *temp = root;

    while (temp != NULL) {
        if (temp->value == val) {
            return 1;
        }
        
        if (temp->value < val) {
            temp = temp->right;
        }
        else {
            temp = temp->left;
        }

    }
    return 0;
}

void free_tree(Node **root) {
    if ((*root)->right != NULL) {
        free_tree(&((*root)->right));
    }
    if ((*root)->left != NULL) {
        free_tree(&((*root)->left));
    }

    free(*root);
    *root = NULL;
    return;
}

void print_inorder(Node* root){
    if (root == NULL){
        return;
    } else {
        print_inorder(root->left);
        fprintf(stdout, "%d ", root->value);
        print_inorder(root->right);
    }
    fprintf(stdout, "\n");
}

void better_print(Node *root) {
    if (root->right != NULL) {
        printf("%d has a right child of value: %d\n", root->value, root->right->value);
        better_print(root->right);
    }
    if (root->left != NULL) {
        printf("%d has a left child of value: %d\n", root->value, root->left->value);
        better_print(root->left);
    }
}

int main(void) {
    
    Node* bst = initialize_tree(100);
    insert(&bst, 90);
    insert(&bst, 120);
    insert(&bst, 150);
    insert(&bst, 60);
    insert(&bst, 70);
    print_inorder(bst);
    better_print(bst);

    free_tree(&bst);

    return 0;
}