#ifndef LIST_QUEUE_INCLUDED
#define LIST_QUEUE_INCLUDED

typedef struct _queue* queue;
typedef int q_type;

queue q_create();
void q_destroy(queue);
void q_enqueue(queue, q_type);
q_type q_dequeue(queue);
int q_is_empty(queue);

#endif