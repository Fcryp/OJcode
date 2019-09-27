#include<cstdio>
#include<queue>
using namespace std;
int main(){
    int i,j,n,m,id,k,cont=0,nextlev=1;
    int tree[105][105]={0};
    queue<int> q;
    scanf("%d %d",&n,&m);
    if(n==0)return 0;
    for(i=0;i<m;i++){
        scanf("%d %d",&id,&k);
        tree[id][0]=k;
        for(j=0;j<k;j++){
            scanf("%d",&tree[id][j+1]);
        }
    }
    q.push(1);
    while(!q.empty()){
        for(i=1;i<=*tree[q.front()];i++){
            q.push(tree[q.front()][i]);
        }
        if(*tree[q.front()]==0){
            cont++;
        }
        if(nextlev==q.front()){
            if(q.size()==1) printf("%d",cont);
            else printf("%d ",cont);
            cont=0;
            nextlev=q.back();
        }
        q.pop();
    }
    return 0;
}