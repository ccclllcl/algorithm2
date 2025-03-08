#include<iostream>
#include<time.h>
#include<random>
using namespace std;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> distribution(1, 100000000);
struct CHREQ{
    int key,x,r,size,val;
}Q[1000100];
int cc;
int rt1;
int newnode(int v){
    Q[++cc].val=v;
    Q[cc].size=1;
    int tp=distribution(gen);
    Q[cc].key=tp;
    Q[cc].x= Q[cc].r=0;
    return cc;
}
void pushup(int h){
    Q[h].size= Q[Q[h].x].size + Q[Q[h].r].size + 1;
}
void split(int h,int v,int &x,int &y){
    if(!h){
        x=y=0;
        return;
    }
    if(Q[h].val>v){
        y=h;
        split(Q[h].x, v, x, Q[h].x);
    }
    else{
        x=h;
        split(Q[h].r,v,Q[h].r,y);
    }
    pushup(h);
}
int merge(int x,int y){
    if(!x||!y)return x+y;
    if(Q[x].key < Q[y].key){
        Q[x].r= merge(Q[x].r,y);
        pushup(x);
        return x;
    }
    Q[y].x= merge(x, Q[y].x);
    pushup(y);
    return y;
}
void Insert(int v){
    int x,y,z;
    split(rt1, x, x, y);
    z= newnode(x);
    rt1= merge(merge(x, z), y);
}
int get_Kth(int k,int p=rt1){
    if(Q[Q[p].x].size == k - 1)return Q[p].val;
    if(Q[Q[p].x].size > k - 1)return get_Kth(k, Q[p].x);
    return get_Kth(k - Q[Q[p].x].size - 1, Q[p].r);
}
int get_lesV(int v){
    int x,y;
    split(rt1, v, x, y);
    int res=Q[x].size;
    rt1= merge(x, y);
    return res;
}

int main(){
    int _;
    cin>>_;
    Insert(-2147483647);
    Insert(2147483647);
    while(_--){
        int op,x;
        cin>>op>>x;
        if(op==1){
            cout<<get_lesV(x-1)<<endl;
        }else if(op==2){
            cout<<get_Kth(x+1)<<endl;
        }else if(op==3){
            cout<<get_Kth(get_lesV(x-1))<<endl;
        }else if(op==4){
            cout<<get_Kth(get_lesV(x)+1)<<endl;
        }else{
            Insert(x);
        }
    }
}