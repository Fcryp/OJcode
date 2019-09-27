#include<stdio.h>
#define MAXSIZE 100
#define MAXPATH 99999

int path[MAXSIZE][MAXSIZE];
int distance[MAXSIZE];
int prev[MAXSIZE];
int visited[MAXSIZE];
int num_of_nodes,num_of_paths,sourcenode;
typedef struct Edge{
    int u,v;
    int weight;
}edge,* pedge;
edge edgeset[5*MAXSIZE];
typedef struct Stack{
    int stack[MAXSIZE];
    int top;
}stk,*pstk;
int stkinit(pstk stk){
    stk->top=0;
    return 0;
}
int stkpush(pstk stk,int data){
    stk->stack[stk->top]=data;
    stk->top++;
    return 0;
}
int stktop(pstk stk){
    return stk->stack[stk->top-1];
}
int stkpop(pstk stk){
    stk->top--;
}
int init(){
    int i,j;
    for(i=0;i<MAXSIZE;i++){
        visited[i]=0;
        prev[i]=-1;
        distance[i]=MAXPATH;
    }
    for(i=0;i<MAXSIZE;i++){
        for(j=0;j<MAXSIZE;j++){
            if(i==j)path[i][j]=0;
            else path[i][j]=MAXPATH;
        }
    }
    return 0;
}
/*打印路径函数实现*/
int show(){
    int i,j;
    stk stack;
    for(i=0;i<num_of_nodes;i++){
        stkinit(&stack);
        j=prev[i];
        if(j==-2){
            printf("node %d cannot be reached\n",i);
            continue;
        }
        printf("node %d distance %d:",i,distance[i]);
        while(j!=-1){
            stkpush(&stack,j);
            j=prev[j];
        }
        while(stack.top>=1){
            printf("%d->",stktop(&stack));
            stkpop(&stack);
        }
        printf("%d\n",i);
    }
}
/*Dijkstra算法实现*/
int dijkstra(){
    visited[sourcenode]=1;
    int i,j,minlen=MAXPATH,minno=-1;
    for(j=0;j<num_of_nodes;j++){
        minlen=MAXPATH;
        minno=-1; 
        for(i=0;i<num_of_nodes;i++){//每一轮找到未访问的节点中距离源点最近的节点
            if(visited[i]==0 && distance[i]<minlen){  
                minlen=distance[i];
                minno=i;
            }
        }
        if(minno==-1){ //找不到源点可达的点
            for(i=0;i<num_of_nodes;i++){
                if(visited[i]==0){//对源点不可达的点的前缀做处理
                    prev[i]=-2;
                }
            }
            break;
        }
        else {
            visited[minno]=1;
            for(i=0;i<num_of_nodes;i++){
                if(visited[i]==0 && (distance[minno]+path[minno][i]<distance[i])){
                    distance[i]=distance[minno]+path[minno][i];
                    prev[i]=minno;
                }
            }
        }
    }
    return 0; 
} 
/*Bellman_ford算法实现*/
int bellman_ford(){
    int i,j,u,v;
    for(i=0;i<num_of_nodes-1;i++){
        for(j=0;j<num_of_paths;j++){
            u=edgeset[j].u;
            v=edgeset[j].v;
            if(distance[v]>(distance[u]+edgeset[j].weight)){//每一轮松弛
                distance[v]=distance[u]+edgeset[j].weight;
                prev[v]=u;
            }
        }
    }
    for(i=0;i<num_of_paths;i++){    //检测是否存在负权回路
        u=edgeset[i].u;
        v=edgeset[i].v;
        if(distance[v]>(distance[u]+edgeset[i].weight)){
            return 1;
        }
    }
    for(i=0;i<num_of_nodes;i++){
        if(distance[i]>=MAXPATH)prev[i]=-2;
    }
    return 0;
}
int main(int argc, char const *argv[])
{
    int i,j,way,src,dst,dis;
    init();
    printf("How many nodes(1~100)>");
    scanf("%d",&num_of_nodes);
    printf("How many paths>");
    scanf("%d",&num_of_paths);
    printf("Input the path(src dst distance),number start from 0>");
    for(i=0;i<num_of_paths;i++){
        scanf("%d %d %d",&src,&dst,&dis);
        path[src][dst]=dis;
        edgeset[i].u=src;
        edgeset[i].v=dst;
        edgeset[i].weight=dis;
    }
    printf("Which source node do you want to calculate>");
    scanf("%d",&sourcenode);
    printf("Which algorithm do you want to use(1.Dijkstra 2.Bellman-Ford)>");
    scanf("%d",&way);
    if(way==1){
        for(i=0;i<num_of_nodes;i++){
            distance[i]=path[sourcenode][i];
            if(path[sourcenode][i]<MAXPATH)prev[i]=sourcenode;
        }
        prev[sourcenode]=-1;
        dijkstra();
    }
    else if(way==2){
        for(i=0;i<num_of_nodes;i++){
            distance[i]=MAXPATH;
            prev[i]=sourcenode;
        }
        prev[sourcenode]=-1;
        distance[sourcenode]=0;
        if(bellman_ford()){
            printf("Negative weight loop");
            return 0;
        }
    }
    else printf("Error argument.");
    show();
    return 0;
}
