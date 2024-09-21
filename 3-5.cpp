//顺序队列
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>
#include<iostream>
#define ElemType int
#define MAXSIZE 8

using namespace std;

typedef struct Queue
{
    ElemType *base;
    int front;
    int rear;
}Queue;

void InitQueue(Queue *Q)
{
    Q->base=(ElemType *)malloc(sizeof(ElemType)*MAXSIZE);
    assert(Q->base!=NULL);
    Q->front=Q->rear=0;
}

void EnQueue(Queue *Q,ElemType x)
{
    if(Q->rear>=MAXSIZE)
        return;
    Q->base[Q->rear++]=x;
}

void ShowQueue(Queue *Q)
{
    for(int i=Q->front;i<Q->rear;++i)
    {
        printf("%d ",Q->base[i]);
    }
    printf("\n");
}
void DeQueue(Queue *Q)
{
    if(Q->front==Q->rear)
        return;
    Q->front++;
}

void GetHead(Queue *Q,ElemType *v)
{
    if(Q->front==Q->rear)
        return;
    *v=Q->base[Q->front];
}

int Length(Queue *Q)
{
    return (Q->rear-Q->front);
}

void ClearQueue(Queue *Q)
{
    Q->front=Q->rear=0;
}

void DestroyQueue(Queue *Q)
{
    free(Q->base);
    Q->base=NULL;
}

int main()
{
    Queue Q;
    InitQueue(&Q);

    for(int i=1;i<=8;++i)
    {
        EnQueue(&Q,i);
    }
    ShowQueue(&Q);
    DeQueue(&Q);
    ShowQueue(&Q);
    //EnQueue(&Q,10);//出队再入队会变成虚空的状态。未充分利用空间，引出循环队列的概念
    //ShowQueue(&Q);

    return 0;
}