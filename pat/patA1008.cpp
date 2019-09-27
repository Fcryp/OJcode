#include<cstdio>
using namespace std;
int main(){
    int i,n,nowlev=0,sumtime=0;
    int request[105]={0};
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&request[i]);
    }
    for(i=0;i<n;i++){
        if(nowlev>=request[i]){
            sumtime+=(nowlev-request[i])*4+5;
        }
        else{
            sumtime+=(request[i]-nowlev)*6+5;
        }
        nowlev=request[i];
    }
    printf("%d",sumtime);
}