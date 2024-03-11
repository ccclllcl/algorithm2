#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
#define LL long long
typedef pair<LL,LL> pll;
const int N=3e5+5;
LL inf=1e12;
__gnu_pbds::priority_queue<LL> q[N];
LL n,m;
vector<int> G[N];
LL L[N];
LL C[N];
LL ans=0;
LL sum=0;
LL dfs(int x){
    LL res=C[x];
    for(int ne:G[x]){
        LL v=dfs(ne);
        q[x].join(q[ne]);
        res+=v;
    }
    while(!q[x].empty()&&res>m)res-=q[x].top(),q[x].pop();
    ans=max(ans,(LL)q[x].size()*L[x]);
    return res;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int u;
        cin>>u>>C[i]>>L[i];
        G[u].push_back(i);
        q[i].push(C[i]);
    }
    dfs(1);
    cout<<ans;
}
