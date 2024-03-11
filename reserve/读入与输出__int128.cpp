#include<bits/stdc++.h>
#define int __int128
#define LL __int128
using namespace std;
inline __int128 read()
{
    __int128 X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}

//输出：
inline void print(__int128 x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
signed main(){
    int n=read();
    print(n);
}