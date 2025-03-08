#include<iostream>
#include<vector>
#include<stdio.h>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
using namespace std;
typedef long long LL;
int h[100005];
int pri[100005];
struct CHREQ{
    int h,p;
    bool operator<(CHREQ o)const{
        return p>o.p;
    }
};
int main(){
    int _;
    cin>>_;
    while(_--){
        int n,k;
        scanf("%d%d",&n,&k);
        for(int i=0;i<n;i++)scanf("%d",&h[i]);
        for(int i=0;i<n;i++)scanf("%d",&pp[i]);
        priority_queue<CHREQ> q;
        for(int i=0;i<n;i++){
            q.push({h[i], pp[i]});
        }
        LL has=0;
        while(k>0){
            has+=k;
            while(!q.empty()&&q.top().h<=has)q.pop();
            if(q.empty())break;
            k-=q.top().p;
        }
        if(q.empty()){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
}