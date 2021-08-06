#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN_CAP 7
#define PROBING_FACTOR 17
#define LOAD_FACTOR 0.65

#define min(x,y) (((x)<(y))?(x):(y))
#define max(x,y) (((x)>(y))?(x):(y))

typedef struct _node* node;
struct _node {
    ht_key_type key;
    ht_value_type value;
};

struct _hash_table {
    node* array;
    int size;
    int capacity;
    int threshold;
};

static int ht_hash(ht_key_type k, int m) {
    return k % m;
}

static int ht_gcd(int a, int b) {
    if (b == 0) return a;
    return ht_gcd(b, a % b);
}

static node ht_get_node(hash_table ht, ht_key_type k) {
    int hash = ht_hash(k, ht->capacity);
    int x = 1, index = hash;
    while (1) {
        if (ht->array[index] != NULL)
            if (ht->array[index]->key == k) return ht->array[index];
            else index = (hash + (x++ * PROBING_FACTOR)) % ht->capacity;
        else return NULL;
    }   
}

static int ht_add_into(node* array, int c, ht_key_type k, ht_value_type v) {
    int hash = ht_hash(k, c);
    int x = 1, index = hash;
    while (1) {
        if (array[index] != NULL) {
            if (array[index]->key == k) {
                array[index]->value = v;
                return 0;
            } else index = (hash + (x++ * PROBING_FACTOR)) % c;
        } else {
            node n = (node)malloc(sizeof(struct _node));
            if (n == NULL) {
                fprintf(stderr, "Not enough memory!");
                abort();
            }
            n->key = k;
            n->value = v;
            array[index] = n;
            return 1;
        }
    }
}

static void ht_increase_capacity(hash_table ht) {
    int new_cap = 2 * ht->capacity + 1;
    while (ht_gcd(PROBING_FACTOR, new_cap) != 1)
        new_cap++;
    node* new_array = (node*)malloc(sizeof(node) * new_cap);
    if (new_array == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    for (int i = 0; i < new_cap; i++)
         *(new_array + i) = NULL;
    for (int i = 0; i < ht->capacity; i++)
        if (*(ht->array + i) != NULL) {
            ht_add_into(new_array, new_cap, ht->array[i]->key, ht->array[i]->value);
            free(ht->array[i]);
        }
    free(ht->array);
    ht->array = new_array;
    ht->capacity = new_cap;
    ht->threshold = (int)(ht->capacity * LOAD_FACTOR);
}

hash_table ht_create(int c) {
    hash_table ht = (hash_table)malloc(sizeof(struct _hash_table));
    if (ht == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    ht->size = 0;
    ht->capacity = max(c, MIN_CAP);
    while (ht_gcd(PROBING_FACTOR, ht->capacity) != 1) {
      ht->capacity++;
    }
    ht->threshold = (int)(ht->capacity * LOAD_FACTOR);
    ht->array = (node*)malloc(sizeof(node) * ht->capacity);
    if (ht->array == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    for (int i = 0; i < ht->capacity; i++) {
        *(ht->array + i) = NULL;
    }
    return ht;
}

void ht_destroy(hash_table ht) {
    for (int i = 0; i < ht->capacity; i++)
        if (ht->array[i] != NULL)
            free(ht->array[i]);
    free(ht->array);
    free(ht);
}

void ht_add(hash_table ht, ht_key_type k, ht_value_type v) {
    if (ht->size >= ht->threshold)
        ht_increase_capacity(ht);
    ht->size += ht_add_into(ht->array, ht->capacity, k, v);
}

int ht_exists(hash_table ht, ht_key_type k) {
    return ht_get_node(ht, k) != NULL;
}

ht_value_type ht_get(hash_table ht, ht_key_type k) {
    node n = ht_get_node(ht, k);
    if (n == NULL) {
        fprintf(stderr, "Key doesn't exist!");
        abort();
    }
    return n->value;
}

void ht_remove(hash_table ht, ht_key_type k) {
    int hash = ht_hash(k, ht->capacity);
    int x = 1, index = hash;
    while (1) {
        if (ht->array[index] != NULL) {
            if (ht->array[index]->key == k) {
                free(ht->array[index]);
                ht->array[index] = NULL;
                return;
            } else index = (hash + (x++ * PROBING_FACTOR)) % ht->capacity;
        } else {
            fprintf(stderr, "Key doesn't exist!");
            abort();
        }
    }   
}