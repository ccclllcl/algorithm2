#include<algorithm>
#include<iostream>
#include<stdio.h>
#include<queue>
using namespace std;
typedef long long LL;
struct CHREQ{
    LL val,tm;
};
const LL NN=1e4;
int cc=0;
LL pp[(int)NN + 1];
LL fi[(int)NN + 1];
bool has[(int)NN + 1];
LL gcd(LL a,LL b){
    return b?gcd(b,a%b):a;
}
LL qpow(LL a,LL t,LL mod){
    LL res=1;
    while(t){
        if(t&1){
            res*=a;
            res%=mod;
        }
        t>>=1;
        a*=a;
        a%=mod;
    }
    return res;
}
void init(){
    for(int i=2; i <= NN; i++){
        if(!has[i]) { fi[i]=i-1;pp[cc++] = i; }
        for(int j=0; j < cc && pp[j] * i <= NN; j++){
            has[pp[j] * i]=true;
            fi[pp[j] * i]= fi[i] * (pp[j] - 1);
            if(i % pp[j] == 0){
                fi[pp[j] * i]= pp[j] * fi[i];
                break;
            }
        }
    }
}
vector<CHREQ> facc(LL x){
    int la=0;
    vector<CHREQ> res;
    while(x!=1){
        for(int i=la; i < cc; i++){
            if(x % pp[i] == 0){
                x/=pp[i];
                if(res.empty() || pp[i] != res[res.size() - 1].val){
                    res.push_back({pp[i], 1});
                }else{
                    res[res.size()-1].tm++;
                }
                la=i;
                break;
            }
        }
    }
    return res;
}
vector<LL> getgen(LL x){
    vector<LL> res;
    vector<CHREQ> tst= facc(fi[x]);
    for(LL i=2;i<x;i++){
        if(gcd(i,x)!=1)continue;
        int h=0;
        for(;h<tst.size();h++){
            if(qpow(i,fi[x]/tst[h].val,x)==1)break;
        }
        if(h==tst.size())res.push_back(i);
    }
    return res;
}
vector<CHREQ> getgen2(LL x){
    vector<CHREQ> res;
    vector<CHREQ> tst=facc(fi[x]);
    for(LL i=1;i<x;i++){
        if(gcd(i,x)!=1)continue;
        for(LL t=1;t<=fi[x];t++){
            if(qpow(i,t,x)==1){
                res.push_back({i,t});
                break;
            }
        }
    }
    return res;
}
vector<CHREQ> getord(LL x, LL gen){
    vector<CHREQ> res;
    for(LL i=1;i<=fi[x];i++){
        res.push_back({i, qpow(gen, i, x)});
    }
    return res;
}
int isgen(LL x,LL v){
    if(gcd(x,v)>1)return 0;
    vector<CHREQ> tst=facc(fi[x]);
    for(int j=0;j<tst.size();j++){
        if(qpow(v,fi[x]/tst[j].val,x)==1)return 0;
    }
    return 1;
}
int main(){
    init();
//    LL xx=29;
//    vector<LL> res= getgen(xx);
//    for(LL x:res)cout<<x<<" ";
//    cout<<endl;
//    vector<LL> res2=getgen(xx*xx);
//    for(LL x:res2)cout<<x<<" ";
   cout<<isgen(29,14)<<" "<<isgen(29*29,14);
   queue<int> q;
   q.push(1);

}
