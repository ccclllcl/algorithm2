#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=1e7;
LL mod=1e9+7;
const int MAXLEN=1e5+5;//所处理字符串的最大长度
//后缀自动机:len表示以i为endpoint的字符串集合中的最大长度,link表示将i的后缀字符串缩短后第一次出现其他位置有相同的后缀的endpoint代表
//next表示i的转移边
//后缀自动机表示一个字符串S,每一条以0为起点的路径(不一定要到头)代表S的一个不同的子串
struct state{
    int len,link;
    std::map<int,int> next;
};
state st[MAXLEN*2];
int sz=0,last=0;
void sam_init(){
    st[0].len=0;
    st[0].link=-1;
    last=0;
}
LL ans=0;//实时记录不同子串的个数
void sam_extend(int c){
    int cur = ++sz;
    st[cur].len=st[last].len+1;
    int p=last;
    while(p!=-1&&!st[p].next.count(c)){
        st[p].next[c]=cur;
        p=st[p].link;
    }
    if(p==-1){
        st[cur].link=0;
    }else{
        int q=st[p].next[c];
        if(st[p].len+1==st[q].len){
            st[cur].link=q;
        }else{
            int clone=++sz;
            st[clone].len=st[p].len+1;
            st[clone].next=st[q].next;
            st[clone].link=st[q].link;
            while(p!=-1&&st[p].next[c]==q){
                st[p].next[c]=clone;
                p=st[p].link;
            }
            st[q].link=st[cur].link=clone;
        }
    }
    last=cur;
    ans+=st[cur].len-st[st[cur].link].len;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    sam_init();
    for(int i=0;i<n;i++){
        int v;
        cin>>v;
        sam_extend(v);
        cout<<ans<<'\n';
    }
}