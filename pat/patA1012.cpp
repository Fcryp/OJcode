#include<cstdio>
#include<cstring>
using namespace std;
typedef struct studentGrade{
    char id[10];
    int c,m,e,a;
}grade;
int main(){
    char tempid[10];
    int i,j,k;
    int n,m,rank,minrank=__INT32_MAX__;
    char course;
    grade rec[3000];
    scanf("%d%d",&n,&m);
    for(i=0;i<n;i++){
        scanf("%s%d%d%d",rec[i].id,&rec[i].c,&rec[i].m,&rec[i].e);
        rec[i].a=rec[i].c+rec[i].m+rec[i].e;
    }
    for(i=0;i<m;i++){
        scanf("%s",tempid);
        for(j=0;strcmp(tempid,rec[j].id)&&j<n;j++);
        if(j==n){
            printf("N/A\n");
            continue;
        }
        rank=1;
        minrank=__INT32_MAX__;
        for(k=0;k<n;k++){
            if(rec[j].a<rec[k].a)rank++;
        }
        if(rank<minrank){
            minrank=rank;
            course='A';
        }
        rank=1;
        for(k=0;k<n;k++){
            if(rec[j].c<rec[k].c)rank++;
        }
        if(rank<minrank){
            minrank=rank;
            course='C';
        }
        rank=1;
        for(k=0;k<n;k++){
            if(rec[j].m<rec[k].m)rank++;
        }
        if(rank<minrank){
            minrank=rank;
            course='M';
        }
        rank=1;
        for(k=0;k<n;k++){
            if(rec[j].e<rec[k].e)rank++;
        }
        if(rank<minrank){
            minrank=rank;
            course='E';
        }
        printf("%d %c\n",minrank,course);
    }
}