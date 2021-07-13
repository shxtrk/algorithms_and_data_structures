#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

#define MINCAP 16
#define min(x,y) (((x)<(y))?(x):(y))

struct _vector {
    v_type* array;
    int size;
    int capacity;
};

static int v_initial_cap(int c) {
    int s = MINCAP;
    while (s < c)
        s *= 2;
    return s;
}

static void v_double_capacity(vector v) {
    int new_cap = 2 * v->capacity;
    v_type *new_arr = (v_type*)realloc(v->array, new_cap * sizeof(v_type));
    if (new_arr == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    v->array = new_arr;
    v->capacity = new_cap;
}

static void v_half_capacity(vector v) {
    if (v->capacity <= MINCAP)
        return;
    int new_cap = v->capacity / 2;
    v_type *new_arr = (v_type*)realloc(v->array, new_cap * sizeof(v_type));
    if (new_arr == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    v->array = new_arr;
    v->capacity = new_cap;
    v->size = min(v->size, new_cap);
}

vector v_create(int capacity) {
    vector v = (vector) malloc(sizeof(struct _vector));
    if (v == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    v->size = 0;
    v->capacity = v_initial_cap(capacity);
    v->array = (v_type*) malloc(sizeof(v_type) * v->capacity);
    if (v->array == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    return v;
}

void v_destroy(vector v) {
    free(v->array);
    free(v);
}

int v_size(vector v) {
    return v->size;
}

int v_capacity(vector v) {
    return v->capacity;
}

int v_is_empty(vector v) {
    return v->size == 0;
}

v_type v_at(vector v, int i) {
    if (i < 0 || i >= v->size) {
        fprintf(stderr, "Out of index!");
        abort();
    }
    return *(v->array + i);
}

void v_push(vector v, v_type x) {
    if (v->size >= v->capacity)
        v_double_capacity(v);
    *(v->array + v->size++) = x;
}

v_type v_pop(vector v) {
    if (v->size <= 0) {
        fprintf(stderr, "Vector is empty!");
        abort();
    }
    v_type val = *(v->array + --v->size);
    if (4 * v->size < v->capacity)
       v_half_capacity(v);
    return val;
}

void v_set(vector v, int i, v_type x) {
    if (i < 0 || i >= v->size) {
        fprintf(stderr, "Out of index!");
        abort();
    }
    *(v->array + i) = x;
}

void v_prepend(vector v, v_type x) {
    v_insert(v, 0, x);
}

void v_insert(vector v, int i, v_type x) {
    if (i < 0 || i >= v->size) {
        fprintf(stderr, "Out of index!");
        abort();
    }
    if (v->size >= v->capacity)
        v_double_capacity(v);
    for(int j = v->size; j>i; j--)
        *(v->array + j) = *(v->array + j - 1);
    *(v->array + i) = x;
    v->size++;
}

v_type v_delete(vector v, int i) {
    if (i < 0 || i >= v->size) {
        fprintf(stderr, "Out of index!");
        abort();
    }
    v_type ret = *(v->array + i);
    for(int j = i + 1; j < v->size; j++)
        *(v->array + j - 1) = *(v->array + j);
    v->size--;
    if (4 * v->size < v->capacity)
        v_half_capacity(v);
    return ret;
}

void v_remove(vector v, v_type x) {
    int found = -1;
    while ((found = v_find(v, x)) != -1)
        v_delete(v, found);
}

void v_clear(vector v) {
    v_type *new_arr = (v_type*)realloc(v->array, MINCAP * sizeof(v_type));
    if (new_arr == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    v->size = 0;
    v->capacity = MINCAP;
    v->array = new_arr;
}

int v_find(vector v, v_type x) {
    for (int i = 0; i < v->size; i++)
        if (*(v->array + i) == x)
            return i;
    return -1;
}