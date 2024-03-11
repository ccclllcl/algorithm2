#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=2e5+5;
void exgcd(LL a,LL b,LL& s,LL& t){ //需保证a,b均为正数且互素,可得到sa+tb=1
    if(a==1){
        s=1;
        t=0;
        return;
    }
    if(b==1){
        s=0;t=1;
        return;
    }
    LL t1,s1;
    exgcd(b,a%b,s1,t1);
    LL k=a/b;
    t=s1-k*t1;
    s=t1;
    LL goal=(s%b+b)%b;
    LL f=(s-goal)/b;
    s=goal;
    t+=f*a;
}
