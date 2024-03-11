#include<bits/stdc++.h>
#define ls ((u)<<1)
#define rs (((u)<<1)|1)
#define LL long long
using namespace std;
const int N=6e6;
LL inf=1e18;
LL mod=inf;//不取模时让mod为inf,取模时区最大和区最小失效
LL s1[N],s2[N],s3[N],fu[N],add[N],mul[N],ma[N],mn[N];
LL A[N];//从1开始
struct P{
    LL s1,s2,s3,ma,mn;
};
P operator+(const P& a,const P& b){
    P res;
    res.s1=(a.s1+b.s1)%mod;
    res.s2=(a.s2+b.s2)%mod;
    res.s3=(a.s3+b.s3)%mod;
    res.ma=max(a.ma,b.ma);
    res.mn=min(a.mn,b.mn);
    return res;
}
P e;
void pushup(int u){
    s1[u]=s1[ls]+s1[rs];
    s2[u]=s2[ls]+s2[rs];
    s3[u]=s3[ls]+s3[rs];
    ma[u]=max(ma[ls],ma[rs]);
    mn[u]=min(mn[ls],mn[rs]);
}
void build(int u,int l,int r){
    if(l==r){
        LL v=A[l];
        s1[u]=v;
        s2[u]=v*v;
        s3[u]=v*v*v;
        ma[u]=v;
        mn[u]=v;
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(u);
}
void init(int n){
    e.s1=e.s2=e.s3=0;
    e.ma=-inf;
    e.mn=inf;
    build(1,1,n);
    fill(mul,mul+n*4,1);
    fill(fu,fu+4*n,inf);
}
void update(int u,int len,int op,LL v){ //op:0表示赋值,1表示乘,2表示加
    if(op==0){
        add[u]=0;
        mul[u]=1;
        fu[u]=v%mod;
        s1[u]=v*len%mod;
        s2[u]=((v*v%mod)*len)%mod;
        s3[u]=((v*v%mod)*v%mod)*len%mod;
        ma[u]=mn[u]=v;
    }else if(op==1){
        mul[u]*=v;
        mul[u]%=mod;
        add[u]*=v;
        add[u]%=mod;
        s1[u]*=v;
        s1[u]%=mod;
        s2[u]*=(v*v)%mod;
        s2[u]%=mod;
        s3[u]*=(v*v%mod)*v%mod;
        s3[u]%=mod;
        if(v==0)ma[u]=mn[u]=0;
        else if(v>0){
            LL tp=ma[u];
            ma[u]=mn[u]*v%mod;
            mn[u]=tp*v%mod;
        }else{
            ma[u]*=v;
            ma[u]%=mod;
            mn[u]*=v;
            mn[u]%=mod;
        }
    }else{
        add[u]+=v;
        add[u]%=mod;
        ma[u]+=v;
        ma[u]%=mod;
        mn[u]+=v;
        mn[u]%=mod;
        LL tmp=(v*v%mod)*v%mod;
        s3[u]+=(len*tmp%mod)+3*(v*(s2[u]+s1[u]*v%mod)%mod)%mod;
        s3[u]%=mod;
        s2[u]+=(v*v%mod)*len%mod+2*(s1[u]*v%mod)%mod;
        s2[u]%=mod;
        s1[u]+=v*len%mod;
        s1[u]%=mod;
    }
}
void pushdown(int u,int l,int r){
    int mid=(l+r)>>1;
    int llen=mid-l+1;
    int rlen=r-mid;
    if(fu[u]!=inf){
        update(ls,llen,0,fu[u]);
        update(rs,rlen,0,fu[u]);
        fu[u]=inf;
    }
    if(mul[u]!=1){
        update(ls,llen,1,mul[u]);
        update(rs,rlen,1,mul[u]);
        mul[u]=1;
    }
    if(add[u]){
        update(ls,llen,2,add[u]);
        update(rs,rlen,2,add[u]);
        add[u]=0;
    }
}
void change(int u,int l,int r,int L,int R,int op,LL v){//op:0表示赋值,1表示乘,2表示加
    if(L<=l&&R>=r){
        update(u,r-l+1,op,v);
        return;
    }
    pushdown(u,l,r);
    int mid=(l+r)>>1;
    if(L<=mid)change(ls,l,mid,L,R,op,v);
    if(R>mid)change(rs,mid+1,r,L,R,op,v);
    pushup(u);
}
P query(int u,int l,int r,int L,int R){
    if(L<=l&&R>=r){
        P res;
        res.s1=s1[u];
        res.s2=s2[u];
        res.s3=s3[u];
        res.ma=ma[u];
        res.mn=mn[u];
        return res;
    }
    pushdown(u,l,r);
    int mid=(l+r)>>1;
    P res=e;
    if(L<=mid)res=res + query(ls,l,mid,L,R);
    if(R>mid)res=res + query(rs,mid+1,r,L,R);
    return res;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    LL n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>A[i];
    }
    init(n);
    for(int _=0;_<m;_++){
        int op;
        int l,r;
        cin>>op>>l>>r;
        if(op==1){
            LL k;
            cin>>k;
            change(1,1,n,l,r,2,k);
        }else if(op==2){
            auto res=query(1,1,n,l,r);
            double ans=((double)res.s1)/(r-l+1);
            printf("%.4lf\n",ans);
        }else{
            auto res= query(1,1,n,l,r);
            double p2=((double)res.s2)/(r-l+1);
            double p1=((double)res.s1)/(r-l+1);
            double ans=p2-p1*p1;
            printf("%.4lf\n",ans);
        }
    }
}