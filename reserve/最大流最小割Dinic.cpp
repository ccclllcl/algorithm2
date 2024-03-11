#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=1e6;
const int M=1e6;
int m,n,s,T;
struct E{
    int v,ne;
    LL c;
};
E e[M*2+5];
int cnt=1;
int h[N],d[N],cur[N];
void add(int a,int b,LL c){
    e[++cnt]={b,h[a],c};
    h[a]=cnt;
}
bool bfs(){
    fill(d+1,d+1+n,0);
    queue<int> q;
    q.push(s);
    d[s]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=h[u];i;i=e[i].ne){
            int v=e[i].v;
            if(!d[v]&&e[i].c){
                d[v]=d[u]+1;
                q.push(v);
                if(v==T)return true;
            }
        }
    }
    return false;
}
LL dfs(int u,LL mf){
    if(u==T)return mf;
    LL sum=0;
    for(int i=cur[u];i;i=e[i].ne){
        cur[u]=i;
        int v=e[i].v;
        if(d[v]==d[u]+1&&e[i].c){
            LL f=dfs(v,min(mf,e[i].c));
            e[i].c-=f;
            e[i^1].c+=f;
            sum+=f;
            mf-=f;
            if(!mf)break;
        }
    }
    if(!sum)d[u]=0;
    return sum;
}
LL dinic(){
    LL flow=0;
    while(bfs()){
        for(int i=1;i<=n;i++)cur[i]=h[i];
        flow+=dfs(s,1e18);
    }
    return flow;
}
bool vis[N];
void mincut(int u){
    vis[u]=1;
    for(int i=h[u];i;i=e[i].ne){
        int v=e[i].v;
        if(!vis[v]&&e[i].c)mincut(v);
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m>>s>>T;
    for(int i=0;i<m;i++){
        int u,v;
        LL c;
        cin>>u>>v>>c;
        add(u,v,c);
        add(v,u,0);
    }
    LL ans=dinic();
    cout<<ans;
}