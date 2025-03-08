#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define ls ((u)<<1)
#define rs ((u)<<1|1)
#define mid (((l)+(r))>>1)
#define lowbit(x) ((x)&(-(x)))
#define itn int
#define asn ans
#define reisze resize
#define pdd pair<double,double>
#define pll pair<LL,LL>
#define pii pair<int,int>
#define LL long long
#define ld long double
using namespace std;
const int N=3e5+5;
const int SIZ=1e7;
const LL inf=1e17;
vector<int> G[N];
LL dfs(int x,int f){
    LL res=0;
    for(int ne:G[x]){
        if(ne==f)continue;
        res=max(res,dfs(ne,x));
    }
    return res+1;
}
signed main(){
    IOS;
    int n;cin>>n;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    int x=1,y=1;
    vector<int> dis(n+1);
    dis[1]=1;
    queue<int> q;
    q.push(1);
    while(!q.empty()){
        int tp=q.front();
        q.pop();
        for(int ne:G[tp]){
            if(!dis[ne])dis[ne]=dis[tp]+1,q.push(ne);
        }
    }
    for(int i=2;i<=n;i++)if(dis[i]>dis[y])y=i;
    fill(dis.begin(),dis.end(),0);
    vector<int> pre(n+1);
    dis[y]=1;
    q.push(y);
    while(!q.empty()){
        int tp=q.front();
        q.pop();
        for(int ne:G[tp]){
            if(!dis[ne])dis[ne]=dis[tp]+1,pre[ne]=tp,q.push(ne);
        }
    }
    for(int i=1;i<=n;i++)if(dis[i]>dis[x])x=i;
    vector<int> dd;
    int now=x;
    while(now!=0)dd.push_back(now),now=pre[now];
    if(dd.size()<7){
        cout<<"Yes";
        return 0;
    }
    set<int> D;
    for(int i:dd)D.insert(i);
    for(int i=3;i<dd.size()-3;i++){
        int v=dd[i];
        if(G[v].size()>2){
            for(int ne:G[v]){
                if(D.count(ne))continue;
                if(dfs(ne,v)>=3){
                    cout<<"No";
                    return 0;
                }
            }
        }
    }
    cout<<"Yes";
}
