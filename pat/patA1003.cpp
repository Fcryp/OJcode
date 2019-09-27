#include<cstdio>
#include<climits>
using namespace std;
int main(){
    int map[500][500],N[500]={0},dist[500],num[500]={0},w[500]={0};
    bool vis[500]={false};
    int i,j,n,m,c1,c2,row,col,dis;
    int u,min;
    for(i=0;i<500;i++){
        for(j=0;j<500;j++){
            map[i][j]=INT_MAX;
        }
    }
    for(i=0;i<500;i++){
        dist[i]=INT_MAX;
    }
    scanf("%d%d%d%d",&n,&m,&c1,&c2);
    for(i=0;i<n;i++){
       scanf("%d",&N[i]);
    }
    for(i=0;i<m;i++){
        scanf("%d%d%d",&row,&col,&dis);
        map[row][col]=map[col][row]=dis;
    }
    dist[c1]=0;
    w[c1]=N[c1];
    num[c1]=1;
    //Dijkstra
    for(i=0;i<n;i++){
        u=-1;
        min=INT_MAX;
        for(j=0;j<n;j++){
            if(vis[j]==false&&dist[j]<min){
                u=j;
                min=dist[j];
            }
        }
        if(u==-1) return -1;
        vis[u]=true;
        for(j=0;j<n;j++){
            if(vis[j]==false&&map[u][j]!=INT_MAX){
                if(dist[u]+map[u][j]<dist[j]){
                    dist[j]=dist[u]+map[u][j];
                    w[j]=w[u]+N[j];
                    num[j]=num[u];
                }
                else if(dist[u]+map[u][j]==dist[j]){
                    if(w[u]+N[j]>w[j]){
                        w[j]=w[u]+N[j];
                    }
                    num[j]+=num[u];
                }
            }
        }
    }
    printf("%d %d",num[c2],w[c2]);
    return 0;
}