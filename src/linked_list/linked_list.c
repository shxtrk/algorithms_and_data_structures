#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct _node* node;
struct _node {
    l_type value;
    node next;
};

struct _list {
    unsigned long size;
    node head;
    node tail;
};

static node l_new_node() {
    node new = (node) malloc(sizeof(struct _node));
    if (new == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    new->value = 0;
    new->next = NULL;
    return new;
}

static node l_node_at(list l, int i) {
    if (i > l->size || i < 0) {
        fprintf(stderr, "Out of index!");
        abort();
    }
    node target = l->head;
    while (i-- > 0)
        target = target->next;
    return target;
}

list l_create() {
    list new_list = (list) malloc(sizeof(struct _list));
    if (new_list == NULL) {
        fprintf(stderr, "Not enough memory!");
        abort();
    }
    new_list->size = 0;
    new_list->head = new_list->tail = NULL;
    return new_list;
}

void l_destroy(list l) {
    node n;
    while (l->head) {
        n = l->head;
        l->head = l->head->next;
        free(n);
    }
    free(l);
}

int l_size(list l) {
    return l->size;
}

int l_is_empty(list l) {
    return l->size == 0;
}

l_type l_at(list l, int i) {
    return l_node_at(l, i)->value;
}

l_type l_from_end(list l, int i) {
    if (l->size - i <= 0 || i < 0) {
        fprintf(stderr, "Out of index!");
        abort();
    }

    node found = l->head;
    for (int j = 1; j < l->size - i; j++)
        found = found->next;
    
    return found->value;
}

void l_push_front(list l, l_type v) {
    node new = l_new_node();
    new->value = v;
    new->next = l->head;
    l->head = new;
    if (l->size++ == 0)
        l->tail = new;
}

l_type l_pop_front(list l) {
    if (l_is_empty(l)) {
        fprintf(stderr, "Out of index!");
        abort();
    }
    node front = l->head;
    l_type val = front->value;

    l->head = front->next;
    free(front);

    if (--l->size == 0)
        l->tail = NULL;
    return val;
}

void l_push_back(list l, l_type v) {
    node new = l_new_node();
    new->value = v;
    if (l->size++ == 0)
        l->head = new;
    else
        l->tail->next = new;
    l->tail = new;
}

l_type l_pop_back(list l) {
    if (l_is_empty(l)) {
        fprintf(stderr, "Out of index!");
        abort();
    }

    l_type value;
    if (l->size-- == 1) {
        value = l->head->value;
        free(l->head);
        l->head = l->tail = NULL;
    } else {
        l->tail = l_node_at(l, l->size - 1);
        value = l->tail->next->value;
        free(l->tail->next);
        l->tail->next = NULL;
    }
    return value;
}

l_type l_front(list l) {
    if (l_is_empty(l)) {
        fprintf(stderr, "Out of index!");
        abort();
    }
    return l->head->value;
}

l_type l_back(list l) {
    if (l_is_empty(l)) {
        fprintf(stderr, "Out of index!");
        abort();
    }
    return l->tail->value;
}

void l_insert(list l, int i, l_type v) {
    if (i != 0 && i > l->size || i < 0) {
        fprintf(stderr, "Out of index!");
        abort();
    }
    node new = l_new_node();
    new->value = v;
    if (i == 0) {
        new->next = l->head;
        l->head = new;
        if (l->tail == NULL)
            l->tail = new;
    } else {
        node prev = l_node_at(l, i - 1);
        new->next = prev->next;
        prev->next = new;
        if (l->size == i)
            l->tail = new;
    }
    l->size++;
}

void l_remove_at(list l, int i) {
    if (i >= l->size || i < 0) {
        fprintf(stderr, "Out of index!");
        abort();
    }

    if (l->size-- == 1) {
        free(l->head);
        l->head = l->tail = NULL;
    } else if (i == 0) {
        node next = l->head->next;
        free(l->head);
        l->head = next;
    } else {
        node prev = l_node_at(l, i - 1);
        node target = prev->next;
        prev->next = prev->next->next;
        free(target);
        if (l->size == i)
            l->tail = prev;
    }
}

void l_reverse(list l) {
    node curr = l->head;
    node prev = NULL, next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    l->head = prev;
    l->tail = curr;
}