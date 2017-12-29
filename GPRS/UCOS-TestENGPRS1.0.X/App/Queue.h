#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "user.h"
#define MAXQUEUE 10

typedef struct Node
{
    u8 Item[12];
    struct Node *next;
}NODE;

typedef struct Queue
{
    int Length;
    NODE *fron;
    NODE *bear;
}QUEUE;

void InitializeqQueue(QUEUE *pq);
bool QueueIsFull(const QUEUE *pq);
bool QueueIsEmpty(const QUEUE *pq);
int QueueItemCount(const QUEUE *pq);
bool EnQueue(u8*,QUEUE*pq);
bool DeQueue(u8*,QUEUE *pq);
void EmtpyQueue(QUEUE *pq);


#endif



