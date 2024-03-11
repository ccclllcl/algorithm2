#include<bits/stdc++.h>
#define LL long long
#define ls ((u)<<1)
#define rs ((u)<<1|1)
using namespace std;
const int N=4*(3e5+5);
LL n,m,q;
LL ans=0;
vector<LL> dd[2];
map<LL,LL> M[2];
LL T[N*8];
struct P{
    LL* Q;
    LL (*calc)(LL);
    P(LL* Q,LL (*calc)(LL)):Q(Q),calc(calc){};
    LL query(LL u,LL l,LL r,LL L,LL R){
        if(L>R)return 0;
        if(L<=l&&R>=r)return Q[u];
        LL mid=(l+r)>>1;
        LL res=0;
        if(L<=mid)res+= query(ls,l,mid,L,R);
        if(R>mid)res+= query(rs,mid+1,r,L,R);
        return res;
    };
    void change(LL u,LL l,LL r,LL p,LL d){
        if(l==r){
            LL v=calc(l);
            if(!v)return;
            LL t0=Q[u]/v;
            t0+=d;
            Q[u]=t0*v;
            return;
        }
        LL mid=(l+r)>>1;
        if(p<=mid)change(ls,l,mid,p,d);
        else change(rs,mid+1,r,p,d);
        Q[u]=Q[ls]+Q[rs];
    };
};
void op1(vector<LL>&A,map<LL,LL>& M,P* tr){
    LL l=A.size();
    LL pre=0;
    for(LL i=1;i<l;i++){
        if(A[i]==0){
            M[pre]=i-pre;
            pre=i;
        }
    }
    M[pre]=l-pre;
    for(auto &[k,v]:M){
        for(int p=0;p<4;p++)
            tr[p].change(1,1,l,v,1);
    }
}
P* seg[2];
LL len[2];
LL ask(int op,LL x){
    int y=op^1;
    LL res=0;
    for(int h=0;h<2;h++){
        res+=seg[op][h].calc(x)*seg[y][3-h].query(1,1,len[y],1,x-1);
    }
    for(int h=2;h<4;h++){
        res+=seg[op][h].calc(x)*seg[y][3-h].query(1,1,len[y],x,len[y]);
    }
    return res;
}
void update(int op,LL x,LL v){
    for(int h=0;h<4;h++){
        seg[op][h].change(1,1,len[op],x,v);
    }
    ans+=ask(op,x)*v;
}
void modify(int t,LL l,LL x){
    LL v0=dd[t][l];
    dd[t][l]+=x;
    if(v0==0){
        auto pr=M[t].lower_bound(l);
        auto pn=pr--;
        LL p1=pr->second;
        LL p2=pn->second;
        pr->second+=pn->second;
        M[t].erase(pn);
        update(t,p1,-1);
        update(t,p2,-1);
        update(t,p1+p2,1);
    }else if(dd[t][l]==0){
        auto tp=--M[t].upper_bound(l);
        LL p1=l-tp->first;
        LL p2=tp->second-p1;
        tp->second=p1;
        M[t][l]=p2;
        update(t,p1,1);
        update(t,p2,1);
        update(t,p1+p2,-1);
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m>>q;
    len[0]=n,len[1]=m;
    dd[0].resize(n);
    dd[1].resize(m);
    for(LL &i:dd[0])cin>>i;
    for(LL &i:dd[1])cin>>i;
    for(int i=n-1;i;i--)dd[0][i]-=dd[0][i-1];
    for(int i=m-1;i;i--)dd[1][i]-=dd[1][i-1];
    dd[0][0]=dd[1][0]=0;
    auto a=[](LL v){
        return 1LL;
    };
    auto b=[](LL v){
        return v;
    };
    auto c=[](LL v){
        return v*(v+1)/2;
    };
    auto d=[](LL v){
        return v*(v+1)*(2*v+1)/6-v*v*(v+1)/2;
    };
    P X[4]={{T,a},{T+N,b},{T+2*N,c},{T+3*N,d}};
    P Y[4]={{T+4*N,a},{T+5*N,b},{T+6*N,c},{T+7*N,d}};
    seg[0]=X;seg[1]=Y;
    op1(dd[0],M[0],X);op1(dd[1],M[1],Y);
    for(auto& [k,v]:M[1]){
        ans+=ask(1,v);
    }
    cout<<ans<<'\n';
    for(int _=0;_<q;_++){
        LL t,l,r,x;
        cin>>t>>l>>r>>x;
        if(x==0){
            cout<<ans<<'\n';
            continue;
        }
        l--,r--;
        t--;
        if(l){
            modify(t,l,x);
        }
        if(r+1<len[t]){
            modify(t,r+1,-x);
        }
        cout<<ans<<'\n';
    }
}