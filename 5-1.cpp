 //矩阵的压缩存储实现
 #include<stdio.h>
 #include<stdlib.h>//用于exit(1);
 #include<memory.h>
 #define ElemType int
 #define MAXSIZE 100

 typedef struct Triple
 {
    int i;
    int j;
    ElemType e;
 }Triple;

 typedef struct SMatrix//定义一个稀疏矩阵类型
 {
   Triple data[MAXSIZE];
   int mu;//行数
   int nu;//列数
   int tu;//非零元素个数
 }SMatrix;

void PrintMatrix(SMatrix *M)
{
   printf("row = %d  column = %d \n",M->mu,M->nu);
   for(int i=0;i<M->tu;++i)
   {
      printf("(%d, %d, %d)\n",M->data[i].i,M->data[i].j,M->data[i].e);
   }
}

void CreateMatrix(SMatrix *M)
{
   FILE *fp=fopen("Matrix.txt","r");
   if(fp==NULL)
       exit(1);
   fscanf(fp,"%d %d",&M->mu,&M->nu);

   int value;
   int k=0;
   for(int i=0;i<M->mu;++i)
   {
      for(int j=0;j<M->nu;++j)
      {
         fscanf(fp,"%d",&value);
         if(value!=0)
         {
            M->data[k].e=value;
            M->data[k].i=i;
            M->data[k].j=j;
            k++;
         }
      }
   }
   M->tu=k;
   fclose(fp);
}

void CopyMatrix(SMatrix *M,SMatrix *T)
{
    T->mu=M->mu;
    T->nu=M->nu;
    T->tu=M->tu;

    for(int i=0;i<M->tu;i++)
    {
      T->data[i].i=M->data[i].i;
      T->data[i].j=M->data[i].j;
      T->data[i].e=M->data[i].e;
    }
}

// void AddMatrix(SMatrix *M,SMatrix *N,SMatrix *T)
// { 
// }

// void SubMatrix(SMatrix *M,SMatrix *N,SMatrix *T)
// {
// }

// void MulMatrix(SMatrix *M,SMatrix *N,SMatrix *T)
// { 
// }

void TransposeMatrix(SMatrix *M,SMatrix *T)
{
    T->mu=M->mu;
    T->nu=M->nu;
    T->tu=M->tu;

    int q=0;
    if(M->tu!=0)
    {
      for(int col=0;col<M->nu;++col)
      {
         for(int p=0;p<M->tu;++p)
         {
            if(M->data[p].j==col)
            {
               T->data[q].i=M->data[p].j;
               T->data[q].j=M->data[p].i;
               T->data[q].e=M->data[p].e;
               q++;
            }
         }
      }
    }
}

int main()
{
   SMatrix sm,sm1;
   memset(&sm,0,sizeof(sm));
   CreateMatrix(&sm);
   PrintMatrix(&sm);

   TransposeMatrix(&sm,&sm1);
   PrintMatrix(&sm1);


   return 0;
}


