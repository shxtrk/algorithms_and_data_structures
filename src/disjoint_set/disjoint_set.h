#ifndef DISJOINT_SET_INCLUDED
#define DISJOINT_SET_INCLUDED

typedef struct _d_set* d_set;

d_set ds_create(int);
void ds_destroy(d_set);
int ds_find(d_set, int);
void ds_union(d_set, int, int);
int ds_connected(d_set, int, int);

#endif