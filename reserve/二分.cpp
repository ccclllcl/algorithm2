#include<iostream>
using namespace std;
int n;
int a[100];
bool check(int m){
    return m>7;
}
int find_max(){
    int l=0,r=n-1,m;
    while(l<r){
        m=l+r+1>>1;
        if(check(m))l=m;
        else r=m-1;
    }
    return l;
}
int find_min(){
    int l=0,r=n-1,m;
    while(l<r){
        m=l+r>>1;
        if(check(m))r=m;
        else l=m+1;
    }
    return l;
}
int main(){
    n=100;
    for(int i=0;i<n;i++){
        a[i]=i;
    }
    cout<<find_min();
    return 0;
}