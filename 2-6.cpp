//双链表的实现
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
}Node,*PNode;

typedef struct List
{
    PNode first;
    PNode last;
    int size;
}List;

void InitDList(List *list)
{
    Node *s=(Node *)malloc(sizeof(Node));
    assert(s!=NULL);
    list->first=list->last=s;
    list->last->next=NULL;
    list->first->prio=NULL;
    list->size=0;
}

int main()
{
    List mylist;
    InitDList(&mylist);

        int select=1;
    ElemType Item;
    Node *p=NULL;

    while(select)
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
        scanf("%d",&select);
        switch(select)
        {
            case 1:
            // printf("Please enter the number you want insert(-1 means end):\n");
            // while(scanf("%d",&Item),Item!=-1)
            // {
            //     push_back(&mylist,Item);
            // }
                break;

            case 2:
            // printf("Please enter the number you want insert(-1 means end):\n");
            // while(scanf("%d",&Item),Item!=-1)
            // {
            //     push_front(&mylist,Item);
            // }
                break;

            case 3:
                // show_list(&mylist);
                // break;
            case 4:
                // pop_back(&mylist);
                // break;
            case 5:
                // pop_front(&mylist);
                // break;
            case 6:
                // printf("Please enter the insert value:\n");
                // scanf("%d",&Item);
                // insert_val(&mylist,Item);
                break;
            case 7:
                // printf("Please enter the data you want find:\n");
                // scanf("%d",Item);
                // p=find(&mylist,Item);
                // if(p==NULL)
                // {
                //     printf("The data you find is absent.\n");
                // }
                break;
            case 8:
                // printf("The LinkList length is:%d \n",length(&mylist));
                break;
            case 9:
                // printf("Please enter the value you want delete:\n");
                // scanf("%d",&Item);
                // delete_val(&mylist,Item);
                break;

            case 10: //插入排序
                // sort(&mylist);
                break;

            case 11:
                // reverse(&mylist);
                break;

            case 12:
                // clear(&mylist);
                break;

            case 13:
                // destroy(&mylist);
                break;

            default:
                printf("The number is wrong, type again.\n");
                break;

        }

    }
    // destroy(&mylist);

    return 0;
}