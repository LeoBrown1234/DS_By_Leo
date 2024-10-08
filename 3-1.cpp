#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>
#include<iostream>

using namespace std;

#define ElemType int
#define STACK_INIT_SIZE 8
#define STACK_INC_SIZE  3

typedef struct SeqStack
{
    ElemType *base;
    int capacity;
    int top;
}SeqStack;

bool Inc(SeqStack *s)
{
    ElemType *newbase=(ElemType *)realloc(s->base,sizeof(ElemType)*(s->capacity+STACK_INC_SIZE));
    if(newbase==NULL)
    {
        printf("Sorry our memory is empty! We can't getting more space.\n");
        return false;
    }
    s->base=newbase;
    s->capacity+=STACK_INC_SIZE;
    return true;
}

void InitStack(SeqStack *s)
{
    s->base=(ElemType *)malloc(sizeof(ElemType)*STACK_INIT_SIZE);
    assert(s->base!=NULL);
    s->capacity=STACK_INIT_SIZE;
    s->top=0;
}

bool IsFull(SeqStack *s)
{
    return s->top==s->capacity;
}

bool IsEmpty(SeqStack *s)
{
    return s->top==0;
}

void Push(SeqStack *s,ElemType x)
{
    if(IsFull(s) && !Inc(s))//空间满了就尝试增加栈空间，增加失败证明没空间了，就失败了
    {
        printf("Stack space is full,  %d can't push.\n",x);
        return;
    }
    s->base[s->top++]=x;
}
void Pop(SeqStack *s)
{
    if(IsEmpty(s))
    {
        printf("Stack space is empty,can't pop stack.");
    }
    s->top--;
}

bool GetTop(SeqStack *s,ElemType *v)//本例中top指示的位置是能够存放空空间的栈的位置
{
    if(IsEmpty(s))
    {
        printf("Stack is empty,can't get top element.");
        return false;
    }
    *v=s->base[s->top-1];
    return true;
}

void Show(SeqStack *s)
{
     for(int i=s->top-1;i>=0;--i)
     {
        printf("%d\n",s->base[i]);
     }
     printf("\n");
}

int Length(SeqStack *s)
{
    return s->top;
}

void Clear(SeqStack *s)
{
    s->top=0;
}

void Destroy(SeqStack *s)
{
    free(s->base);
    s->base=NULL;
    s->capacity=s->top=0;
}


int main()
{
    SeqStack st;
    InitStack(&st);

    ElemType v;

    for(int i=1;i<=10;++i)
    {
        Push(&st,i);
    }

    Show(&st);
    GetTop(&st,&v);
    printf("pop v = %d .\n",v);
    Pop(&st);
    Show(&st);

    return 0;
}