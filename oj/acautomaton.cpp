#include<cstdio>
#include<cstring>
using namespace std;
const int NUM_OF_LETTER=26;
const int TARGET_LENGTH=1000;
const int ROOT=0;
int m=1;
int numofpattern;      //n--模式串个数
char pattern[20][20];   //模式串
char target[TARGET_LENGTH];     //目标串
int head,tail;
int q[500];     //求解fail需要的队列
struct tree{
    char ch;
    int son,next,father,danger,suffix;
}a[2501];
void insert(char *s,int l,int t,int x){
    int i;
    if(a[x].danger)
        return;
    if(a[x].son==0){
        m++;
        a[x].son=m;
        a[m].father=x;
        a[m].ch=s[t];
        if(t+1==l)
            a[m].danger=1;
        else insert(s,l,t+1,m);
    }
    else{
        i=a[x].son;
        while(1){
            if(a[i].next==0||a[i].ch==s[t])
                break;
            i=a[i].next;
        }
        if(a[i].ch==s[t]&&t+1==l)
            a[i].danger=1;
        else if(a[i].ch==s[t])
            insert(s,l,t+1,i);
        else{
            m++;
            a[i].next=m;
            a[m].father=x;
            a[m].ch=s[t];
            if(t+1==l)
                a[m].danger=1;
            else 
                insert(s,l,t+1,m);
        }
    }
}
int child(int x,char ch){
    int i;
    i=a[x].son;
    while(i!=0){
        if(a[i].ch==ch)break;
        i=a[i].next;
    }
    if(i!=0)
        return i;
    else if(x==1)
        return 1;
    else
        return child(a[i].suffix,ch);
}
void build(){
    int i,l,r;
    l=r=1;
    q[1]=1;
    a[1].suffix=1;
    if(a[l].son==0)
        return ;
    while(l<=r){
        if(!a[q[l]].danger){
            i=a[q[l]].son;
            while(1){
                r++;
                q[r]=i;
                i=a[i].next;
                if(i==0)
                    break;
            }
        }
        l++;
    }
    for(i=2;i<=r;i++){
        if(a[q[i]].father==1){
            a[q[i]].suffix=1;
            continue;
        }
        a[q[i]].suffix=child(a[a[q[i]].father].suffix,a[q[i]].ch);
        if(a[a[q[i]].suffix].danger)
            a[q[i]].danger=1;
    }
}
int main(int argc, char const *argv[]){
    int i,j;
    scanf("%d",&numofpattern);
    for(i=0;i<numofpattern;i++){
        scanf("%s",&pattern[i]);
        insert(pattern[i],strlen(pattern[i]),0,1);
    }
    build();
    return 0;
}
