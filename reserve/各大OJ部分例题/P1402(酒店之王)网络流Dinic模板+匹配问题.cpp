#include<bits/stdc++.h>
#define LL long long
const LL INF=1e9;
const LL inf=1e9;
using namespace std;
const int N=2e5+5;
struct E{
    int v;
    LL ca;
};
E e[N];
int nn;
int s,t;
int cnt=1;
vector<int> G[N];
int d[N];
int cur[N];
void add(int a,int b,LL c){
    e[++cnt]={b,c};
    G[a].push_back(cnt);
    e[++cnt]={a,0};
    G[b].push_back(cnt);
}
bool bfs(){
    for(int i=1;i<=nn;i++)d[i]=0;
    d[s]=1;
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int tp=q.front();q.pop();
        for(int j:G[tp]){
            if(!e[j].ca)continue;
            int ne=e[j].v;
            if(!d[ne]) { d[ne] = d[tp] + 1, q.push(ne);if(ne==t)return true; }
        }
    }
    return false;
}
LL dfs(int x,LL mf){
    if(x==t)return mf;
    LL sum=0;
    for(int& i=cur[x];i<G[x].size();i++){
        int I=G[x][i];
        auto v=e[I];
        if(d[v.v]==d[x]+1&&v.ca){
            LL f=dfs(v.v,min(mf, v.ca));
            e[I].ca-=f;
            e[I^1].ca+=f;
            sum+=f;
            mf-=f;
            if(!mf)break;
        }
    }
    if(!sum)d[x]=0;
    return sum;
}
LL dinic(){
    LL flow=0;
    while(bfs()){
        for(int i=1;i<=nn;i++)cur[i]=0;
        flow+=dfs(s,INF);
    }
    return flow;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int a,b,c;
    cin>>a>>b>>c;
    nn=2+a*2+b+c;
    s=1;
    t=nn;
    for(int i=2;i<=b+1;i++)add(s,i,1);
    for(int i=2+a*2+b;i<nn;i++)add(i,t,1);
    for(int i=1;i<=a;i++)add(i+1+b,i+1+b+a,1);
    for(int i=1;i<=a;i++){
        for(int j=1;j<=b;j++){
            int v;
            cin>>v;
            if(v){
                add(j+1,i+1+b,1);
            }
        }
    }
    for(int i=1;i<=a;i++){
        for(int j=1;j<=c;j++){
            int v;
            cin>>v;
            if(v){
                add(i+1+b+a,a*2+b+1+j,1);
            }
        }
    }
    LL res=dinic();
    cout<<res;
}