#include<cstdio>
using namespace std;
int main(){
    int k,i,j,temp=0,tempend=0,tempstart=0,maxsum=-1,maxstart=0,maxend=0,tailstart=0;
    int seq[10005]={0};
    scanf("%d",&k);
    for(i=0;i<k;i++){
        scanf("%d",&seq[i]);
        temp+=seq[i];
        if(temp<0){
            temp=0;
            tempstart=i+1;
            tempend=tempstart;
        }
        else{
            tempend=i;
            if(temp>maxsum){
                maxsum=temp;
                maxstart=tempstart;
                maxend=tempend;
            }
        }
    }
    if(maxsum<0){
        if(k>0)
            printf("%d %d %d",0,seq[0],seq[k-1]);
        else printf("0 0 0");
    }
    else {
        printf("%d %d %d",maxsum,seq[maxstart],seq[maxend]);
    }
}