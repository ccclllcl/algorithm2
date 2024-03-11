#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
class Fancy {
public:
    typedef long long LL;
    const int N=1e5;
    LL mod=1e9+7;
    struct P{
        int l=0,r=0,ls=0,rs=0;
        LL sum=0;
        LL add=0;
        LL mul=1;
    };
    vector<P> Q;
    int cnt=1;
    int R=0;
    Fancy() {
    Q=vector<P>(N<<2);
    Q[1].l=0,Q[1].r=N;
    }
    void gen(int u){
        int mid=Q[u].l+((Q[u].r-Q[u].l)>>1);
        Q[u].ls=++cnt,Q[Q[u].ls].l=Q[u].l,Q[Q[u].ls].r=mid;
        Q[u].rs=++cnt,Q[Q[u].rs].l=mid+1,Q[Q[u].rs].r=Q[u].r;
    }
    bool isleaf(int u){
        return Q[u].l==Q[u].r;
    }
    void pushdown2(int u){
        if(isleaf(u))return;
        if(!Q[u].ls)gen(u);
        if(Q[u].mul!=1)pushdown1(u);
        LL ad=Q[u].add;
        Q[Q[u].ls].add+=ad;
        Q[Q[u].ls].add%=mod;
        Q[Q[u].rs].add+=ad;
        Q[Q[u].rs].add%=mod;
        Q[Q[u].ls].sum+=ad*(Q[Q[u].ls].r-Q[Q[u].ls].l+1);
        Q[Q[u].ls].sum%=mod;
        Q[Q[u].rs].sum+=ad*(Q[Q[u].rs].r-Q[Q[u].rs].l+1);
        Q[Q[u].rs].sum%=mod;
        Q[u].add=0;
    }
    void pushdown1(int u){
        if(isleaf(u))return;
        if(!Q[u].ls)gen(u);
        if(Q[Q[u].ls].add)pushdown2(Q[u].ls);
        if(Q[Q[u].rs].add)pushdown2(Q[u].rs);
        Q[Q[u].ls].mul*=Q[u].mul;
        Q[Q[u].ls].mul%=mod;
        Q[Q[u].rs].mul*=Q[u].mul;
        Q[Q[u].rs].mul%=mod;
        Q[Q[u].ls].sum*=Q[u].mul;
        Q[Q[u].ls].sum%=mod;
        Q[Q[u].rs].sum*=Q[u].mul;
        Q[Q[u].rs].sum%=mod;
        Q[u].mul=1;
    }
    void pushup(int u){
        Q[u].sum=Q[Q[u].ls].sum+Q[Q[u].rs].sum;
        Q[u].sum%=mod;
    }
    void mul(int u,int l,int r,LL val){
        if(l<=Q[u].l&&r>=Q[u].r){
            if(Q[u].add) {pushdown2(u);}
            Q[u].sum*=val;
            Q[u].sum%=mod;
            Q[u].mul*=val;
            Q[u].mul%=mod;
            return;
        }
        if(!Q[u].ls)gen(u);
        if(Q[u].add)pushdown2(u);
        if(Q[u].mul!=1)pushdown1(u);
        if(l<=Q[Q[u].ls].r)mul(Q[u].ls,l,r,val);
        if(r>=Q[Q[u].rs].l)mul(Q[u].rs,l,r,val);
        pushup(u);
    }
    void add(int u,int l,int r,LL val){
        if(l<=Q[u].l&&r>=Q[u].r){
            Q[u].add+=val;
            Q[u].add%=mod;
            Q[u].sum+=val*(Q[u].r-Q[u].l+1);
            Q[u].sum%=mod;
            return;
        }
        if(!Q[u].ls)gen(u);
        if(Q[u].add)pushdown2(u);
        if(Q[u].mul!=1)pushdown1(u);
        if(l<=Q[Q[u].ls].r)add(Q[u].ls,l,r,val);
        if(r>=Q[Q[u].rs].l)add(Q[u].rs,l,r,val);
        pushup(u);
    }
    LL query(int u,int l,int r){
        if(l<=Q[u].l&&r>=Q[u].r){
            return Q[u].sum;
        }
        if(!Q[u].ls)gen(u);
        if(Q[u].add)pushdown2(u);
        if(Q[u].mul!=1)pushdown1(u);
        LL s=0;
        if(l<=Q[Q[u].ls].r)s+= query(Q[u].ls,l,r);
        if(r>=Q[Q[u].rs].l)s+= query(Q[u].rs,l,r);
        return s;
    }
    void append(int val) {
        add(1,R,R,val);
        R++;
    }

    void addAll(int inc) {
        if(!R)return;
        add(1,0,R-1,inc);
    }

    void multAll(int m) {
        if(!R)return;
        mul(1,0,R-1,m);
    }

    int getIndex(int idx) {
        if(idx>=R)return -1;
        return query(1,idx,idx);
    }
};
int main(){
    Fancy ss;
    ss.append(2);
    ss.addAll(3);
    ss.append(7);
    ss.multAll(2);
    cout<<ss.getIndex(0)<<endl;
    ss.addAll(3);
    ss.append(10);
    ss.multAll(2);
    cout<<ss.getIndex(0)<<endl;
    cout<<ss.getIndex(1)<<endl;
    cout<<ss.getIndex(2)<<endl;
}