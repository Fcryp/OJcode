#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stack>
using namespace std;
int min_bike=-1;
int cmax;
stack <int> stk_min;
stack <int> stk;
int num_of_bike[510];
int visited[510];
int prepoint[510][510];
int road[510][510];
int prepoint_count[510];
int high_priority(int jump,int n,int cn){
    int sum=cmax/2*jump;
    if(n<sum && cn<sum){
        return n<cn;
    }
    else if(n<sum && cn>=sum){
        return 1;
    }
    else if(n>=sum && cn<sum){
        return 0;
    }
    else if(n>=sum && cn>=sum){
        return n>cn;
    }
    return 2;
}
int dfs(const int &des,int prepoint[][510],int *prepoint_count,int *num_of_bike,int bike,int jmp){
    if(des==0){
        if(min_bike>bike)min_bike=bike;
        stk.push(0);
        stk_min=stk;
        return 0;
    }
    int i;
    for(i=0;i<prepoint_count[des];i++){
        stk.push(des);
        bike += num_of_bike[des];
        jmp++;
        dfs(prepoint[des][i],prepoint,prepoint_count,num_of_bike,bike,jmp);
    }
    return 0;
}
int main(){
    
    int distance[510];
    int i,j,k,src,dst,dis,mindistance=0x7FFFFFFF,minidx,cnt=0,temp;
    int n,sp,m;

    road[0][0]=0;
    memset(visited,0,sizeof(int)*510);
    visited[0]=1;
    memset(num_of_bike,0,sizeof(int)*510);
    memset(road,-1,sizeof(int)*510*510);
    scanf("%d%d%d%d",&cmax,&n,&sp,&m);
    
    for(i=0;i<=n;i++){
        distance[i]=road[0][i];
        prepoint_count[i]=0;
    }
    for(i=1;i<=n;i++){
        scanf("%d",&num_of_bike[i]);
        road[i][i]=0;
    }
    for(i=0;i<m;i++){
        scanf("%d%d%d",&src,&dst,&dis);
        road[src][dst]=dis;
        road[dst][src]=dis;
    }
    for(i=1;i<=n;i++){
        mindistance=__INT32_MAX__;
        for(j=1;j<=n;j++){
            if(distance[j]<mindistance && visited[j]==0){
                minidx=j;
                mindistance=distance[j];
            }
        }
        visited[minidx]=1;
        for(j=0;j<=n;j++){
            if(visited[j]==0 && road[minidx][j]!=-1 && distance[j]>mindistance+road[minidx][j]){
                distance[j]=mindistance+road[minidx][j];
            }
            else if(visited[j]==1 && distance[j]+road[j][minidx]==mindistance){
                prepoint[minidx][prepoint_count[minidx]]=j;
                prepoint_count[j]++;
            }
        }
        if(minidx==sp)break;
    }
    dfs(sp,prepoint,prepoint_count,num_of_bike,0,0);
    printf("%d",min_bike);
    while(!stk_min.empty()){
        printf("%d",stk_min.top());
        stk_min.pop();
    }
    return 0;
}