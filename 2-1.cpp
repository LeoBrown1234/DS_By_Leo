/*
结构体功能的理解才是核心的问题
*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<assert.h>
#define SEQLIST_INIT_SIZE 8
using namespace std;

typedef int ElemType;
typedef struct SeqList
{
    ElemType *base;
    int capacity;//结构体空间容量
    int size;//所存的大小
}SeqList;

void InitSeqList(SeqList *list)
{
    list->base=(ElemType*)malloc(sizeof(ElemType)*SEQLIST_INIT_SIZE);
    assert(list->base!=NULL);//判断顺序表创建成功
    list->capacity=SEQLIST_INIT_SIZE;
    list->size=0;
}

void push_back(SeqList *list,ElemType x)//尾部插入
{
    if(list->size>=list->capacity)
    {
        printf("SeqList has no space,can't insert.\n");
        return;
    }
    list->base[list->size]=x;
    list->size++;
}

void push_front(SeqList *list,ElemType x)//头插法
{
    if(list->size>=list->capacity)
    {
        printf("SeqList has no space,can't insert.\n");
        return;
    }

    for(int i=list->size;i>0;--i)
    {
        list->base[i]=list->base[i-1];
    }
    list->base[0]=x;
    list->size++;

}

void show_list(SeqList *list)//打印数据
{
    for(int i=0;i<list->size;++i)
    {
        printf("%d",list->base[i]);
    }
    printf(" \n");

}

void pop_back(SeqList *list)
{
    if(list->size==0)
    {
        printf("SeqList is empty,can't delete.");
        return;
    }
    list->size--;
}

void pop_front(SeqList *list)
{
    if(list->size==0)
    {
        printf("SeqList is empty,can't delete.");
        return;
    }
    for(int i=0;i<list->size-1;++i)
    {
        list->base[i]=list->base[i+1];
    }
    list->size--;
}

void insert_pos(SeqList *list,int pos,ElemType x)
{
    if(pos<0||pos>list->size)
    {
        printf("Insert position is ilegal!\n");
        return;
    }
   
    for(int i=list->size;i>pos;--i)
    {
        list->base[i]=list->base[i-1];
    }
    list->base[pos]=x;
    list->size++;
    
}

int find(SeqList *list,ElemType key)
{
    for(int i=0;i<list->size;++i)
    {
        if(list->base[i]==key)
        {
            return i;
        }
    }
    return -1;
}

int length(SeqList *list)
{
    return list->size;
}

void delete_pos(SeqList *list,int pos)
{
    if(pos<0||pos>=list->size)
    {
        printf("Delete location is ilegal.");
        return;
    }
    for(int i=pos;i<list->size-1;++i)
    {
        list->base[i]=list->base[i+1];
    }
    list->size--;
}

void delete_val(SeqList *list,ElemType key)
{
    int pos=find(list,key);
    if(pos==-1)
    {
        printf("Value is not exist.");
        return;
    }
    delete_pos(list,pos);
}

void sort(SeqList *list)
{
    for(int i=0;i<list->size-1;++i)
    {
        for(int j=0;j<list->size-i-1;++j)
        if(list->base[j]>list->base[j+1])
        {
            ElemType tmp=list->base[j];
            list->base[j]=list->base[j+1];
            list->base[j+1]=tmp;
        }
    }
}

void reverse(SeqList *list)//前后对调,low\high
{
    if(list->size==0||list->size==1)
    {
        return;
    }
    int low=0;
    int high=list->size-1;
    ElemType tmp;
    while(low<high)
    {
        tmp=list->base[low];
        list->base[low]=list->base[high];
        list->base[high]=tmp;
        low++;
        high--;
    }
}

void clear(SeqList*list)
{
    list->size=0;
}

void destroy(SeqList *list)
{
    free(list->base);
    list->base=NULL;
    list->capacity=0;
    list->size=0;
}


int main()
{
    SeqList mylist;
    InitSeqList(&mylist);
    ElemType Item;
    int pos;
    int select=1;
   
    while(select)
    {
        printf("*******************************************\n");
        printf("* [1]  push_back          [2] push_front  *\n");
        printf("* [3]  show_list          [4] pop_back    *\n");
        printf("* [5]  pop_front          [6] insert_pos  *\n");
        printf("* [7]  find               [8] length      *\n");
        printf("* [9]  delete_pos         [10] delete_val *\n");
        printf("* [11] sort               [12] reverse    *\n");
        printf("* [13] clear              [14] destroy    *\n");
        printf("* [0] quit_system                         *\n");
        printf("*******************************************\n");
        printf("Chose a item you want\n");
        scanf("%d",&select);
        if(select == 0)
            break;
        switch(select)
        {
            case 1:
                printf("Please enter the insert number(-1 means end.):\n");
                while(scanf("%d",&Item),Item!=-1)//知识点：C语言的逗号表达式/多个同时输入，中间只能用空格分开
                {
                    push_back(&mylist,Item);
                }
                break;

            case 2:
                printf("Please enter the insert number(-1 means end.):\n");
                while(scanf("%d",&Item),Item!=-1)
                {
                    push_front(&mylist,Item);
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
                printf("Please enter the data:\n");
                scanf("%d",&Item);
                printf("Please enter the location you want:\n");
                scanf("%d",&pos);
                insert_pos(&mylist,pos,Item);
                break;

            case 7:
                printf("Please enter the number you want find:\n");
                scanf("%d",&Item);
                pos=find(&mylist,Item);
                if(pos==-1)//没找到-1
                {
                    printf("Data %d can't find in this SeqList.\n",Item);
                }
                else
                {
                    printf("Data %d is in:mylist[%d].\n",Item,pos);
                }
                break;

            case 8:
                printf("SeqList length is:%d\n",length(&mylist));

            case 9://按位置删除
                printf("Please enter which location you want delete:");
                scanf("%d",&pos);
                delete_pos(&mylist,pos);
                break;

            case 10:
                printf("Please enter the value you want delete:");
                scanf("%d",&Item);
                delete_val(&mylist,Item);
                break;

            case 11:
                sort(&mylist);
                break;

            case 12:
                reverse(&mylist);
                break;
            case 13:
                clear(&mylist);
                break;
            case 14:
                destroy(&mylist);
                break;



            default:
                printf("Wrong type try again.\n");
                break;

        }

    }
    
    return 0;
}



