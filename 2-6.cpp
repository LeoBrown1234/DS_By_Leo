// 双链表的实现
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <iostream>
using namespace std;

#define ElemType int

typedef struct Node
{
    ElemType data;
    struct Node *prio;
    struct Node *next;
} Node, *PNode;

typedef struct List
{
    PNode first;
    PNode last;
    int size;
} List;

Node *_buynode(ElemType x)
{
    Node *s = (Node *)malloc(sizeof(Node));
    assert(s != NULL);
    s->data = x;
    s->next = s->prio = NULL;
    return s;
}

void InitDList(List *list)
{
    Node *s = (Node *)malloc(sizeof(Node));
    assert(s != NULL);
    list->first = list->last = s;
    list->last->next = NULL;
    list->first->prio = NULL;
    list->size = 0;
}

void push_back(List *list, ElemType x)
{
    Node *s = _buynode(x);
    s->prio = list->last;
    list->last->next = s;
    list->last = s;
    list->size++;
}

void push_front(List *list, ElemType x) // 头插，先连接再断开
{
    Node *s = _buynode(x);
    if (list->first == list->last)
    {
        // s->prio=list->first;
        // list->first->next=s;
        list->last = s;
    }
    else
    {
        s->next = list->first->next;
        s->next->prio = s;
        // s->prio=list->first;
        // list->first->next=s;
    }
    s->prio = list->first;
    list->first->next = s;
    list->size++;
}

void show_list(List *list)
{
    Node *p = list->first->next;
    while (p != NULL)
    {
        printf("%d-->", p->data);
        p = p->next;
    }
    printf("NULL.\n");
}

void pop_back(List *list)
{
    if (list->size == 0)
        return;

    Node *p = list->first;
    while (p->next != list->last)
    {
        p = p->next;
    }
    free(list->last);
    list->last = p;
    list->last->next = NULL;
    list->size--;
}

void pop_front(List *list)
{
    if (list->size == 0)
        return;
    Node *p = list->first->next;
    if (list->first->next == list->last)
    {
        list->last = list->first;
        list->last->next = NULL;
    }
    else
    {
        p->next->prio = list->first;
        list->first->next = p->next;
    }
    free(p);
    list->size--;
}

void insert_val(List *list, ElemType x)
{
    Node *p = list->first;
    while (p->next != NULL && p->next->data < x)
    {
        p = p->next;
    }
    if (p->next == NULL)
    {
        push_back(list, x);
    }
    else
    {
        Node *s = _buynode(x);
        s->next = p->next;
        s->next->prio = s;
        s->prio = p;
        p->next = s;
        list->size++;
    }
}

Node *find(List *list, ElemType key)
{
    Node *p = list->first->next;
    while (p != NULL && p->data != key)
    {
        p = p->next;
    }
    return p;
}
int length(List *list)
{
    return list->size;
}

void delete_val(List *list, ElemType key)
{
    if (list->size == 0)
        return;
    Node *p = find(list, key);
    if (p == NULL)
    {
        printf("The delete value is not exist.\n");
        return;
    }
    if (p == list->last)
    {
        list->last = p->prio;
        list->last->next = NULL;
    }
    else
    {
        p->next->prio = p->prio;
        p->prio->next = p->next;
    }
    free(p);
    list->size--;
}

void sort(List *list)
{
    if (list->size == 0 || list->size == 1)
        return;
    Node *s = list->first->next;
    Node *q = s->next;

    list->last = s;
    list->last->next = NULL;

    while (q != NULL)
    {
        s = q;
        q = q->next;

        Node *p = list->first;
        while (p->next != NULL && p->next->data < s->data)
        {
            p = p->next;
        }
        if (p->next == NULL)
        {
            s->next = NULL;
            s->prio = list->last;
            list->last->next = s;
            list->last = s;
        }
        else
        {
            s->next = p->next;
            s->next->prio = s;
            s->prio = p;
            p->next = s;
        }
    }
}

void reverse(List *list)
{
    if (list->size == 0 || list->size == 1)
        return;
    Node *p = list->first->next;
    Node *q = p->next;
    list->last = p;
    list->last->next = NULL;
    while (q != NULL)
    {
        p = q;
        q = q->next;
        p->next = list->first->next;
        p->next->prio = p;
        p->prio = list->first;
        list->first->next = p;
    }
}

void clear(List *list)
{
    if (list->size == 0)
        return;
    Node *p = list->first->next;

    while (p != NULL)
    {
        if (p == list->last)
        {
            list->last = list->first;
            list->last->next = NULL;
        }
        else
        {
            p->next->prio = list->first;
            list->first->next = p->next;
        }
        free(p);
        p=list->first->next;
    }
    list->size = 0;
}

void destroy(List *list)
{
    clear(list);
    free(list->first);
    list->first=list->last=NULL;
}

int main()
{
    List mylist;
    InitDList(&mylist);

    int select = 1;
    ElemType Item;
    Node *p = NULL;

    while (select)
    {
        printf("****************************************************************\n");
        printf("*[1] push_back**********************[2] push_front**************\n");
        printf("*[3] show_list**********************[4] pop_back****************\n");
        printf("*[5] pop_front**********************[6] insert_val**************\n");
        printf("*[7] find***************************[8] length******************\n");
        printf("*[9] delete_val*********************[10]sort********************\n");
        printf("*[11]reverse************************[12]clear*******************\n");
        printf("*[13]destroy************************[0] quit_system*************\n");
        printf("****************************************************************\n");
        printf("Choose a item you want:\n");
        scanf("%d", &select);
        switch (select)
        {
        case 1:
            printf("Please enter the number you want insert(-1 means end):\n");
            while (scanf("%d", &Item), Item != -1)
            {
                push_back(&mylist, Item);
            }
            break;

        case 2:
            printf("Please enter the number you want insert(-1 means end):\n");
            while (scanf("%d", &Item), Item != -1)
            {
                push_front(&mylist, Item);
            }
            break;

        case 3:
            show_list(&mylist);
            break;
        case 4:
            pop_back(&mylist);
            break;
        case 5:
            pop_front(&mylist);
            break;
        case 6:
            printf("Please enter the insert value:\n");
            scanf("%d", &Item);
            insert_val(&mylist, Item);
            break;
        case 7:
            printf("Please enter the data you want find:\n");
            scanf("%d", Item);
            p = find(&mylist, Item);
            if (p == NULL)
            {
                printf("The data you find is absent.\n");
            }
            break;
        case 8:
            printf("The LinkList length is:%d \n", length(&mylist));
            break;
        case 9:
            printf("Please enter the value you want delete:\n");
            scanf("%d", &Item);
            delete_val(&mylist, Item);
            break;

        case 10: // 插入排序
            sort(&mylist);
            break;

        case 11:
            reverse(&mylist);
            break;

        case 12:
            clear(&mylist);
            break;

        case 13:
            destroy(&mylist);
            break;

        default:
            printf("The number is wrong, type again.\n");
            break;
        }
    }
    destroy(&mylist);

    return 0;
}