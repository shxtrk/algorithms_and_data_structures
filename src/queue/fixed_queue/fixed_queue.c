#include "fixed_queue.h"
#include <stdio.h>
#include <stdlib.h>

struct _f_queue {
    fq_type *arr;
    int cap, size, head;
};

f_queue fq_create(int c) {
    f_queue q = (f_queue)malloc(sizeof(struct _f_queue));
    if (q == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    q->arr = (fq_type *)malloc(sizeof(fq_type) * c);
    if (q->arr == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    q->cap = c;
    q->size = 0;
    q->head = 0;
    return q;
}

void fq_destroy(f_queue q) {
    free(q->arr);
    free(q);
}

void fq_enqueue(f_queue q, fq_type v) {
    if (q->size == q->cap) {
        fprintf(stderr, "Queue is full!");
        abort();
    }
    q->arr[(q->head + q->size++) % q->cap] = v;
}

fq_type fq_dequeue(f_queue q) {
    if (q->size == 0) {
        fprintf(stderr, "Queue is empty!");
        abort();
    }
    fq_type ret = q->arr[q->head];
    q->head = (q->head + 1) % q->cap;
    q->size--;
    return ret;
}

int fq_is_empty(f_queue q) {
    return q->size == 0;
}

int fq_is_full(f_queue q) {
    return q->size == q->cap;
}