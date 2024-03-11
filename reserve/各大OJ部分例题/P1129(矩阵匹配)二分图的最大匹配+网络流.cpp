#include<bits/stdc++.h>
#define LL long long
const LL inf=1e18;
using namespace std;
const int N=2e5+5;
int n;
struct E{
    int v;
    LL ca;
};
E e[N];
int s,t;
int cnt=1;
vector<int> G[N];
int d[N];
int cur[N];
void add(int a,int b,int c){
    e[++cnt]={b,c};
    G[a].push_back(cnt);
}
bool bfs(){
    for(int i=1;i<=2*n+2;i++)d[i]=0;
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
    if(x==2*n+2)return mf;
    LL sum=0;
    for(int& i=cur[x];i<G[x].size();i++){
        auto v=e[G[x][i]];
        int I=G[x][i];
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
        for(int i=1;i<=2*n+2;i++)cur[i]=0;
        flow+=dfs(s,inf);
    }
    return flow;
}
void solve(){
    cin>>n;
    cnt=1;
    s=2*n+1;
    t=2*n+2;
    for(int i=1;i<=2*n+2;i++)G[i].clear();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int v;
            cin>>v;
            if(v){
                add(i,n+j,1);
                add(n+j,i,0);
            }
        }
    }
    for(int i=1;i<=n;i++)add(s,i,1),add(i,s,0),
                add(i+n,t,1),add(t,i+n,0);
    LL res=dinic();
    if(res==n){
        cout<<"Yes\n";
    }else cout<<"No\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int _;
    cin>>_;
    while(_--)solve();
}