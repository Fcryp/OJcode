#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,t;
int main(int argc, char const *argv[])
{
    int k=0;      //循环节计数
    while(scanf("%d %d",&n,&t)!=EOF){
        k=0;
        for(int i=0;i<n;i++){
            k+=pow(t,__gcd(i,n));
        }
        printf("%d",k/n);
        if(n%2==1){
            k+=(pow(t,n/2+1)*n);
        }
        else{
            k+=(pow(t,n/2+1)*(n/2)+pow(t,n/2)*(n/2));
        }
        printf(" %d\n",k/(2*n));
    }
    return 0;
}
