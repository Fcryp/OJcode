#include<cstdio>
using namespace std;
typedef struct Records{
    char id[20];
    char sign_in_time[20];
    char sign_out_time[20];
}record;
int main(){
    int i,j,m,unlock_index=0,lock_index=0;
    scanf("%d",&m);
    record rec[1000];
    for(i=0;i<m;i++){
        scanf("%s%s%s",&rec[i].id,&rec[i].sign_in_time,&rec[i].sign_out_time);
    }
    for(i=1;i<m;i++){
        j=0;
        while(rec[i].sign_in_time[j]!='\0'){
            if(rec[i].sign_in_time[j]<rec[unlock_index].sign_in_time[j]){
                unlock_index=i;
                break;
            }
            else if(rec[i].sign_in_time[j]==rec[unlock_index].sign_in_time[j]){
                j++;
                continue;
            }
            else break;
        }
    }
    for(i=1;i<m;i++){
        j=0;
        while(rec[i].sign_out_time[j]!='\0'){
            if(rec[i].sign_out_time[j]>rec[lock_index].sign_out_time[j]){
                lock_index=i;
                break;
            }
            else if(rec[i].sign_out_time[j]==rec[lock_index].sign_out_time[j]){
                j++;
                continue;
            }
            else break;
        }
    }
    printf("%s %s",rec[unlock_index].id,rec[lock_index].id);
}