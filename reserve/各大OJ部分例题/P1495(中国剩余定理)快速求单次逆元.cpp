#include<bits/stdc++.h>
#define qwe(i,a,b) for(int i=a;i<=b;i++)
#define LL long long
using namespace std;
const int N=3e5+5;
const LL inf=1e12;
LL inv(const LL& x, const LL& y) {
    if(x==0)return -1;
    LL u = 0, v = 1, a = x, m = y, t;
    while (a != 0) {
        t = m / a;
        swap(a, m -= t * a);
        swap(u -= t * v, v);
    }
    if(m!=1)return -1;
    return (u%y+y)%y;
}
struct CHREQ{
    LL res, md;
};
LL CHR(vector<CHREQ>& A ,LL& Lcm){
    Lcm=1;
    LL a1=0;
    for(int i=0;i<A.size();i++){
        LL g=gcd(Lcm,A[i].md);
        if((a1-A[i].res)%g)return -1;
        LL dt=(A[i].res-a1)/g;
        LL k1=Lcm/g;
        LL k2=A[i].md/g;
        LL m1=inv(k1,k2);
        m1*=dt;
        m1=(m1%A[i].md+A[i].md)%A[i].md;
        a1+=m1*Lcm;
        Lcm=Lcm/g*A[i].md;
        a1=(a1%Lcm+Lcm)%Lcm;
    }
    return a1;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    vector<CHREQ> A(n);
    for(int i=0;i<n;i++){
        LL a,b;
        cin>>a>>b;
        A[i].md=a;
        A[i].res=b;
    }
    LL i;
    cout<<CHR(A,i);
}
