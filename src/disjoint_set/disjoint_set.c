#include "disjoint_set.h"
#include <stdlib.h>
#include <stdio.h>

struct _d_set {
    int* root;
    int* rank;
};

d_set ds_create(int s) {
    d_set set = (d_set)malloc(sizeof(struct _d_set));
    if (set == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    int *root = (int*)malloc(s * sizeof(int));
    int *rank = (int*)malloc(s * sizeof(int));
    if (root == NULL || rank == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    set->root = root;
    set->rank = rank;
    for (int i = 0; i < s; i++) {
        set->root[i] = i;
        set->rank[i] = 1;
    }
    return set;
}

void ds_destroy(d_set set) {
    free(set->root);
    free(set->rank);
    free(set);
}

int ds_find(d_set set, int x) {
    if (set->root[x] == x) {
        return x;
    }
    return set->root[x] = ds_find(set, set->root[x]);
}

void ds_union(d_set set, int x, int y) {
    int rootX = ds_find(set, x);
    int rootY = ds_find(set, y);

    if (rootX != rootY) {
        if (set->rank[rootX] > set->rank[rootY]) {
            set->root[rootY] = rootX;
        } else if (set->rank[rootX] < set->rank[rootY]) {
            set->root[rootX] = rootY;
        } else {
            set->root[rootY] = rootX;
            set->rank[rootX] += 1;
        }
    }
}

int ds_connected(d_set set, int x, int y) {
    return ds_find(set, x) == ds_find(set, y);
}