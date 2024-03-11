#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL mod=1e9+7;
const int N=2e5+5;
int n,m;
struct P{
    int v;
    bool isbridge;
};
map<int,P> G[N];
int cnt=0;
int low[N],dfn[N];
int dfc;
void tarjan(int x,int f){
    low[x]=dfn[x]=++dfc;
    for(auto& [ne,j]:G[x]){
        if(!dfn[ne]){
            tarjan(ne,x);
            low[x]=min(low[x],low[ne]);
            if(low[x]>dfn[x]){
                j.isbridge= true;
                G[ne][x].isbridge=true;
                cnt++;
            }
        }else if(dfn[ne]<dfn[x]&&ne!=f){
            low[x]=min(low[x],dfn[ne]);
        }
    }
}

void solve(){
    cin>>n>>m;
    dfc=0;
    cnt=0;
    for(int i=1;i<=n;i++)G[i].clear(),low[i]=dfn[i]=0;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        G[u][v]={w,false};
        G[v][u]={w,false};
    }
    tarjan(1,0);
    int x,y;
    int minn=INT_MAX;
    for(int i=1;i<=n;i++){
        for(auto& [ne,j]:G[i]){
            if(!j.isbridge&&j.v<minn){
                minn=j.v;
                x=i;
                y=ne;
            }
        }
    }
    G[x][y].isbridge=1;
    G[y][x].isbridge=1;
    queue<int> q;
    q.push(x);
    vector<int> has(n+1);
    has[x]= -1;
    while(!q.empty()){
        int tp=q.front();q.pop();
        for(auto& [ne,j]:G[tp]){
            if(j.isbridge)continue;
            if(!has[ne]){
                has[ne]=tp;
                q.push(ne);
            }
        }
    }
    vector<int> ans;
    int t=y;
    while(t!=-1){
        ans.push_back(t);
        t=has[t];
    }
    cout<<minn<<' '<<ans.size()<<'\n';
    for(int i:ans)cout<<i<<' ';
    cout<<'\n';
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int _;
    cin>>_;
    while(_--)solve();
}