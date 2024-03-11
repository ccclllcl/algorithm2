#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
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
constexpr int N=2e5+5;
const int SIZ=1e7;
constexpr LL inf=1e12;
#define arr array<int,31>
itn n;
LL v;
LL maxx[N][25];
LL Log[N];
int len=30;
LL A[N];
LL B[N];
void init(){
    Log[1]=0;
    Log[2]=1;
    for(int i=3;i<N;i++)Log[i]=Log[i/2]+1;
}
void buildA(){
    for(int j=1;j<=n;j++)maxx[j][0]=A[j];
    for(int j=1;j<25;j++){
        for(itn i=1;i+(1<<j)-1<=n;i++){
            maxx[i][j]=max(maxx[i][j-1],maxx[i+(1<<(j-1))][j-1]);
        }
    }
}
LL queryA(int L,int R){
    int s=Log[R-L+1];
    return max(maxx[L][s],maxx[R-(1<<s)+1][s]);
}
struct P{
    int lm[31],rm[31];
    int l,r;
    LL ans=INT_MAX;
};
P operator+(const P& a,const P& b){
    P res;
    res.l=a.l,res.r=b.r;
    for(int i=len;~i;i--){
        res.lm[i]=a.lm[i]==-1?b.lm[i]:a.lm[i];
        res.rm[i]=b.rm[i]==-1?a.rm[i]:b.rm[i];
    }
    res.ans=min(a.ans,b.ans);
    P tl=a,tr=b;
    LL vl,vr;
    int mi=a.r;
    int ll=mi+1;
    int rr=mi;
    int lh=-1,rh=-1;
    for(int i=len;~i;i--){
        if((1<<i)&v){
            if(~lh){
                if(tl.rm[i]==-1)tl.rm[i]=lh;
                else tl.rm[i]=max(tl.rm[i],lh);
            }
            if(~rh){
                if(tr.lm[i]==-1)tr.lm[i]=rh;
                else tr.lm[i]=min(tr.lm[i],rh);
            }
        }else{
            if(tl.rm[i]!=-1){
                if(lh==-1)lh=tl.rm[i];
                else lh=max(lh,tl.rm[i]);
            }
            if(tr.lm[i]!=-1){
                if(rh==-1)rh=tr.lm[i];
                else rh=min(rh,tr.lm[i]);
            }
        }
    }
    for(int i=len;~i;i--){
        if((1<<i)&v){
            if(tl.rm[i]==-1)vl=LONG_LONG_MAX;
            else vl= queryA(tl.rm[i],mi);
            if(tr.lm[i]==-1)vr=LONG_LONG_MAX;
            else vr= queryA(mi+1,tr.lm[i]);
            if(vl==LONG_LONG_MAX&&vr==LONG_LONG_MAX)return res;
            if(vl<=vr)ll=min(ll,tl.rm[i]);
            else rr=max(rr,tr.lm[i]);
            if(queryA(ll,rr)>=res.ans)return res;
        }
    }
    res.ans=min(res.ans, queryA(ll,rr));
    return res;
}
P Q[N*4];
void build(int u,int l,int r){
    if(l==r){
        for(int i=len;~i;i--){
            if((1<<i)&B[l])Q[u].lm[i]=Q[u].rm[i]=l;
            else Q[u].lm[i]=Q[u].rm[i]=-1;
        }
        Q[u].l=Q[u].r=l;
        if(B[l]>=v)Q[u].ans=A[l];
        else Q[u].ans=INT_MAX;
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
    Q[u]=Q[ls]+Q[rs];
}
void change(int u,int l,int r,int p,LL val){
    if(l==r){
        B[l]=val;
        for(int i=len;~i;i--){
            if((1<<i)&B[l])Q[u].lm[i]=Q[u].rm[i]=l;
            else Q[u].lm[i]=Q[u].rm[i]=-1;
        }
        if(B[l]>=v)Q[u].ans=A[l];
        else Q[u].ans=INT_MAX;
        return;
    }
    p<=mid?change(ls,l,mid,p,val):change(rs,mid+1,r,p,val);
    Q[u]=Q[ls]+Q[rs];
}
P query(int u,int l,int r,int L,int R){
    if(L<=l&&R>=r)return Q[u];
    if(L<=mid&&R>mid)return query(ls,l,mid,L,R)+ query(rs,mid+1,r,L,R);
    if(L<=mid)return query(ls,l,mid,L,R);
    return query(rs,mid+1,r,L,R);
}
void solve(){
    cin>>n>>v;
    for(int i=1;i<=n;i++)for(int j=0;j<25;j++)maxx[i][j]=0;
    for(int i=1;i<=n;i++)cin>>A[i];
    buildA();
    for(int i=1;i<=n;i++)cin>>B[i];
    build(1,1,n);
    int q;
    cin>>q;
    while(q--){
        int l,r,op,i;
        LL x;
        cin>>op;
        if(op==1) {
            cin>>i>>x;
            change(1,1,n,i,x);
        }else{
            cin>>l>>r;
            P res= query(1,1,n,l,r);
            if(res.ans==INT_MAX)res.ans=-1;
            cout<<res.ans<<' ';
        }
    }
    cout<<'\n';
}
signed main(){
    init();
    IOS;
    int _;
    cin>>_;
    while(_--)solve();
}
