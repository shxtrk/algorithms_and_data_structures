#include "max_heap.h"
#include <stdlib.h>
#include <stdio.h>

struct _max_heap {
    max_h_type *array;
    int capacity;
    int size;
};

static void sift_up(max_h_type *array, int i) {
    int parent = (i - 1) / 2;
    while (parent >= 0 && array[i] > array[parent]) {
        int temp = array[i];
        array[i] = array[parent];
        array[parent] = temp;
        i = parent;
        parent = (i - 1) / 2;
    }
}

static void sift_down(max_h_type *array, int s, int i) {
    while (i < s / 2) {
        int left = i * 2 + 1;
        int right = (i * 2) + 2;
        if (array[i] < array[left] || array[i] < array[right]) {
            if (array[left] > array[right]) {
                int temp = array[left];
                array[left] = array[i];
                array[i] = temp;
                i = left;
            } else {
                int temp = array[right];
                array[right] = array[i];
                array[i] = temp;
                i = right;
            }
        } else {
            break;
        }
    }
}

static void max_h_heapify(max_h_type *array, int s, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if (left < s && array[left] > array[largest]) {
        largest = left;
    }
    if (right < s && array[right] > array[largest]) {
        largest = right;
    }
    if (largest != i) {
        int temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;
        max_h_heapify(array, s, largest);
    }
}

max_heap max_h_create(int capacity) {
    max_heap h = (max_heap)malloc(sizeof(struct _max_heap));
    if (h == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    h->size = 0;
    h->capacity = capacity;
    h->array = (max_h_type*)malloc(sizeof(max_h_type) * h->capacity);
    if (h->array == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    return h;
}

void max_h_destroy(max_heap h) {
    free(h->array);
    free(h);
}

max_h_type max_h_max(max_heap h) {
    if (h->size == 0) {
        fprintf(stderr, "Heap is empty!");
        abort();
    }
    return h->array[0];
}

int max_h_size(max_heap h) {
    return h->size;
}

int max_h_is_empty(max_heap h) {
    return h->size == 0;
}

void max_h_insert(max_heap h, max_h_type v) {
    if (h->size + 1 > h->capacity) {
        fprintf(stderr, "Heap is full!");
        abort();
    }
    h->array[h->size] = v;
    sift_up(h->array, h->size++);
}

max_h_type max_h_extract(max_heap h) {
    if (h->size == 0) {
        fprintf(stderr, "Heap is empty!");
        abort();
    }
    max_h_type v = h->array[0];
    h->array[0] = h->array[--h->size];
    sift_down(h->array, h->size, 0);
    return v;
}

void max_h_sort(max_h_type *array, int s) {
    for (int i = s / 2 - 1; i >= 0; i--) {
        max_h_heapify(array, s, i);
    }

    for (int i = s - 1; i > 0; i--) {
        int temp = array[i];
        array[i] = array[0];
        array[0] = temp;
        max_h_heapify(array, i, 0);
    }
}