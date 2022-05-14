#include <stdio.h>
#include <stdlib.h>

/* 
Functions:
- Rotate left
- Rotate right
- Rotate left right
- Rotate right left
- Update height
- Balance
- Initialize tree
- Insert
- Remove
- Search
*/


typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
    int height;
} Node;


int update_height(Node *root);


void rotate_left(Node **root) {
    // Right right violation --> rotate left
    
    Node *temp = (*root)->right;
    (*root)->right = temp->left;
    temp->left = *root;
    *root = temp;
    
    /*
    Node *temp = (*root)->right;
    (*root)->right = temp->right;
    temp->right = temp->left;
    temp->left = (*root)->left;
    (*root)->left = temp;

    int temp_val = temp->value;
    temp->value = (*root)->value;
    (*root)->value = temp_val;
    */
    update_height(*root); // Need to update height
}


void rotate_right(Node **root) {
    // Left left violation --> rotate right
    
    Node *temp = (*root)->left;
    (*root)->left = temp->right;
    temp->right = *root;
    *root = temp;
    
    /*
    Node *temp = (*root)->left;
    (*root)->left = temp->left;
    temp->left = temp->right;
    temp->right = (*root)->right;
    (*root)->right = temp;

    int temp_val = temp->value;
    temp->value = (*root)->value;
    (*root)->value = temp_val;
    */
    update_height(*root); // Need to update height
}


void rotate_right_left(Node **root) {
    // Right left violation
    rotate_right(&((*root)->right));
    rotate_left(root);
}


void rotate_left_right(Node **root) {
    // Left right violation
    rotate_left(&((*root)->left));
    rotate_right(root);
}


int update_height(Node *root) {
    // Don't have to pass in whole tree (can pass in subtree)
    if (root == NULL) {
        return -1;
    }
    
    int left_height = update_height(root->left);
    int right_height = update_height(root->right);

    if (left_height > right_height) {
        root->height = left_height + 1;
    }
    else {
        root->height = right_height + 1;
    }
    
    return root->height;
}


void balance(Node *root) {
    if (root == NULL) {
        return;
    }
    
    balance(root->right);
    balance(root->left);

    int right_height;
    int left_height;
    if (root->right == NULL) {
        right_height = -1;
    }
    else {
        right_height = root->right->height;
    }
    if (root->left == NULL) {
        left_height = -1;
    }
    else {
        left_height = root->left->height;
    }
    
    int bf = right_height - left_height;
    printf("ran value: %d  bf: %d\n", root->value, bf);
    if (bf > 1) { // right violation
        if (root->right != NULL && root->right->right != NULL && root->right->left != NULL) {
            if (root->right->right->height < root->right->left->height) {
                rotate_right(&(root->right));
            }
        }
        rotate_left(&(root));
        printf("rotated right\n");
    }
    else if (bf < -1) {
        if (root->left != NULL && root->left->right != NULL && root->left->left != NULL) {
            if (root->left->left->height < root->left->right->height) {
                rotate_left(&(root->left));
            }
        }
        rotate_right(&(root));
        printf("rotated left\n");
    }

    return;
}


Node *initialize(int val) {
    Node *new = (Node *)malloc(sizeof(Node));
    new->value = val;
    new->left = NULL;
    new->right = NULL;
    new->height = 0;
}


void insert_node(Node **root, int val) {
    Node *new = initialize(val);
    
    if (*root == NULL) {
        *root = new;
        return;
    }
    
    Node *iter = *root;
    while (1==1) {
        if (iter->value < val) {
            if (iter->right == NULL) {
                iter->right = new;
                break;
            }
            else {
                iter = iter->right;
            }
        }
        else {
            if (iter->left == NULL) {
                iter->left = new;
                break;
            }
            else {
                iter = iter->left;
            }
        }
    }
    
    update_height(*root);
    balance(*root);
}


void remove_node(Node **root, int val) {
    if ((*root)->value == val) {
        free(*root);
        *root = NULL;
    }

    Node *iter = *root;
    while (1==1) {

        Node *temp;

        if (iter->value < val) {
            temp = iter->right;
        }
        else {
            temp = iter->left;
        }

        if (temp == NULL) {
            return;
        }
        if (temp->value == val) {
            if (val > iter->value) {
                iter->right = NULL;
            }
            else {
                iter->left = NULL;
            }
            free(temp);
            update_height(*root);
            balance(*root);
            return;
        }
        
        if (val > iter->value) {
            iter = iter->right;
        }
        else {
            iter = iter->left;
        }
    }   
}


void better_print(Node *root) {
    if (root->right != NULL) {
        printf("%d has a right child of value: %d  height: %d\n", root->value, root->right->value, root->right->height);
        better_print(root->right);
    }
    if (root->left != NULL) {
        printf("%d has a left child of value: %d  height: %d\n", root->value, root->left->value, root->left->height);
        better_print(root->left);
    }
}

int main(void) {

    Node *avl_tree = NULL;
    insert_node(&avl_tree, 9);
    insert_node(&avl_tree, 1);
    insert_node(&avl_tree, 50);
    insert_node(&avl_tree, 25);
    insert_node(&avl_tree, 19);
    insert_node(&avl_tree, 30);
    insert_node(&avl_tree, 100);
    insert_node(&avl_tree, 60);
    insert_node(&avl_tree, 110);
    insert_node(&avl_tree, 55);
    insert_node(&avl_tree, 80);
    insert_node(&avl_tree, 90);
    better_print(avl_tree);

    return 0;
}