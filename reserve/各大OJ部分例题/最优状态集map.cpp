#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define ls ((u)<<1)
#define rs ((u)<<1|1)
#define mid (((l)+(r))>>1)
#define lowbit(x) ((x)&(-(x)))
#define itn int
#define asn ans
#define reisze resize
#define pdd pair<double,double>
#define pll pair<LL,LL>
#define plll pair<LLL,LLL>
#define pii pair<int,int>
#define tll tuple<LL,LL,LL>
#define tii tuple<int,int,int>
#define LL long long
#define LLL __int128
#define ld long double
using namespace std;
template<typename T>
istream& operator>>(istream& in,vector<T>& arr){
    for(auto& v:arr)in>>v;
    return in;
}
template<typename T>
ostream& operator<<(ostream& out,vector<T>& arr){
    for(auto& v:arr)out<<v<<' ';
    return out;
}
template<typename t1,typename t2>
istream& operator>>(istream& in,pair<t1,t2>& pa){
    in>>pa.first>>pa.second;
    return in;
}
template<typename t1,typename t2>
ostream& operator<<(ostream& out,const pair<t1,t2>& pa){
    out<<pa.first<<' '<<pa.second;
    return out;
}
const int N=6e5+5;
const int SIZ=1e7;
const LL inf=1e17;
const int ss=62;
plll chmax(const pll& a,const pll& b){
    if(a.first+a.second!=b.first+b.second)return a.first+a.second>b.first+b.second?a:b;
    else return a.first>b.first?a:b;
}
struct P{
    map<LLL,LLL> M;
    void insert(const plll& a){
        if(M.empty()) { M.insert(a);
            return; }
        if(a.first>(--M.end())->first){
            auto tp=--M.end();
            while(tp->second<=a.second) {
                bool fst=tp==M.begin();
                M.erase(tp--);
                if(fst)break;
            }
            M[a.first]=a.second;
            return;
        }
        auto ne=M.lower_bound(a.first);
        if(ne->second>=a.second)return;
        if(ne==M.begin()){
            M[a.first]=a.second;
            return;
        }
        ne=(--M.upper_bound(a.first));
        while(ne->second<=a.second){
            bool fst=ne==M.begin();
            M.erase(ne--);
            if(fst)break;
        }
        M[a.first]=a.second;
    }
    bool empty(){
        return M.empty();
    }
};
plll calc(const plll& a){
    return {a.first+a.second,a.first};
}
void solve(){
    LL n,m;
    cin>>n>>m;
    vector<LL> B(n);
    vector<LLL> A(n);
    cin>>B;
    for(int i=0;i<n;i++)A[i]=B[i];
    std::destroy(B.begin(), B.end());
    int cc=0;
    if(n<m){
        cout<<-1;
        return;
    }
    for(LLL v:A)if(v>0)cc++;
    if(cc==m){
        cout<<0;
        return;
    }
    if(n==1){
        cout<<-1;
        return;
    }
    if(cc==0&&m){
        cout<<-1;
        return;
    }
    if(cc==n&&m<n){
        cout<<-1;
        return;
    }
    if(cc<m){
        LL ans=0;
        sort(A.begin(),A.end(),greater<>());
        if(A[0]<=0){
            cout<<-1;
            return;
        }
        vector<P> dp(ss);
        if(A[1]<0){
            LLL d=(-A[1])/A[0];
            A[1]+=(d+1)*A[0];
            ans+=d+1;
            cc++;
        }
        if(cc==m){
            cout<<ans<<'\n';
            return;
        }
        dp[0].insert({A[0],A[1]});
        for(int i=cc-1;i<m-1;i++){
            vector<P> ndp(ss);
            for(int j=0;j<ss-1;j++){
                auto pp=dp[j];
                if(pp.empty())continue;
                for(auto pr:pp.M){
                    dp[j+1].insert(calc(pr));
                }
            }
            for(int j=0;j<ss;j++) {
                auto pp = dp[j];
                if (pp.empty())continue;
                for (auto &pr: pp.M) {
                    LLL d = (-A[i + 1]) / pr.first;
                    d++;
                    if (j + d - 1 < ss) {
                        LLL val = A[i + 1] + d * pr.first;
                        LLL ma = max(val, pr.first);
                        LLL mi = val + pr.first + pr.second - ma - min(val, pr.second);
                        ndp[j + d - 1].insert({ma, mi});
                    }
                }
            }
            dp=ndp;
        }
        for(int i=0;i<ss;i++){
            if(!dp[i].empty()){
                ans+=i;
                break;
            }
        }
        ans+=m-cc;
        cout<<ans<<'\n';
        return;
    }else{
        for(LLL& v:A)v=-v;
        m=n-m;
        cc=n-cc;
        LL ans=0;
        sort(A.begin(),A.end(),greater<>());
        if(A[0]<=0){
            cout<<-1;
            return;
        }
        vector<P> dp(ss);
        if(A[1]<0){
            LLL d=(-A[1])/A[0];
            A[1]+=d*A[0];
            if(A[1]<0)A[1]+=A[0],d++;
            ans+=d;
            cc++;
        }
        if(cc==m){
            cout<<ans<<'\n';
            return;
        }
        dp[0].insert({A[0], A[1]});
        for(int i=cc-1;i<m-1;i++){
            vector<P> ndp(ss);
            for(int j=0;j<ss-1;j++){
                auto pp=dp[j];
                if(pp.empty())continue;
                for(auto& pr:pp.M){
                    dp[j+1].insert(calc(pr));
                }
            }
            for(int j=0;j<ss;j++){
                auto pp=dp[j];
                if(pp.empty())continue;
                for(auto& pr:pp.M){
                    LLL d=(-A[i+1]+pr.first-1)/pr.first;
                    if(j+d-1<ss){
                        LLL val=A[i+1]+pr.first*d;
                        LLL ma=max(val,pr.first);
                        LLL mi=val+pr.first+pr.second-ma-min(val,pr.second);
                        ndp[j + d - 1].insert({ma,mi}); }
                }
            }
            dp=ndp;
        }
        for(int i=0;i<ss;i++){
            if(!dp[i].empty()){
                ans+=i;
                break;
            }
        }
        ans+=m-cc;
        cout<<ans<<'\n';
    }
}
signed main(){
    IOS;
    int _;
    cin>>_;
    while(_--)solve();
}
