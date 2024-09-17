// 单循环链表实现
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
    struct Node *next;
} Node, *PNode;

typedef struct List
{
    PNode first;
    PNode last;
    int size;
} List;

// 代码复用，构造一个方法
Node *_buynode(ElemType x)
{
    Node *s = (Node *)malloc(sizeof(Node));
    assert(s != NULL);
    s->data = x;
    s->next = NULL;
    return s;
}

void InitSCList(List *list)
{
    Node *s = (Node *)malloc(sizeof(Node));
    assert(s != NULL);
    list->first = list->last = s;
    list->last->next = list->first;
    list->size = 0;
}

void push_back(List *list, ElemType x)
{
    Node *s = _buynode(x);
    list->last->next = s;
    list->last = s;
    list->last->next = list->first;
    list->size++;
}

void push_front(List *list, ElemType x)
{
    Node *s = _buynode(x);
    s->next = list->first->next;
    list->first->next = s;

    if (list->first == list->last) // 判断插入的是第一个结点，之前没有
    {
        list->last = s;
    }
    list->size++;
}

void show_list(List *list)
{
    Node *p = list->first->next;
    while (p != list->first) // 转一圈停止
    {
        printf("%d-->", p->data);
        p = p->next;
    }
    printf("NULL.\n");
}

void pop_back(List *list) // 尾部删除
{
    if (list->size == 0)
        return;
    Node *p = list->first;
    while (p->next != list->last) // 找到被删除结点的前驱结点（倒数第二个结点）
    {
        p = p->next;
    }
    free(list->last);
    list->last = p;
    list->last->next = list->first;
    list->size--;
}

void pop_front(List *list)
{
    if (list->size == 0)
        return;
    Node *p = list->first->next;
    list->first->next = p->next;
    free(p);
    if (list->size == 1)
    {
        list->last = list->first;
    }
    list->size--;
}

void insert_val(List *list, ElemType x) // 按值插入（从小到大/从大到小）
{
    Node *p = list->first;
    while (p->next != list->last && p->next->data < x)
    {
        p = p->next;
    }

    if (p->next == list->last && p->next->data < x)
    {
        push_back(list, x);
    }
    else
    {
        Node *s = _buynode(x);
        s->next = p->next;
        p->next = s;
        list->size++;
    }
}

Node *find(List *list, ElemType key)
{
    if (list->size == 0)
        return NULL;
    Node *p = list->first->next;
    while (p != list->first && p->data != key) // 顺序不可对换，代码逻辑完全不同，很重要
    {
        p = p->next;
    }
    if (p == list->first)
        return NULL;
    return p;
}

int length(List *list)
{
    return list->size;
}

void delete_val(List *list, ElemType key)
{
    if (list->size == 0)
    {
        return;
    }
    Node *p = find(list, key);
    if (p == NULL)
    {
        printf("The value you want delete is absent.\n");
        return;
    }
    if (p == list->last) // 如果是尾结点删除，用已有方法
    {
        pop_back(list);
    }
    else
    {
        Node *q = p->next; // 直接原地复制一份p->next，然后删除p->next（即q），不必找p前驱
        p->data = q->data;
        p->next = q->next;
        free(q);
        // if(p->next==list->first)
        // list->last=p;
        list->size--;
    }
}

void sort(List *list)
{
    if (list->size == 0 || list->size == 1)
        return;
    Node *s = list->first->next;
    Node *q = s->next;

    list->last->next = NULL;
    list->last = s;
    list->last->next = list->first;

    while (q != NULL)
    {
        s = q;
        q = q->next;

        Node *p = list->first;
        while (p->next != list->last && p->next->data < s->data)
        {
            p = p->next;
        }

        if (p->next == list->last && p->next->data < s->data)
        {
            s->next=list->last->next;
            list->last->next=s;
            list->last=s;
        }
        else
        {
            s->next = p->next;
            p->next = s;
        }
    }
}

void reverse(List *list) // 截取头插
{
    if (list->size == 0 || list->size == 1)
        return;
    Node *p = list->first->next;
    Node *q = p->next;

    list->last->next = NULL;
    list->last = p;
    list->last->next=list->first;

    while (q != NULL)
    {
        p = q; // 一步一步后移
        q = p->next;
        p->next = list->first->next; // 头插入表头
        list->first->next = p;
    }
}

void clear(List *list)
{
    Node *p = list->first->next;
    while (p != list->first)
    {
        list->first->next = p->next;
        free(p);
        p = list->first->next;
    }
    list->last = list->first;
    list->last->next=list->first;
    list->size = 0;
}

void destroy(List *list)
{
    clear(list);
    free(list->first);
    list->first = list->last = NULL;
}

int main()
{
    List mylist;
    InitSCList(&mylist);

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