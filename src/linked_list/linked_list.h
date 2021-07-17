#ifndef LINKED_LIST_INCLUDED
#define LINKED_LIST_INCLUDED

typedef struct _list* list;
typedef int l_type;

list l_create();
void l_destroy(list);
int l_size(list);
int l_is_empty(list);
l_type l_at(list, int);
l_type l_from_end(list, int);
void l_push_front(list, l_type);
l_type l_pop_front(list);
void l_push_back(list, l_type);
l_type l_pop_back(list);
l_type l_front(list);
l_type l_back(list);
void l_insert(list, int, l_type);
void l_remove_at(list, int);
void l_reverse(list);

#endif