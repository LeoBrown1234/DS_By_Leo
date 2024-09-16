//静态链表实现
/*
L->next=NULL;等价于游标cur=-1；(意思是下一节点的数组下标为-1)。
查找结点时只能从头出发寻找,T(n)=O(n)。
插入时扫描数组，找到空闲节点存放下一节点数据，
需要把前驱节点的-1改为本节点的下标位置，本节点/新插入节点的下标/游标cur改为-1。
空闲节点下标常设置一个标志值，比如-2。
0下标表示的是头节点。

此处讲述了一个头插法的表示模式
head [0]是头节点位置下标cur
pool [1]是空闲节点位置下标cur
*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<assert.h>
#include<malloc.h>
#define ElemType char
#define MAX_SIZE 20

using namespace std;

typedef struct ListNode
{
    ElemType data;
    int cur;//游标，相当于next指针
}ListNode;

typedef ListNode StaticList[MAX_SIZE];


void InitSList(StaticList &space)//构建一个成型的空集静态链表
{
    for(int i=1;i<MAX_SIZE-1;++i)
    {
        space[i].cur=i+1;
    }
    space[MAX_SIZE-1].cur=0;
    space[0].cur=-1;
}

int Malloc_SL(StaticList &space)//pool的实现，标记下一个空闲位置的cur下标
{
    int i=space[1].cur;
    if(space[1].cur !=0)
        space[1].cur=space[i].cur;
    return i;
}

void Insert(StaticList &space,ElemType x)
{
    int i=Malloc_SL(space);
    if(i==0)//回到head，满了
    {
        printf("Space request failed.We need more memory.\n");
        return;
    }
    space[i].data=x;
    if(space[0].cur==-1)
    {
        space[i].cur=-1;
    }
    else
    {
        space[i].cur=space[0].cur;
    }
    space[0].cur=i;
}

void ShowSList(StaticList &space)
{
    int i=space[0].cur;
    while(i!=-1)
    {
        printf("%c-->",space[i].data);
        i=space[i].cur;//p=p->next;
    }
    printf("NULL.\n");
}

void Free_SL(StaticList &space,int k)
{
    space[k].cur=space[1].cur;
    space[1].cur=k;
}


void Delete(StaticList &space)//删除时对应空间应该回收,头删
{
    int i=space[0].cur;
    space[0].cur=space[i].cur;

    Free_SL(space,i);
    //space[i].cur=space[1].cur;
    //space[1].cur=i;
}


int main()
{
    StaticList SL;
    InitSList(SL);

    for(int i=0;i<5;++i)
    {
        Insert(SL,'A'+i);
    }

    ShowSList(SL);
    Delete(SL);
    ShowSList(SL);

    return 0;
}