using namespace std;

#include <iostream>
#include"stdio.h"
#include"string.h"
#include"stdlib.h"
#include"ctype.h"
#include"math.h"
#include<algorithm>
#define MAXSIZE 1005


typedef struct
{
    int* base;
    int* top;
    int stacksize;
}SqStack;

//S
void InitStack(SqStack &S);
void Push(SqStack &S,int x);
int main()
{
    freopen("in","Y",stdin);
    freopen("out.txt","w",stdout);
    SqStack S;
    int val=0,i=0,j=0,tag=1,m,n,x=0,y=0,tag1=0;
    int a[MAXSIZE]={-1};
    int b[MAXSIZE]={-1};
    fill(a,a+MAXSIZE,-1);
    fill(b,b+MAXSIZE,-1);
    InitStack(S);

    while(val!=-1)
    {
        scanf("%d",&val);
        a[i]=val;
        i++;
    }

    m=i;
    val=0;
    i=0;

    while(val!=-1)
    {
        scanf("%d",&val);
        b[i]=val;
        i++;
    }

    n=i;
    i=0;

    if(m!=n)
    {
        printf("false");
        return 0;
    }

    while(b[x]!=-1)
    {
        tag1=0;
        y=0;
        while(a[y]!=-1)
        {
            if(a[y]==b[x])
            {
                tag1=1;
            }
            y++;
        }

        if(tag1==0)
        {
            printf("false");
            return 0;
        }

        x++;
    }

    while(b[j]!=-1)
    {
        if(a[i]==-1)
        {
            break;
        }
        while(a[i]!=-1)
        {
            if(a[i]!=b[j])
            {
                Push(S,a[i]);
            }else
            {
                i++;
                break;
            }
            i++;
        }
        j++;
    }

    if(b[j]!=-1)
    {
        while(S.top!=S.base)
        {
            S.top--;
            if(*S.top!=b[j])
            {
                tag=0;
            }
            j++;
        }
    }else
    {
        printf("true");
        return 0;
    }

    if(tag==0)
    {
        printf("false");
    }else
    {
        printf("true");
    }

    return 0;

}

void InitStack(SqStack &S)
{
    S.base = new int[MAXSIZE];
    if(!S.base) return;
    S.top=S.base;
    S.stacksize=MAXSIZE;
    return;
}
void Push(SqStack &S,int x)
{
    *S.top=x;
    S.top++;
}

