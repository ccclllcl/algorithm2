#include <stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
int ee(int &a){
    int e=0;
    while(a%2==0){
        a=a/2;
        e++;
    }
    return e;
}
LL qpow(LL a,LL t,LL p){
    LL res=1;
    while(t){
        if(t%2){
            res*=a;
            res%=p;
        }
        a*=a;
        a%=p;
        t>>=1;
    }
    return res;
}
LL inv(LL a,LL p){
    return qpow(a,p-2,p);
}
int div(LL p){
    for(int i=2;i<p;i++)
        if(p%i==0)
            return -1;
    return 1;
}
int L_FAST(int a,int p) {
    int s;
    a=(a%p+p)%p;
    if(a==0){
        return 0;
    }else if(a==1){
        return 1;
    }else{
        if(ee(a)%2==0){
            s=1;
        }else{
            if(p%8==1||p%8==7){
                s=1;
            }
            if(p%8==3||p%8==5){
                s=-1;
            }
        }
        if(p%4==3&&a%4==3){
            s=-s;
        }
        int p1=p%a;
        if(a==1){
            return s;
        }else{
            return s*L_FAST(p1,a);
        }
    }
}
vector<int> shengyu(int p){
    vector<int> res;
    for(int i=1;i<p;i++){
        if(L_FAST(i,p)==1){
            res.push_back(i);
        }
    }
    return res;
}
void PRINT(vector<int>& a){
    for(int i=0;i<a.size();i++)cout<<a[i]<<" ";
}
int main(){
    int a,p,L;
//    int res=L_FAST(1,5);
//    printf("%d",res);
//    vector<int> res= shengyu(7);
//    //PRINT(res);
    for(int x=1;x<=11;x++){
        int h=x*x;
        cout<<x<<":"<<h%23<<" ";
    }
    //cout<<L_FAST(911,2003);
    //cout<<inv(4,141);
    return 0;
}

