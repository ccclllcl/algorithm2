#include<bits/stdc++.h>
#define LL long long
using namespace std;
constexpr int N= 3e5 + 5;
constexpr LL inf=1e12;
vector<int> KMP(const string& S, const string& T){
    vector<int> Next;  //回溯指针  j和Next[j]之间的关系是j前面有若干个字符组成的串与[0,Next[j]-1]相同
    Next.push_back(-1);
    for(int i = 0, j = -1; i < T.size();){
        if (j == -1 || T[i] == T[j]) {
            i++, j++;
            if (i != T.size() && T[j] == T[i]) Next.push_back(Next[j]);//Next数组优化为Nextval数组
            else Next.push_back(j);
        }
        else j = Next[j];  //向前减少字符匹配量
    }

    vector<int> res;
    for (int i = 0, j = 0; i < S.size() && j < (int)T.size();){
        if (j == -1 || S[i] == T[j]) {
            i++, j++;
            if (j == T.size()) {
                res.push_back(i - j);
                j = Next[j];
            }
        }
        else j = Next[j];
    }
    return res;
}
int main(){
    string A="aaaaaaab";
    string B="aaaaa";
    auto res=KMP(A,B);
    for(int i:res)cout<<i<<' ';//0 1 2
}