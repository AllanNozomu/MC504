#include <stdlib.h>
#define MAX_SIZE 1000

typedef struct queue{
  int size;
  int init;
  int end;
  int queue[MAX_SIZE];
} queue;

void queue_init(queue* q_pt, int size);
void queue_add(queue* q_pt, int val);
int queue_remove(queue* q_pt);
int queue_is_full(queue q);
int queue_is_empty(queue q);
