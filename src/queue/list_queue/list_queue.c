#include "list_queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct _node* node;
struct _node {
    q_type val;
    node next;
};

struct _queue {
    node head;
    node tail;
};

queue q_create() {
    queue q = (queue)malloc(sizeof(queue));
    if (q == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    q->head = NULL;
    q->tail = NULL;
    return q;
}

void q_destroy(queue q) {
    node n = q->head;
    while (n) {
        q->head = q->head->next;
        free(n);
        n = q->head;
    }
    free(q);
}

void q_enqueue(queue q, q_type v) {
    node new = (node)malloc(sizeof(node));
    if (new == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    new->val = v;
    new->next = NULL;

    if (q->tail) {
        q->tail->next = new;
        q->tail = new;
    } else {
        q->head = q->tail = new;
    }
}

q_type q_dequeue(queue q) {
    if (q->head == NULL) {
        fprintf(stderr, "Queue is empty!");
        abort();
    }
    
    q_type ret = q->head->val;
    q->head = q->head->next;
    if (q->head == NULL)
        q->tail = NULL;
    return ret;
}

int q_is_empty(queue q) {
    return q->head == NULL;
}