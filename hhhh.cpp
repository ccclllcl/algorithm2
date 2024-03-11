#include<iostream>
#include<vector>
#include<stdio.h>
#include<algorithm>
#include<map>
#include<set>
#include<unordered_set>
using namespace std;
typedef long long LL;
LL mod=1e9+7;
struct CHREQ{
    int x;LL val;
    bool operator<(CHREQ o)const{
        return val<o.val;
    }
};
CHREQ X[100005];
LL B[100005];
LL gap[100005];
int main() {
    int _;
    cin>>_;
    while(_--){
        int n;
        cin>>n;
        for(int i=0;i<n;i++){
            LL va;
            scanf("%lld",&va);
            X[i]={i, va};
        }
        sort(X, X + n);
        LL sum=0;
        vector<int> stk;
        vector<int> sp;
        for(int i=0;i<n;i++){
            gap[i]= X[i].val - sum;
            if(gap[i]>0)sp.push_back(i);
            if(stk.empty()||gap[i]>gap[stk.back()])stk.push_back(i);
            sum+=X[i].val;
        }
        for(int i=0;i<n;i++){
            if(X[i].val < gap[0]){
                B[X[i].x]=0;
                continue;
            }
            if(X[i].val >= gap[stk.back()]){
                if(i>=sp.back()){
                    B[X[i].x]= n - 1;
                    continue;
                }
                int l=0,r=sp.size()-1;
                while(l<r){
                    int m=(l+r)>>1;
                    if(sp[m]>i)r=m;
                    else l=m+1;
                }
                B[X[i].x]= sp[l] - 1;
                continue;
            }
            int l=0,r=stk.size()-1;
            while(l<r){
                int m=(l+r)>>1;
                if(X[i].val < gap[stk[m]])r=m;
                else l=m+1;
            }
            int mi=stk[l];
            int mm;
            if(i>sp.back())mm=n;
            else{
                l=0,r=sp.size()-1;
                while(l<r){
                    int m=(l+r)>>1;
                    if(sp[m]>i)r=m;
                    else l=m+1;
                }
                mm=sp[l];
            }
            if(mi<mm){
                B[X[i].x]=mi;
            }else{
                B[X[i].x]= mm - 1;
            }
        }
        for(int i=0;i<n;i++)printf("%lld ",B[i]);
        printf("\n");
    }
}