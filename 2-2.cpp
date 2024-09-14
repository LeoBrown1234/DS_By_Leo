//单链表实现
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<assert.h>
#include<malloc.h>
#define ElemType int

using namespace std;

typedef struct ListNode
{
    ElemType data;
    struct ListNode *next;
}ListNode;

typedef ListNode *List;


void InitList(List *head)
{
    *head=(ListNode *)malloc(sizeof(ListNode));
    assert(*head !=NULL);
    (*head)->next=NULL;
}
/*
void CreateList(List *head)//尾插法
{
    *head=(ListNode *)malloc(sizeof(ListNode));
    assert(*head!=NULL);
    (*head)->data=1;
    (*head)->next=NULL;
    
    ListNode *p=*head;
    for(int i=2;i<10;++i)
    {
        ListNode *s=(ListNode *)malloc(sizeof(ListNode));
        assert(s!=NULL);
        s->data=i;
        s->next=NULL;

        p->next=s;
        p=s;
    }
}

void CreateList(List *head)//头插法
{
    *head=(ListNode *)malloc(sizeof(ListNode));
    assert(*head!=NULL);
    (*head)->data=1;
    (*head)->next=NULL;
    
    for(int i=2;i<=10;++i)
    {
        ListNode *s=(ListNode *)malloc(sizeof(ListNode));
        assert(s!=NULL);
        s->data=i;

        s->next=*head;
        *head=s;
    }
}
*/

/*
void CreateList(List *head)//带头节点头插
{
    for(int i=1;i<=10;++i)
    {
        ListNode *s=(ListNode *)malloc(sizeof(ListNode));
        s->data=i;
        s->next=(*head)->next;
        (*head)->next=s;
    }
}
*/



void CreateList(List *head)//带尾结点尾插
{
    ListNode *p=*head;
    for(int i=1;i<=10;++i)
    {
        p=p->next=(ListNode *)malloc(sizeof(ListNode));
        assert(p!=NULL);
        p->data=i;
        p->next=NULL;

    }
}






void ShowList(List head)
{
    ListNode *p=head->next;
    while(p!=NULL)
    {
        printf("%d-->",p->data);
        p=p->next;
    }
    printf("NULL.\n");
}

int main()
{
    List mylist;
    InitList(&mylist);
    CreateList(&mylist);
    ShowList(mylist);


    return 0;
}


