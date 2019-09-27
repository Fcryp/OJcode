#include<cstdio>
using namespace std;
int main(){
    int k1,k2,i,index,count=0;
    float s[2][1005]={0},value;
    scanf("%d",&k1);
    for(i=0;i<k1;i++){
        scanf("%d%f",&index,&value);
        s[0][index]=value;
    }
    scanf("%d",&k2);
    for(i=0;i<k2;i++){
        scanf("%d%f",&index,&value);
        s[1][index]=value;
    }
    for(i=0;i<1005;i++){
        if(s[0][i]!=0||s[1][i]!=0){
            s[0][i]+=s[1][i];
            if(s[0][i]!=0)count++;
        }
    }
    printf("%d",count);
    for(i=1004;i>=0;i--){
        if(s[0][i]!=0){
            printf(" %d %.1f",i,s[0][i]);
        }
    }
    getchar();
}