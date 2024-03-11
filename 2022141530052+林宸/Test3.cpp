#include"stdio.h"
#include"stdlib.h"
#define MaxVertexNum 100     //定义最大顶点数
typedef struct{
    char vexs[MaxVertexNum];        //顶点表
    int edges[MaxVertexNum][MaxVertexNum];   //邻接矩阵
    int n, e;          //图中的顶点数n和边数e
}MGraph;
//=========建立邻接矩阵=======
void CreatMGraph(MGraph &G)
{
    int i,j,k;
    char a;
    printf("Input VertexNum(n) and EdgesNum(e): ");
    scanf("%d,%d",&G.n,&G.e);         //输入顶点数和边数
    scanf("%c",&a);
    printf("Input Vertex string:");
    for(i=0;i<G.n;i++)
    {
        scanf("%c",&a);
        G.vexs[i]=a;             //读入顶点信息，建立顶点表
    }
    for(i=0;i<G.n;i++)
        for(j=0;j<G.n;j++)
            G.edges[i][j]=0;    //初始化邻接矩阵
    printf("Input edges,Creat Adjacency Matrix\n");
    for(k=0;k<G.e;k++) {       //读入e条边，建立邻接矩阵
        scanf("%d%d",&i,&j);        //输入边（Vi，Vj）的顶点序号
        G.edges[i][j]=1;
        G.edges[j][i]=1;
    }
}

//=========定义标志向量，为全局变量=======
typedef enum{FALSE,TRUE} Boolean;
Boolean visited[MaxVertexNum];

//========DFS：深度优先遍历的递归算法======
void DFSM(MGraph & G,int i)
{
    printf("%c",G.vexs[i]);
    visited[i]= TRUE;
    for(int j=0;j<G.n;j++) {
        if (!visited[j]&&G.edges[i][j]) {
            DFSM(G, j);
        }
    }
}
void DFS(MGraph &G)
{
    int i;
    for(i=0;i<G.n;i++)
        visited[i]=FALSE;            //标志向量初始化
    for(i=0;i<G.n;i++)
        if(!visited[i])              //Vi未访问过
            DFSM(G,i);               //以Vi为源点开始DFS搜索
}
//===========BFS：广度优先遍历=======
void BFS(MGraph &G, int k)
{   //以Vk为源点对用邻接矩阵表示的图G进行广度优先搜索
    int i,j,f=0,r=0;
    int cq[MaxVertexNum];        //定义队列
    for(i=0;i<G.n;i++)
        visited[i]=FALSE;             //标志向量初始化
    for(i=0;i<G.n;i++)
        cq[i]=-1;                    //队列初始化
    printf("%c",G.vexs[k]);     //访问源点Vk
    visited[k]=TRUE;
    cq[r]=k; //Vk已访问，将其入队。
    r++;
    while(cq[f]!=-1 && f<G.n) {
        i=cq[f]; f=f+1;
        for(j=0;j<G.n;j++){
            if(!visited[j]&&G.edges[i][j]){
                printf("%c",G.vexs[j]);
                cq[r++]=j;
                visited[j]=TRUE;
            }
        }
    }
}
//==========main=====
int main()
{
    MGraph G;
    CreatMGraph(G);          //建立邻接矩阵
    printf("Print Graph DFS: ");
    DFS(G);                  //深度优先遍历
    printf("\n");
    printf("Print Graph BFS: ");
    BFS(G,3);             //以序号为3的顶点开始广度优先遍历
    printf("\n");
}
