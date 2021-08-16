#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

#define min(x,y) (((x)<(y))?(x):(y))
#define max(x,y) (((x)>(y))?(x):(y))

struct _bst_node {
    bst_value_type value;
    bst_node left;
    bst_node right;
};

static void bst_print_nodes(bst_node root) {
    if (root->left != NULL) {
        bst_print_nodes(root->left);
        printf(", ");
    }
    printf("%d", root->value);
    if (root->right != NULL) {
        printf(", ");
        bst_print_nodes(root->right);
    }
}

static int bst_is_valid_util(bst_node root, bst_value_type min_val, bst_value_type max_val) {
    if (root == NULL)
        return 1;

    if (root->value >= min_val && root->value <= max_val
        && bst_is_valid_util(root->left, min_val, root->value)
        && bst_is_valid_util(root->right, root->value, max_val))
        return 1;

    return 0;
}

static bst_node bst_find(bst_node root, bst_value_type value) {
    if (root == NULL)
        return NULL;
    else if (value < root->value)
        return bst_find(root->left, value);
    else if (value > root->value)
        return bst_find(root->right, value);
    else
        return root;
}

static bst_node  bst_find_min(bst_node root) {
    if (root == NULL)
        return NULL;
    while (root->left != NULL)
        root = root->left;
    return root;
}

bst_node bst_insert(bst_node root, bst_value_type value) {
    if (root == NULL) {
        root = (bst_node)malloc(sizeof(struct _bst_node));
        if (root == NULL) {
            fprintf(stderr, "Not enough memory!");
            abort();
        }
        root->value = value;
        root->left = NULL;
        root->right = NULL;
    } else if (value <= root->value)
        root->left = bst_insert(root->left, value);
    else
        root->right = bst_insert(root->right, value);
    return root;
}

int bst_node_count(bst_node root) {
    if (root == NULL)
        return 0;
    else
        return bst_node_count(root->left) + bst_node_count(root->right) + 1;
}

void bst_print_values(bst_node root) {
    if (root == NULL)
        printf("BST is empty\n");
    else {
        printf("[");
        bst_print_nodes(root);
        printf("]\n");
    }
}

void bst_destroy_tree(bst_node root) {
    if (root == NULL)
        return;
    
    bst_destroy_tree(root->left);
    bst_destroy_tree(root->right);
    free(root);
}

int bst_contains(bst_node root, bst_value_type value) {
    if (root == NULL)
        return 0;
    else if (value < root->value)
        return bst_contains(root->left, value);
    else if (value > root->value)
        return bst_contains(root->right, value);
    return 1;
}

int bst_height(bst_node root) {
    if (root == NULL)
        return 0;
    else
        return max(bst_height(root->left), bst_height(root->right)) + 1;
}

bst_value_type bst_min_value(bst_node root) {
    if (root == NULL) {
        printf("BST is empty");
        abort();
    }
    while (root->left != NULL)
        root = root->left;
    return root->value;
}

bst_value_type bst_max_value(bst_node root) {
    if (root == NULL) {
        printf("BST is empty");
        abort();
    }
    while (root->right != NULL)
        root = root->right;
    return root->value;
}

int bst_is_valid(bst_node root) {
    return bst_is_valid_util(root, INT32_MIN, INT32_MAX);
}

bst_node bst_delete_value(bst_node root, bst_value_type value) {
    if (root == NULL)
        return root;
    else if (value < root->value)
        root->left = bst_delete_value(root->left, value);
    else if (value > root->value)
        root->right = bst_delete_value(root->right, value);
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        } else if (root->left == NULL) {
            bst_node temp = root;
            root = root->right;
            free(temp);
        } else if (root->right == NULL) {
            bst_node temp = root;
            root = root->left;
            free(temp);
        } else {
            root->value = bst_min_value(root->right);
            root->right = bst_delete_value(root->right, root->value);
        }
    }
    return root;
}

bst_node bst_successor(bst_node root, bst_value_type value) {
    bst_node current = bst_find(root, value);
    if (current == NULL)
        return NULL;
    if (current->right != NULL)
        return bst_find_min(root->right);
    else {
        bst_node successor = NULL;
        bst_node ancestor = root;
        while (ancestor != current) {
            if (current->value < ancestor->value) {
                successor = ancestor;
                ancestor = ancestor->left;
            } else
                ancestor = ancestor->right;
        }
        return successor;
    }
}