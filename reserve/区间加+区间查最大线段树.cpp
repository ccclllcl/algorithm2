#include<bits/stdc++.h>
#define ls ((u)<<1)
#define rs (((u)<<1)|1)
#define LL long long
using namespace std;
const int N=6e6;
LL inf=1e18;
struct P{
    LL l,r,v;
    bool operator<(P o)const{
        return v<o.v;
    }
};
LL tag[N],ma[N];
void pushdown(int u){
    if(tag[u]){
        tag[ls]+=tag[u];
        tag[rs]+=tag[u];
        ma[ls]+=tag[u];
        ma[rs]+=tag[u];
        tag[u]=0;
    }
}
void pushup(int u){
    ma[u]=max(ma[ls],ma[rs]);
}
void change(int u,LL l,LL r,LL L,LL R,LL v){
    if(L<=l&&R>=r){
        tag[u]+=v;
        ma[u]+=v;
        return;
    }
    pushdown(u);
    int mid=(l+r)>>1;
    if(L<=mid)change(ls,l,mid,L,R,v);
    if(R>mid)change(rs,mid+1,r,L,R,v);
    pushup(u);
}
LL query(int u,LL l,LL r,LL L,LL R){
    if(L<=l&&R>=r){
        return ma[u];
    }
    pushdown(u);
    LL res=0;
    int mid=(l+r)>>1;
    if(L<=mid)res=max(res, query(ls,l,mid,L,R));
    if(R>mid)res=max(res, query(rs,mid+1,r,L,R));
    return res;
}
int n,m;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    vector<P> arr(n);
    for(int i=0;i<n;i++) { cin >> arr[i].l >> arr[i].r;arr[i].v=arr[i].r-arr[i].l; }
    sort(arr.begin(),arr.end());
    vector<LL> b(2*n);
    for(int i=0;i<n;i++)b[i*2]=arr[i].l,b[2*i+1]=arr[i].r;
    sort(b.begin(),b.end());
    int bn=unique(b.begin(),b.end())-b.begin();
    for(P& tp:arr){
        tp.r= lower_bound(b.begin(),b.begin()+bn,tp.r)-b.begin();
        tp.l= lower_bound(b.begin(),b.begin()+bn,tp.l)-b.begin();
    }
    LL ans=inf;
    int i=0,j=-1;
    LL now=0;
    while(1){
        while(j+1<n&&now<m){
            j++;
            change(1,0,bn-1,arr[j].l,arr[j].r,1);
            now= ma[1];
        }
        if(j==n-1&&now<m){
            break;
        }
        while(i<=j&&now>=m){
            change(1,0,bn-1,arr[i].l,arr[i].r,-1);
            i++;
            now=ma[1];
        }
        ans=min(ans,arr[j].v-arr[i-1].v);
    }
    if(ans==inf){
        cout<<-1;
    }else cout<<ans;
}