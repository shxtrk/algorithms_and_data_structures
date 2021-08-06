#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

typedef struct _hash_table* hash_table;
typedef int ht_key_type;
typedef int ht_value_type;

hash_table ht_create(int);
void ht_destroy(hash_table);
void ht_add(hash_table, ht_key_type, ht_value_type);
int ht_exists(hash_table, ht_key_type);
ht_value_type ht_get(hash_table, ht_key_type);
void ht_remove(hash_table, ht_key_type);

#endif