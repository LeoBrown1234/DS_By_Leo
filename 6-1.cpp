#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>
#include<string.h>

#define ElemType char

typedef struct BinTreeNode
{
	ElemType data;
	struct BinTreeNode *leftChild;
	struct BinTreeNode *rightChild;
}BinTreeNode;

typedef struct BinTree
{
	BinTreeNode *root;
	ElemType     refvalue; //stop flag停止标记/空标记,判断节点指针是否空
}BinTree;


void InitBinTree(BinTree *bt, ElemType ref)
{
	bt->root = NULL;
	bt->refvalue = ref;//引用值,遇到引用值#，就证明表示为NULL，赋值为NULL
}

void CreateBinTree_1(BinTree *bt)//利用重载函数实现
{
	CreateBinTree_1(bt,&(bt->root));
}
void CreateBinTree_1(BinTree *bt, BinTreeNode **t)//二级指针，其实可以用引用
{
	ElemType Item;
	scanf("%c",&Item);
	if(Item == bt->refvalue)//遇到#标记为NULL
		(*t) = NULL;
	else
	{
		(*t) = (BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert((*t) != NULL);
		(*t)->data = Item;
		CreateBinTree_1(bt,&((*t)->leftChild));
		CreateBinTree_1(bt,&((*t)->rightChild));
	}
}

void CreateBinTree_2(BinTree *bt)
{
	CreateBinTree_2(bt,bt->root);
}
void CreateBinTree_2(BinTree *bt, BinTreeNode *&t)//用了引用的方式
{
	ElemType Item;
	scanf("%c",&Item);
	if(Item == bt->refvalue)
		t = NULL;
	else
	{
		t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(t != NULL);
		t->data = Item;
		CreateBinTree_2(bt,t->leftChild);
		CreateBinTree_2(bt,t->rightChild);
	}
}

void CreateBinTree_3(BinTree *bt)
{
	bt->root = CreateBinTree_3_(bt);
}
BinTreeNode* CreateBinTree_3_(BinTree *bt)//返回创建好的树
{
	ElemType Item;
	scanf("%c",&Item);
	if(Item == bt->refvalue)
		return NULL;
	else
	{
		BinTreeNode *t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(t != NULL);
		t->data = Item;
		t->leftChild = CreateBinTree_3_(bt);
		t->rightChild = CreateBinTree_3_(bt);
		return t;
	}
}

void CreateBinTree_4(BinTree *bt, char *str)//用现成字符串来创建树
{
	CreateBinTree_4(bt,bt->root,str);
}
void CreateBinTree_4(BinTree *bt, BinTreeNode *&t, char *&str)
{
	if(*str == bt->refvalue)
		t = NULL;
	else
	{
		t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(t != NULL);
		t->data = *str;
		CreateBinTree_4(bt,t->leftChild,++str);
		CreateBinTree_4(bt,t->rightChild,++str);
	}
}


int main()
{
    BinTree mytree;
    InitBinTree(&mytree,'#'); 
    CreateBinTree_1(&mytree);

    return 0;
}