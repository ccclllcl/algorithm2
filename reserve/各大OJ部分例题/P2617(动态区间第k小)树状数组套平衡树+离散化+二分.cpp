#include<bits/stdc++.h>
#include<bits/extc++.h>
#define ls ((u)<<1)
#define rs ((u)<<1|1)
#define mid (((l)+(r))>>1)
#define lowbit(x) ((x)&(-(x)))
#define itn int
#define asn ans
#define reisze resize
#define pll pair<LL,LL>
#define pii pair<int,int>
#define LL long long
using namespace std;
constexpr int N=3e5+5;
constexpr LL inf=1e12;
typedef __gnu_pbds::tree<pll, __gnu_pbds::null_type, std::less<pll>,
        __gnu_pbds::rb_tree_tag,
        __gnu_pbds::tree_order_statistics_node_update>
        RBTree;
int cc=0;
int n,m;
RBTree C[N*4];
LL A[N];
void change(int x,LL v,int op){
    ++cc;
    if(op)for(;x<=n;x+= lowbit(x))C[x].insert({v,cc});
    else for(;x<=n;x+= lowbit(x))C[x].erase(C[x].lower_bound({v,0}));
}
LL query(int x,LL v){
    LL res=0;
    for(;x;x-= lowbit(x))res+=C[x].order_of_key({v,0});
    return res;
}
struct P{
    char op;
    LL a,b,c;
};
vector<LL> B;
int bn;
vector<P> OP;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n>>m;
    B.resize(n);
    for(int i=1;i<=n;i++){
        cin>>A[i];
        B[i-1]=A[i];
    }
    OP.resize(m);
    for(int _=0;_<m;_++){
        char op;
        cin>>op;
        int l,r,x;
        LL k,y;
        if(op=='Q'){
            cin>>l>>r>>k;
            OP[_]={op,l,r,k};
        }else{
            cin>>x>>y;
            OP[_]={op,x,y,0};
            B.push_back(y);
        }
    }
    sort(B.begin(),B.end());
    bn=B.erase(unique(B.begin(),B.end()),B.end())-B.begin();
    for(int i=1;i<=n;i++){
        int p= lower_bound(B.begin(),B.end(),A[i])-B.begin();
        change(i,p,1);
    }
    for(auto& q:OP){
        if(q.op=='Q'){
            int l=q.a,r=q.b,k=q.c;
            LL L=0,R=bn-1;
            while(L<R){
                LL M=(L+R+1)>>1;
                LL has= query(r,M)- query(l-1,M);
                if(has<=k-1)L=M;
                else R=M-1;
            }
            cout<<B[L]<<'\n';
        }else{
            int x=q.a;
            LL y=q.b;
            LL v= lower_bound(B.begin(),B.end(),A[x])-B.begin();
            change(x,v,0);
            v= lower_bound(B.begin(),B.end(),y)-B.begin();
            change(x,v,1);
            A[x]=y;
        }
    }
}
