#include<bits/stdc++.h>
#define LL long long
#define ls ((p)<<1)
#define rs ((p)<<1|1)
using namespace std;
const int N=1e6;
typedef pair<int,int> pii;
vector<pii> his;
vector<pii> efc;
int pre[N],siz[N];
void init(int n){
    for(int i=1;i<=n;i++)siz[i]=1,pre[i]=i;
}
int root(int x){
    return x==pre[x]?x:root(pre[x]);
}
void merge(int x,int y){
    int rx=root(x),ry=root(y);
    if(rx==ry)return;
    if(siz[rx]>siz[ry])swap(rx,ry);
    his.emplace_back(rx,ry);
    efc.emplace_back(x,y);
    pre[rx]=ry;
    siz[ry]+=siz[rx];
}
void dismerge(){
    auto tp=his.back();
    his.pop_back();
    efc.pop_back();
    int x=tp.first,y=tp.second;
    pre[x]=x;
    siz[y]-=siz[x];
}
int n,m;
struct Q{
    int t;
    int u,v;
};
vector<pii> seg[N];
vector<Q> qu[N];
void change(int p,int l,int r,int L,int R,int u,int v){
    if(L<=l&&R>=r){
        seg[p].emplace_back(u,v);
        return;
    }
    int mid=(l+r)>>1;
    if(L<=mid)change(ls,l,mid,L,R,u,v);
    if(R>mid)change(rs,mid+1,r,L,R,u,v);
}
void addq(int p,int l,int r,int x,Q& q){
    if(l==r){
        qu[p].push_back(q);
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid)addq(ls,l,mid,x,q);
    else addq(rs,mid+1,r,x,q);
}
int cnt=0;
bool ans[N];
void MERGE(int p){
    for(auto tp:seg[p]){
        merge(tp.first,tp.second);
    }
}
bool biequal(pii a,pii b){
    return (a.second==b.first&&a.first==b.second)||a==b;
}
void DISMERGE(int p){
    int c=seg[p].size();
    for(int _=c-1;~_;_--){
        if(!his.empty()&&biequal(seg[p][_],efc.back()))dismerge();
    }
}
void dfs(int p,int l,int r){
    MERGE(p);
    if(l==r){
        for(auto q:qu[p]){
            if(root(q.u)==root(q.v)){
                ans[q.t]=true;
            }
        }
        DISMERGE(p);
        return;
    }
    int mid=(l+r)>>1;
    dfs(ls,l,mid);
    dfs(rs,mid+1,r);
    DISMERGE(p);
}
int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n>>m;
    init(n);
    map<pii,int> M;
    for(int i=1;i<=m;i++){
        int op,u,v;
        cin>>op>>u>>v;
        if(u>v)swap(u,v);
        if(op==1){
            auto it=M.find({u,v});
            if(it!=M.end()){
                change(1,1,m,it->second,i,u,v);
                M.erase(it);
            }else{
                M[{u,v}]=i;
            }
        }else{
            Q q={cnt++,u,v};
            addq(1,1,m,i,q);
        }
    }
    for(auto& [k,v]:M){
        change(1,1,m,v,m,k.first,k.second);
    }
    dfs(1,1,m);
    for(int i=0;i<cnt;i++){
        if(ans[i]){
            cout<<"Y\n";
        }else cout<<"N\n";
    }
}