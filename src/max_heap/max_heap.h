#ifndef MAX_HEAP_INCLUDED
#define MAX_HEAP_INCLUDED

typedef struct _max_heap* max_heap;
typedef int max_h_type;

max_heap max_h_create(int);
void max_h_destroy(max_heap);
max_h_type max_h_max(max_heap);
int max_h_size(max_heap);
int max_h_is_empty(max_heap);
void max_h_insert(max_heap, max_h_type);
max_h_type max_h_extract(max_heap);
void max_h_sort(max_h_type *, int);

#endif
