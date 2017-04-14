#include <stdlib.h>
#include "queue.h"
// #define MAX_SIZE 1000

// typedef struct queue{
//   int size;
//   int init;
//   int end;
//   int queue[MAX_SIZE];
// } queue;

void queue_init(queue* q_pt, int size)
{
  q_pt->size = size;
  q_pt->init = -1;
  q_pt->end = 0;

}

void queue_add(queue* q_pt, int val)
{
  if (queue_is_full(*q_pt))
    return;

  if (q_pt->init < 0)
    q_pt->init = q_pt->end;
  q_pt->queue[q_pt->end++] = val;
  if (q_pt->end >= q_pt->size)
    q_pt->end = 0;
}

int queue_remove(queue* q_pt)
{
  if (queue_is_empty(*q_pt))
    return -1;

  int ret = q_pt->queue[q_pt->init++];
  if (q_pt->init >= q_pt->size)
    q_pt->init = 0;
  if (q_pt->init == q_pt->end)
    q_pt->init = -1;
  return ret;
}

int queue_is_full(queue q)
{
  return q.init == q.end;
}

int queue_is_empty(queue q)
{
  return q.init == -1;
}
