#include<cstdio>
using namespace std;
typedef struct Routine{
    int src,dist;
}routine;
int pre[1005];
routine map[10000000];
int Find(int x){
    return pre[x]==x?x:pre[x]=Find(pre[x]);
}
int Union(int x,int y){
    x=Find(x);
    y=Find(y);
    if(x==y) return 1;
    pre[y]=x;
    return 0;
}
int main(){
    int i,j;
    int checkid;
    int n,m,k,sum;      //n:total number of cities  m:number of remaining highways  k:number of cities to be checked
    scanf("%d%d%d",&n,&m,&k);
    for(i=0;i<m;i++){
        scanf("%d%d",&map[i].src,&map[i].dist);
    }
    for(i=0;i<k;i++){
        sum=0;
        scanf("%d",&checkid);
        for(j=0;j<1005;j++){
            pre[j]=j;
        }
        for(j=0;j<m;j++){
            if(map[j].src!=checkid && map[j].dist!=checkid){
                Union(map[j].src,map[j].dist);
            }
        }
        for(j=1;j<=n;j++){
            if(pre[j]==j && j!=checkid){
                sum++;
            }
        }
        printf("%d\n",sum-1);
    }
    return 0;
}