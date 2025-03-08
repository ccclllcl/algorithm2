#include<bits/stdc++.h>
#define endl '\n'

using namespace std;

struct Manacher{
    string s;			//原串
    int n;				//str的size
    string str;			//补充后的字符串
    vector<int> len;	//回文半径
    Manacher(string s) : s(s),n(s.size()*2+3){
        init(str);
        build(len);
    }
    void init(string &str){
        str="$#";
        for(auto &i : s){
            str+=i;
            str+='#';
        }
        str+='@';
    }
    void build(vector<int> &len){
        // 写12行 + 改3行 = 15行
        auto equ = [&](char l,char r){
            if(l=='#' && r=='#') return 1;
            if(l=='o' || l=='s' || l=='x' || l=='z'){
                if(l==r) return 1;
                else return 0;
            }
            if(l>r) swap(l,r);
            if(l=='b' && r=='q') return 1;
            if(l=='d' && r=='p') return 1;
            if(l=='n' && r=='u') return 1;
            return 0;
        };
        len=vector<int>(n,0);
        int l=1 , r=1 , p=1;
        for(int i=2;i<=n-3;i++){
            if(!equ(str[i],str[i])) continue;
            if(i>r){
                l = r = p = i;
                while(equ(str[l-1],str[r+1]))
                    l--,r++;
                len[i] = r - p;
            }
            else{
                len[i] = len[2*p-i];
                if(i+len[i]>=r){
                    p = i;
                    l = 2 * p - r;
                    while(equ(str[l-1],str[r+1]))
                        l--,r++;
                    len[i] = r - p;
                }
            }
        }
    }
};

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T;
    cin>>T;
    map<int,int> mp;
    mp['o']++;
    mp['s']++;
    mp['x']++;
    mp['z']++;
    mp['b']++;
    mp['q']++;
    mp['d']++;
    mp['p']++;
    mp['n']++;
    mp['u']++;
    while(T--){
        string s;
        cin>>s;
        Manacher ma(s);
        int n = s.size();
        int j = 1;
        for(auto &i : s){
            if(!mp.count(i)){
                goto no;
            }
        }
        for(int i=1;i<=n;i++){
            int t = i - j + 1;
            if(ma.len[i+j]>=t) j = i + 1;
        }
        if(j>n) cout<<"Yes"<<endl;
        else goto no;
        if(0) no: cout<<"No"<<endl;
    }
    return 0;
}