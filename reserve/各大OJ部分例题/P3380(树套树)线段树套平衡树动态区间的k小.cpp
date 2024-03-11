#include<bits/stdc++.h>
#include<bits/extc++.h>
#define ls ((u)<<1)
#define rs ((u)<<1|1)
#define mid (((l)+(r))>>1)
#define itn int
#define asn ans
#define reisze resize
#define pll pair<LL,LL>
#define pii pair<int,int>
#define LL long long
using namespace std;
typedef __gnu_pbds::tree<pll, __gnu_pbds::null_type, std::less<>,
        __gnu_pbds::rb_tree_tag,
        __gnu_pbds::tree_order_statistics_node_update>
        RBTree;
constexpr int N=5e4+5;
constexpr LL inf=1e12;
RBTree S[N*4];
int cc=0;
int A[N];
void change(int u,int l,int r,int p,int v){
    if(A[p]!=-1)S[u].erase(S[u].lower_bound({A[p],-1}));
    S[u].insert({v,++cc});
    if(l==r){
        A[p]=v;
        return;
    }
    if(p<=mid)change(ls,l,mid,p,v);
    else change(rs,mid+1,r,p,v);
}
int Rank(int u,int l,int r,int L,int R,int k){
    if(L<=l&&R>=r){
        return S[u].order_of_key({k,0});
    }
    int res=0;
    if(L<=mid)res+=Rank(ls,l,mid,L,R,k);
    if(R>mid)res+=Rank(rs,mid+1,r,L,R,k);
    return res;
}
int get_pre(int u,int l,int r,int L,int R,int k){
    if(L<=l&&R>=r){
        auto p=S[u].lower_bound({k,0});
        if(p!=S[u].begin())return (--p)->first;
        else return INT_MIN;
    }
    int res=INT_MIN;
    if(L<=mid)res=max(res,get_pre(ls,l,mid,L,R,k));
    if(R>mid)res=max(res,get_pre(rs,mid+1,r,L,R,k));
    return res;
}
int get_ne(int u,int l,int r,int L,int R,int k){
    if(L<=l&&R>=r){
        auto p=S[u].upper_bound({k+1,0});
        if(p!=S[u].end())return p->first;
        else return INT_MAX;
    }
    int res=INT_MAX;
    if(L<=mid)res=min(res, get_ne(ls,l,mid,L,R,k));
    if(R>mid)res=min(res, get_ne(rs,mid+1,r,L,R,k));
    return res;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        A[i]=-1;
        change(1,1,n,i,v);
    }
    for(int _=0;_<m;_++){
        int op;
        cin>>op;
        int l,r,k,pos;
        if(op==1){
            cin>>l>>r>>k;
            cout<<Rank(1,1,n,l,r,k)+1<<'\n';
        }else if(op==2){
            cin>>l>>r>>k;
            LL L=0,R=1e8;
            while(L<R){
                LL M=(L+R+1)>>1;
                if(Rank(1,1,n,l,r,M)<k)L=M;
                else R=M-1;
            }
            cout<<L<<'\n';
        }else if(op==3){
            cin>>pos>>k;
            change(1,1,n,pos,k);
        }else if(op==4){
            cin>>l>>r>>k;
            int v=get_pre(1,1,n,l,r,k);
            cout<<(v==INT_MIN?INT_MIN+1:v)<<'\n';
        }else{
            cin>>l>>r>>k;
            cout<<get_ne(1,1,n,l,r,k)<<'\n';
        }
    }
}
