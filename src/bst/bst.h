#ifndef BST_INCLUDED
#define BST_INCLUDED

typedef struct _bst_node* bst_node;
typedef int bst_value_type;

bst_node bst_insert(bst_node, bst_value_type);
int bst_node_count(bst_node);
void bst_print_values(bst_node);
void bst_destroy_tree(bst_node);
int bst_contains(bst_node, bst_value_type);
int bst_height(bst_node);
bst_value_type bst_min_value(bst_node);
bst_value_type bst_max_value(bst_node);
int bst_is_valid(bst_node);
bst_node bst_delete_value(bst_node, bst_value_type);
bst_node bst_successor(bst_node, bst_value_type);

#endif