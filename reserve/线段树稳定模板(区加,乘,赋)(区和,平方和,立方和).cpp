#include<cstdio>
using namespace std;
#define LL long long
#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r
const int mod=10007;
const int maxn=100000+5;
LL add[maxn<<2],set[maxn<<2],mul[maxn<<2];
LL seg1[maxn<<2],seg2[maxn<<2],seg3[maxn<<2];
void PushUp(int rt)
{
    seg1[rt]=(seg1[rt<<1]+seg1[rt<<1|1])%mod;
    seg2[rt]=(seg2[rt<<1]+seg2[rt<<1|1])%mod;
    seg3[rt]=(seg3[rt<<1]+seg3[rt<<1|1])%mod;
}
void build(int rt,int l,int r)
{
    add[rt]=set[rt]=0;
    mul[rt]=1;
    if(l==r)
    {
        seg1[rt]=seg2[rt]=seg3[rt]=0;
        return;
    }
    int mid=(l+r)>>1;
    build(lson);
    build(rson);
    PushUp(rt);
}
void PushDown(int rt,int x)
{
    if(set[rt])
    {
        set[rt<<1]=set[rt<<1|1]=set[rt];
        add[rt<<1]=add[rt<<1|1]=0;
        mul[rt<<1]=mul[rt<<1|1]=1;
        LL tmp=((set[rt]*set[rt])%mod)*set[rt]%mod;
        seg1[rt<<1]=((x-(x>>1))%mod)*(set[rt]%mod)%mod;
        seg1[rt<<1|1]=((x>>1)%mod)*(set[rt]%mod)%mod;
        seg2[rt<<1]=((x-(x>>1))%mod)*((set[rt]*set[rt])%mod)%mod;
        seg2[rt<<1|1]=((x>>1)%mod)*((set[rt]*set[rt])%mod)%mod;
        seg3[rt<<1]=((x-(x>>1))%mod)*tmp%mod;
        seg3[rt<<1|1]=((x>>1)%mod)*tmp%mod;
        set[rt]=0;
    }
    if(mul[rt]!=1)
    {
        mul[rt<<1]=(mul[rt<<1]*mul[rt])%mod;
        mul[rt<<1|1]=(mul[rt<<1|1]*mul[rt])%mod;
        add[rt<<1]=(add[rt<<1]*mul[rt])%mod;
        add[rt<<1|1]=(add[rt<<1|1]*mul[rt])%mod;
        LL tmp=(((mul[rt]*mul[rt])%mod*mul[rt])%mod);
        seg1[rt<<1]=(seg1[rt<<1]*mul[rt])%mod;
        seg1[rt<<1|1]=(seg1[rt<<1|1]*mul[rt])%mod;
        seg2[rt<<1]=(seg2[rt<<1]%mod)*((mul[rt]*mul[rt])%mod)%mod;
        seg2[rt<<1|1]=(seg2[rt<<1|1]%mod)*((mul[rt]*mul[rt])%mod)%mod;
        seg3[rt<<1]=(seg3[rt<<1]%mod)*tmp%mod;
        seg3[rt<<1|1]=(seg3[rt<<1|1]%mod)*tmp%mod;
        mul[rt]=1;
    }
    if(add[rt])
    {
        add[rt<<1]+=add[rt];
        add[rt<<1|1]+=add[rt];
        LL tmp=(add[rt]*add[rt]%mod)*add[rt]%mod;
        seg3[rt<<1]=(seg3[rt<<1]+(tmp*(x-(x>>1))%mod)+3*add[rt]*((seg2[rt<<1]+seg1[rt<<1]*add[rt])%mod))%mod;
        seg3[rt<<1|1]=(seg3[rt<<1|1]+(tmp*(x>>1)%mod)+3*add[rt]*((seg2[rt<<1|1]+seg1[rt<<1|1]*add[rt])%mod))%mod;
        seg2[rt<<1]=(seg2[rt<<1]+((add[rt]*add[rt]%mod)*(x-(x>>1))%mod)+(2*seg1[rt<<1]*add[rt]%mod))%mod;
        seg2[rt<<1|1]=(seg2[rt<<1|1]+(((add[rt]*add[rt]%mod)*(x>>1))%mod)+(2*seg1[rt<<1|1]*add[rt]%mod))%mod;
        seg1[rt<<1]=(seg1[rt<<1]+(x-(x>>1))*add[rt])%mod;
        seg1[rt<<1|1]=(seg1[rt<<1|1]+(x>>1)*add[rt])%mod;
        add[rt]=0;
    }
}
void update(int rt,int l,int r,int L,int R,int c,int ch)
{
    if(L<=l&&R>=r)
    {
        if(ch==3)
        {
            set[rt]=c;
            add[rt]=0;
            mul[rt]=1;
            seg1[rt]=((r-l+1)*c)%mod;
            seg2[rt]=((r-l+1)*((c*c)%mod))%mod;
            seg3[rt]=((r-l+1)*(((c*c)%mod)*c%mod))%mod;
        }
        else
        if(ch==2)
        {
            mul[rt]=(mul[rt]*c)%mod;
            add[rt]=(add[rt]*c)%mod;
            seg1[rt]=(seg1[rt]*c)%mod;
            seg2[rt]=(seg2[rt]*(c*c%mod))%mod;
            seg3[rt]=(seg3[rt]*((c*c%mod)*c%mod))%mod;
        }
        else
        if(ch==1)
        {
            add[rt]+=c;
            LL tmp=(((c*c)%mod*c)%mod*(r-l+1))%mod; //(r-l+1)*c^3
            seg3[rt]=(seg3[rt]+tmp+3*c*((seg2[rt]+seg1[rt]*c)%mod))%mod;
            seg2[rt]=(seg2[rt]+(c*c%mod*(r-l+1)%mod)+2*seg1[rt]*c)%mod;
            seg1[rt]=(seg1[rt]+(r-l+1)*c)%mod;
        }
        return;
    }
    PushDown(rt,r-l+1);
    int mid=(l+r)>>1;
    if (mid>=L)
        update(lson,L,R,c,ch);
    if (mid<R)
        update(rson,L,R,c,ch);
    PushUp(rt);
}
LL query(int rt,int l,int r,int L,int R,int c)
{
    if(L<=l&&R>=r)
        if(c==1)
            return seg1[rt]%mod;
        else if(c==2)
            return seg2[rt]%mod;
        else
            return seg3[rt]%mod;
    PushDown(rt,r-l+1);
    LL mid=(l+r)>>1,ans=0;
    if (mid>=L)
        ans=(ans+query(lson,L,R,c))%mod;
    if (mid<R)
        ans=(ans+query(rson,L,R,c))%mod;
    return ans%mod;
}
signed main()
{
    int n,m,a,b,c,ch;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0)
            break;
        build(1,1,n);
        while(m--)
        {
            scanf("%d%d%d%d",&ch,&a,&b,&c);
            if(ch!=4)
                update(1,1,n,a,b,c,ch);
            else
                printf("%I64dn",query(1,1,n,a,b,c));
        }
    }
}