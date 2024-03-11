#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=2e7;
struct P{
    int a,b,c,t;
    bool operator<(P o)const{
        if(a!=o.a)return a<o.a;
        if(b!=o.b)return b<o.b;
        return c<o.c;
    }
    bool operator==(P o)const{
        return a==o.a&&b==o.b&&c==o.c;
    }
    bool operator!=(P o)const{
        return !(*this==o);
    }
};
int n,k;
int ls[N],rs[N],sum[N],root[N];
int cnt=0;
vector<P> arr;
int head;
int ans[N];
void changeY(int& p,int l,int r,P& tp,int num){
    if(!p)p=++cnt;
    sum[p]+=num;
    if(l==r)return;
    int mid=(l+r)>>1;
    if(tp.c<=mid)changeY(ls[p],l,mid,tp,num);
    else changeY(rs[p],mid+1,r,tp,num);
}
void changeX(int& p,int l,int r,P& tp,int num){
    if(!p)p=++cnt;
    changeY(root[p],1,k,tp,num);
    if(l==r)return;
    int mid=(l+r)>>1;
    if(tp.b<=mid)changeX(ls[p],l,mid,tp,num);
    else changeX(rs[p],mid+1,r,tp,num);
}
int queryY(int p,int l,int r,int L,int R){
    if(!p)return 0;
    if(L<=l&&R>=r){
        return sum[p];
    }
    int mid=(l+r)>>1;
    int res=0;
    if(L<=mid)res+= queryY(ls[p],l,mid,L,R);
    if(R>mid)res+=queryY(rs[p],mid+1,r,L,R);
    return res;
}
int queryX(int p,int l,int r,int L,int R,int Ly,int Ry){
    if(!p)return 0;
    if(L<=l&&R>=r){
        return queryY(root[p],1,k,Ly,Ry);
    }
    int mid=(l+r)>>1;
    int res=0;
    if(L<=mid)res+=queryX(ls[p],l,mid,L,R,Ly,Ry);
    if(R>mid)res+=queryX(rs[p],mid+1,r,L,R,Ly,Ry);
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>k;
    arr.resize(n+1);
    for(int i=1;i<=n;i++){
        cin>>arr[i].a>>arr[i].b>>arr[i].c;
    }
    sort(arr.begin(),arr.end());
    vector<P> A;
    A.push_back(arr[1]);
    A[0].t=1;
    for(int i=2;i<=n;i++){
        if(arr[i]==A.back())A.back().t++;
        else A.push_back(arr[i]),A.back().t=1;
    }
    int s=A.size();
    for(int i=0;i<s;i++){
        int num=queryX(1,1,k,1,A[i].b,1,A[i].c);
        ans[num+A[i].t-1]+=A[i].t;
        changeX(head,1,k,A[i],A[i].t);
    }
    for(int i=0;i<n;i++){
        cout<<ans[i]<<'\n';
    }
}