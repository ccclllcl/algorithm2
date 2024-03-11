#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
#define LL long long
typedef pair<LL,LL> pll;
const int N=3e5+5;
LL inf=1e12;
__gnu_pbds::priority_queue<pll,greater<>> q[N];
bool has[N];
int fa[N];
int root(int x){
    return x==fa[x]?x:fa[x]=root(fa[x]);
}
void merge(int x,int y){
    x=root(x),y=root(y);
    if(x==y)return;
    fa[x]=y;
    q[y].join(q[x]);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    int m;
    cin>>m;
    for(int i=1;i<=n;i++){
        fa[i]=i;
        LL v;
        cin>>v;
        q[i].push({v,i});
    }
    for(int _=0;_<m;_++){
        int op;
        cin>>op;
        if(op==1){
            int x,y;
            cin>>x>>y;
            if(has[x]||has[y])continue;
            merge(x,y);
        }else{
            int x;
            cin>>x;
            if(has[x]){
                cout<<-1<<'\n';
                continue;
            }
            auto res=q[root(x)].top();
            cout<<res.first<<'\n';
            q[root(x)].pop();
            has[res.second]=1;
        }
    }
}
