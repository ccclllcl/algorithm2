#include<bits/stdc++.h>
#define ls ((p)<<1)
#define rs (((p)<<1)|1)
using namespace std;
//namespace fastio{
//    struct reader{
//        template<typename T>reader&operator>>(T&x){
//            char c=getchar();short f=1;
//            while(c<'0'||c>'9'){if(c=='-')f*=-1;c=getchar();}
//            x=0;while(c>='0'&&c<='9'){
//                x=(x<<1)+(x<<3)+(c^48);
//                c=getchar();
//            }x*=f;return *this;
//        }
//    }cin;
//    struct writer{
//        template<typename T>writer&operator<<(T x){
//            if(x==0)return putchar('0'),*this;
//            if(x<0)putchar('-'),x=-x;
//            static int sta[45];int top=0;
//            while(x)sta[++top]=x%10,x/=10;
//            while(top)putchar(sta[top]+'0'),--top;
//            return*this;
//        }
//    }cout;
//};
//#define cin fastio::cin
//#define cout fastio::cout
//#define LL __int128
//#define int __int128
#define LL long long
LL mod=999999893;
const LL N=3e5+5;
struct P{
    int l,r;
    LL mul,add,dec,sum;
};
P Q[N*4];
int m,n,q;
vector<LL> V;
vector<LL> X;
vector<LL> init;
struct P2{
    LL x,v;
    bool operator<(P2 o)const{
        return x<o.x;
    }
};
void pushdownadd(int p);
void pushdownmul(int p);
void pushdowndec(int p);
void pushup(int p){
    Q[p].sum=Q[ls].sum+Q[rs].sum;
}
void pushdownadd(int p){
    if(Q[p].l==Q[p].r)return;
    LL& add=Q[p].add;
    if(!add)return;
    pushdowndec(ls);
    pushdowndec(rs);
    pushdownmul(ls);
    pushdownmul(rs);
    Q[ls].sum+=add*(Q[ls].r-Q[ls].l+1);
    Q[rs].sum+=add*(Q[rs].r-Q[rs].l+1);
    Q[ls].add+=add;
    Q[rs].add+=add;
    add=0;
}
void pushdownmul(int p){
    if(Q[p].l==Q[p].r)return;
    LL& mul=Q[p].mul;
    if(mul==1)return;
    pushdownadd(p);
    if(Q[ls].dec%mul==0)Q[ls].dec/=mul;
    else pushdowndec(ls),Q[ls].mul*=mul;
    if(Q[rs].dec%mul==0)Q[rs].dec/=mul;
    else pushdowndec(rs),Q[rs].mul*=mul;
    Q[ls].sum*=mul;
    Q[rs].sum*=mul;
    mul=1;
}
void pushdowndec(int p){
    if(Q[p].l==Q[p].r)return;
    LL& dec=Q[p].dec;
    if(dec==1)return;
    if(Q[p].mul%dec==0) { Q[p].mul /= dec;dec=1;
        return; }
    pushdownmul(p);
    pushdownadd(p);
    Q[ls].sum/=dec;
    Q[rs].sum/=dec;
    Q[ls].dec*=dec;
    Q[rs].dec*=dec;
    dec=1;
}
void build(int p,int l,int r){
    Q[p].l=l,Q[p].r=r;
    Q[p].sum=Q[p].add=0;
    Q[p].mul=Q[p].dec=1;
    if(l==r){
        Q[p].sum=init[l];
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}
void ADD(int p,int L,int R,LL v){
    if(L>R)return;
    pushdowndec(p);
    pushdownmul(p);
    if(Q[p].l>=L&&Q[p].r<=R){
        Q[p].sum+=v*(Q[p].r-Q[p].l+1);
        Q[p].add+=v;
        return;
    }
    pushdownadd(p);
    int mid=(Q[p].l+Q[p].r)>>1;
    if(L<=mid)ADD(ls,L,R,v);
    if(R>mid)ADD(rs,L,R,v);
    pushup(p);
}
void MUL(int p,int L,int R,LL v){
    if(L>R)return;
    pushdowndec(p);
    if(Q[p].l>=L&&Q[p].r<=R){
        Q[p].sum*=v;
        Q[p].mul*=v;
        return;
    }
    pushdownmul(p);
    int mid=(Q[p].l+Q[p].r)>>1;
    if(L<=mid)MUL(ls,L,R,v);
    if(R>mid)MUL(rs,L,R,v);
    pushup(p);
}
void DEC(int p,int L,int R,LL v){
    if(L>R)return;
    if(Q[p].l>=L&&Q[p].r<=R){
        Q[p].sum/=v;
        Q[p].dec*=v;
        return;
    }
    pushdowndec(p);
    int mid=(Q[p].l+Q[p].r)>>1;
    if(L<=mid)DEC(ls,L,R,v);
    if(R>mid)DEC(rs,L,R,v);
    pushup(p);
}
LL query(int p,int L,int R){
    if(Q[p].l>=L&&Q[p].r<=R)return Q[p].sum;
    pushdowndec(p);
    pushdownmul(p);
    pushdownadd(p);
    int mid=(Q[p].l+Q[p].r)>>1;
    LL res=0;
    if(L<=mid)res+= query(ls,L,R);
    if(R>mid)res+= query(rs,L,R);
    return res;
}
set<P2> S;
map<LL,P2> M;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m>>q;
    X.resize(m);
    V.resize(n);
    for(int i=0;i<m;i++){
        cin>>X[i];
    }
    for(int i=0;i<m;i++)cin>>V[i];
    vector<P2> arr(m);
    for(int i=0;i<m;i++){
        arr[i].x=X[i];
        arr[i].v=V[i];
    }
    sort(arr.begin(),arr.end());
    for(int i=0;i<m;i++)X[i]=arr[i].x,V[i]=arr[i].v;
    for(int i=0;i<m;i++)S.insert(arr[i]);
    for(int i=1;i<m;i++)M[arr[i].x]=arr[i-1];
    init.resize(n+1);
    for(int i=0;i<m-1;i++){
        init[X[i]]=0;
        for(int j=X[i]+1;j<X[i+1];j++){
            init[j]=V[i]*(X[i+1]-j);
        }
    }
    init[X[m-1]]=0;
    build(1,1,n);
    for(int _=0;_<q;_++){
        int op;
        cin>>op;
        if(op==1){
            LL x,v;
            cin>>x>>v;
            P2 tp={x,v};
            auto t2= *S.upper_bound(tp);
            P2 t1=M[t2.x];
            LL vt= query(1,x,x);
            ADD(1,x,x,-vt);
            LL dc=t1.v*(t2.x-x);
            ADD(1,t1.x+1,x-1,-dc);
            DEC(1,x+1,t2.x-1,t1.v);
            MUL(1,x+1,t2.x-1,v);
            S.insert(tp);
            M[t2.x]=tp;
            M[tp.x]=t1;
        }else{
            LL l,r;
            cin>>l>>r;
            cout<<query(1,l,r)<<'\n';
        }
    }
}