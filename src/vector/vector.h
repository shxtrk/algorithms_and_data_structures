#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

typedef struct _vector* vector;
typedef int v_type;

vector v_create(int);
void v_destroy(vector);
int v_size(vector);
int v_capacity(vector);
int v_is_empty(vector);
v_type v_at(vector, int);
void v_push(vector, v_type);
v_type v_pop(vector);
void v_set(vector, int, v_type);
void v_prepend(vector, v_type);
void v_insert(vector, int, v_type);
v_type v_delete(vector, int);
void v_remove(vector, v_type);
void v_clear(vector);
int v_find(vector, v_type);

#endif