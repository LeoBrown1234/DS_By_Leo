//链栈的关键实现，就是受限的单链表
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>
#include<iostream>

using namespace std;

#define ElemType int

typedef struct StackNode
{
    ElemType data;
    struct StackNode *next;
}StackNode;

typedef StackNode *LinkStack;

void InitStack(LinkStack *s)//二级指针，先NULL，表示空栈
{
    *s=NULL;
}

void Push(LinkStack *s,ElemType x)
{
    StackNode *t=(StackNode *)malloc(sizeof(StackNode));
    assert(t!=NULL);
    t->data=x;
    if(*s==NULL)
    {
        *s=t;
        t->next=NULL;
    }
    else
    {
        t->next=*s;
        *s=t;
    }
}

void Show(LinkStack *s)
{
    StackNode *p=*s;
    while(p!=NULL)
    {
        printf("%d\n",p->data);
        p=p->next;
    }
    printf("\n");
}

void Pop(LinkStack *s)
{
    StackNode *p=*s;
    *s=p->next;
    free(p);
    p=NULL;
}


int main()
{
    LinkStack st;
    InitStack(&st);
    for(int i=1;i<=5;++i)
    {
        Push(&st,i);
    }
    Show(&st);
    Pop(&st);
    Show(&st);

    return 0;
}
