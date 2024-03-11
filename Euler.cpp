#include<iostream>
#include<vector>
#include<map>
#include<unordered_set>
#include<unordered_map>
#include<set>
#include<queue>
#include<array>
#include<algorithm>
#include<valarray>
#include<stdio.h>
#include<string>
typedef long long LL;
LL mod=1e9+7;
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<LL> A(n);
    vector<LL> B(n);
    for(int i=0;i<n;i++){
        scanf("%lld",&A[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%lld",&B[i]);
    }
    if(A[0] != B[0]){
        cout<<"No"<<endl;
        return 0;
    }
    if(A[n - 1] != B[n - 1]){
        cout<<"No"<<endl;
        return 0;
    }
    if(n==2){
        cout<<"Yes"<<endl;
        return 0;
    }
    unordered_map<LL,int> M;
    for(int i=2;i<n;i++){
        M[A[i]-A[i-1]]++;
    }
    for(int i=1;i<n-1;i++){
        if(A[i]==B[i]){
            if(i>1)M[A[i]-A[i-1]]--;
            continue;
        }
        if(M[B[i]-A[i-1]]>0){
            if(i>1)M[A[i]-A[i-1]]--;
        }else{
            cout<<"No"<<endl;
            return 0;
        }
    }
    cout<<"Yes"<<endl;
}