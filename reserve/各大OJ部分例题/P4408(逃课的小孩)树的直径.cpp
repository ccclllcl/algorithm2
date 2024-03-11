#include<bits/stdc++.h>
#define qwe(i,a,b) for(int i=a;i<=b;i++)
#define itn int
#define asn ans
#define reisze resize
#define LL long long
using namespace std;
constexpr int N=3e5+5;
constexpr LL inf=1e12;
struct P{
    int x;
    LL l;
    bool operator<(P o)const{
        return l>o.l;
    }
};
vector<P> G[N];
LL dis[N];
LL disy[N];
int x,y;
int n;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int _;
    cin>>n>>_;
    for(int i=0;i<n-1;i++){
        int u,v;
        LL l;
        cin>>u>>v>>l;
        G[u].push_back({v,l});
        G[v].push_back({u,l});
    }
    priority_queue<P> q;
    q.push({1,1});
    while(!q.empty()){
        P tp=q.top();q.pop();
        if(dis[tp.x])continue;
        dis[tp.x]=tp.l;
        for(auto j:G[tp.x]){
            if(dis[j.x])continue;
            q.push({j.x,tp.l+j.l});
        }
    }
    LL ma=0;
    for(int i=1;i<=n;i++){
        if(dis[i]>ma)x=i,ma=dis[i];
    }
    fill(dis+1,dis+1+n,0);
    q.push({x,1});
    while(!q.empty()){
        P tp=q.top();q.pop();
        if(dis[tp.x])continue;
        dis[tp.x]=tp.l;
        for(auto j:G[tp.x]){
            if(dis[j.x])continue;
            q.push({j.x,tp.l+j.l});
        }
    }
    ma=0;
    for(int i=1;i<=n;i++)if(ma<dis[i])y=i,ma=dis[i];
    LL ll=dis[y]-1;
    q.push({y,1});
    while(!q.empty()){
        P tp=q.top();q.pop();
        if(disy[tp.x])continue;disy[tp.x]=tp.l;
        for(auto j:G[tp.x]){
            if(disy[j.x])continue;
            q.push({j.x,j.l+tp.l});
        }
    }
    LL ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,min(dis[i],disy[i])-1+ll);
    }
    cout<<ans;
}
