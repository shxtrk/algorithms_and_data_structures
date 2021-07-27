#ifndef FIXED_QUEUE_INCLUDED
#define FIXED_QUEUE_INCLUDED

typedef struct _f_queue *f_queue;
typedef int fq_type;

f_queue fq_create(int);
void fq_destroy(f_queue);
void fq_enqueue(f_queue, fq_type);
fq_type fq_dequeue(f_queue);
int fq_is_empty(f_queue);
int fq_is_full(f_queue);

#endif