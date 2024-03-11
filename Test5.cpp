#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<algorithm>
#include<queue>
#include <valarray>
using namespace std;
double calc(double U1,double U2,double U3,double U4){
    double res=U1-U2+U3-U4;
    return abs(res)*0.25;
}
double Kh=205.1;
double Is=5.00;
double cal(double Uh){
    return Uh/(Kh*Is);
}
int main(){

//    vector<double> arr={-21.96,-26.07,24.17,20.07};
//    int st=9;
//    while(cin>>arr[0]>>arr[1]>>arr[2]>>arr[3])
//    cout<<10000*cal(sum(arr[0],arr[1],arr[2],arr[3]))<<endl;
    vector<double> arr1(17);
    for(int i=0;i<17;i++)cin>>arr1[i];
    vector<double> arr2(17);
    for(int i=0;i<17;i++)cin>>arr2[i];
//    for(int i=0;i<17;i++){
//        cout<<i+9<<": "<<arr1[i]+arr2[i]<<endl;
//    }
    vector<double> arr3(17);
    for(int i=0;i<17;i++)cin>>arr3[i];
    for(int i=0;i<17;i++)
    cout<<i+9<<"\t"<<100*abs(arr3[i]-(arr1[i]+arr2[i]))/arr3[i]<<endl;
}