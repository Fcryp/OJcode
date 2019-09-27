#include<cstdio>
#include<queue>
using namespace std;
int main(){
    int hour,minute;
    int i,j;
    int n,m,k,q,checkid,count=0,front;
    int min_wait,min_no;
    int t[1005]={0};
    int end_serv[1005]={0};
    int timebase[25]={0};
    queue<int> windows[25];
    scanf("%d%d%d%d",&n,&m,&k,&q);
    for(i=0;i<k;i++){
        scanf("%d",&t[i]);
    }
    for(i=0;count<n*m && count<k;count++){
        windows[i].push(count);
        timebase[i]+=t[count];
        end_serv[count]=timebase[i];
        i=(i+1)%n;
    }
    while(count<k){
        min_wait=__INT32_MAX__;
        min_no=-1;
        for(i=0;i<n;i++){
            front=windows[i].front();
            if(min_wait>end_serv[front]){
                min_no=i;
                min_wait=end_serv[front];
            }
        }
        windows[min_no].pop();
        windows[min_no].push(count);
        timebase[min_no]+=t[count];
        end_serv[count]=timebase[min_no];
        count++;
    }
    for(i=0;i<q;i++){
        scanf("%d",&checkid);
        if(end_serv[checkid-1]-t[checkid-1]>=540){
            printf("Sorry\n");
        }
        else{
            hour=end_serv[checkid-1]/60;
            minute=end_serv[checkid-1]%60;
            printf("%02d:%02d\n",hour+8,minute);
        }
    }
    return 0;
}