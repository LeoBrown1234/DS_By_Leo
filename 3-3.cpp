//栈的应用
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>
#include<iostream>


using namespace std;

//#define ElemType int    //在进制转换时开启
#define ElemType char     //在栈括号匹配时开启
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
        printf("%d",s->base[i]);
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

// void Convert_8(int value)//进制转换
// {
//     SeqStack st;
//     InitStack (&st);
//     int v;
//     while(value)
//     {
//         Push(&st,value%8);
//         value/=8;
//     }
//     printf("Convert is:\n");
//     //Show(&st);
//     while(!IsEmpty(&st))
//     {
//         GetTop(&st,&v);
//         Pop(&st);
//         printf("%d",v);
//     }    
//     printf("\n");
// }

// bool Check(const char *str)//栈的括号匹配检测,此处的const char* 类型是自己修改，debug了警告，因为C++不允许修改字符串常量，具体问询chatgpt
// {
//     SeqStack st;
//     InitStack(&st);

//     char v;

//     while(*str!='\0')
//     {
//         if(*str=='[' || *str=='(')
//         {
//             Push(&st,*str);
//         }
//         else if(*str==']')
//         {
//             GetTop(&st,&v);
//             if(v!='[')
//             {
//                 return false;
//             }
//             Pop(&st);
//         }
//         else if(*str==')')
//         {
//             GetTop(&st,&v);
//             if(v!='(')
//             {
//                 return false;
//             }
//             Pop(&st);
//         }
//         ++str;
//     }
//     return IsEmpty(&st);
// }


void Print(SeqStack *s)//3,栈的逆向打印
{
    for(int i=0;i<s->top;++i)
    {
        printf("%c",s->base[i]);
    }
    printf("\n");
}

//测试数据符：whle##ilr#e(s#*s)    outcja@putchar(*s=#++)   $
void LineEdit()//行编辑程序，但是它在VScode里没法交互输入，做一个简单版本的
{
    SeqStack st;
    InitStack(&st);
    char ch=getchar();
    while(ch!='$')
    {
            while(ch!='$' && ch!='\n')
            {
                switch(ch)
                {
                    case '#':
                        Pop(&st);
                        break;

                    case '@':
                        Clear(&st);
                        break;

                    default:
                        Push(&st,ch);
                        break;
                }
                ch=getchar();
            }
            Print(&st);
            ch=getchar();
    }
    Destroy(&st);
}

void LineEdit_VScode(const char *str)//行编辑程序，但是它在VScode里没法交互输入，做一个简单版本的
{
    SeqStack st;
    InitStack(&st);
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];

        switch(ch) {
            case '#':
                Pop(&st);
                break;
            case '@':
                Clear(&st);
                break;
            default:
                Push(&st, ch);
                break;
        }
    }
    Print(&st);
}

int main()
{
    // //1进制转换部分
    // int value=47183;
    // Convert_8(value);

    // //2栈括号匹配部分
    // const char *str="[([][])]";
    // bool flag=Check(str);
    // if(flag)
    // {
    //     printf("Match signal!\n");
    // }
    // else
    // {
    //     printf("Error!No match!\n");
    // }

    //3行编辑程序部分
    //如果能够交互则代码为：
    //LineEdit();
    const char *str="whli##ilr#e(s#*s)";
    LineEdit_VScode(str);
    
    return 0;
}
