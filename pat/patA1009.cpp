#include<cstdio>
using namespace std;
int main(){
    int k1,k2,i,j,index,cont=0;
    float n1[1005]={0},n2[1005]={0},res[2005]={0};
    scanf("%d",&k1);
    for(i=0;i<k1;i++){
        scanf("%d",&index);
        scanf("%f",&n1[index]);
    }
    scanf("%d",&k2);
    for(i=0;i<k2;i++){
        scanf("%d",&index);
        scanf("%f",&n2[index]);
    }

    for(i=0;i<1005;i++){
        for(j=0;j<1005;j++){
            if(n1[i]!=0&&n2[j]!=0){
                res[i+j]+=n1[i]*n2[j];
            }
        }
    }
    for(i=0;i<2005;i++){
        if(res[i]!=0)cont++;
    }
    printf("%d",cont);
    for(i=2004;i>=0;i--){
        if(res[i]!=0)printf(" %d %.1f",i,res[i]);
    }
}