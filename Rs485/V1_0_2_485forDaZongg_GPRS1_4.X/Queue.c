/*
建立队列数据结构
xyp
//用于存放发送的数据
2016/11/12
*/
#include <stdio.h>
//#include <stdbool.h>
#include <stdlib.h>
#include "Queue.h"

//建立队列
void InitializeqQueue(QUEUE *pq)
{
    pq->bear=pq->fron=NULL;
    pq->Length=0;
}

bool QueueIsFull(const QUEUE *pq)
{
    return pq->Length==MAXQUEUE;
}

bool QueueIsEmpty(const QUEUE *pq)
{
    return pq->Length==0;
}

int QueueItemCount(const QUEUE *pq)
{
    return pq->Length;
}
//从队伍尾部添加节点
bool EnQueue(u8* item,QUEUE *pq)
{
    NODE *pnew;
    u8 cnt=0;
    if(QueueIsFull(pq))
        return false;
    pnew=(NODE*)malloc(sizeof(NODE));
    if(pnew==NULL)
        return false;
    for(cnt=0;cnt<16;cnt++)
        pnew->Item[cnt]=*(item+cnt);
    pnew->next=NULL;
    if(QueueIsEmpty(pq))
        pq->fron=pnew;
    else
        pq->bear->next=pnew;
    pq->bear=pnew;
    pq->Length+=1;
    return true;
}

bool DeQueue(u8* item,QUEUE *pq)
{
    NODE *pold;
    u8 cnt=0;
    if(QueueIsEmpty(pq))
        return false;
    for(cnt=0;cnt<16;cnt++)
        pq->fron->Item[cnt]=*(item+cnt);//???
    pold=pq->fron;
    pq->fron=pq->fron->next;
    free(pold);
    pq->Length-=1;
    if(pq->Length==0)
        pq->bear=NULL;
    return true;
}

void EmptyQueue(QUEUE *pq)
{
    u8* item=0;
    while(!QueueIsEmpty(pq))
        DeQueue(item,pq);
}




