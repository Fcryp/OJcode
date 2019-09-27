#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
typedef struct Time{
    int hh,mm,ss;
    int process;
}time;
int TimeCmp(const Time &t1,const Time &t2){
    int diff=0;
    diff=(t1.hh-t2.hh)*3600+(t1.mm-t2.mm)*60+t1.ss-t2.ss;
    return diff;
}
int TimeCpy(Time &t1,const Time &t2){
    t1.hh=t2.hh;
    t1.mm=t2.mm;
    t1.ss=t2.ss;
    t1.process=t2.process;
    return 0;
}
int Process(Time &t1){
    t1.mm=(t1.mm+t1.process)%60;
    t1.hh=(t1.hh+t1.process/60);
    return 0;
}
int adjust(Time pt[],const int &i,const int &n){
    int min_no=i;
    int lchild=i*2+1;
    int rchild=i*2+2;
    time temp;
    TimeCpy(temp,pt[i]);
    if(i==0){
        lchild=1;
        rchild=2;
    }
    if(rchild>=n) rchild=-1;
    if(TimeCmp(pt[i],pt[lchild])>0)min_no=lchild;
    if(rchild!=-1 && TimeCmp(pt[min_no],pt[rchild])>0)min_no=rchild;
    TimeCpy(pt[i],pt[min_no]);
    TimeCpy(pt[min_no],temp);
    return 0;
}
Time dequesort(Time pt[],const int &n){
    int i;
    time t;
    int non_leaf=n/2-1;
    for(i=non_leaf;i>=0;i--){
        adjust(pt,i,n);
    }
    TimeCpy(t,pt[0]);
    return t;
}
int main(int argc, char const *argv[])
{
    int i,j;
    int k,n,min_no,count=0,wait;
    long long int sum=0;
    double average=0;
    int process[10005]={0};
    time temp;
    time t[10005],windows[105]={8,0,0};
    time mintime={24,60,60},maxlimit={17,0,0};
    memset(t,0,sizeof(time)*10005);
    memset(t,0,sizeof(time)*105);
    scanf("%d %d",&n,&k);
    for(i=0;i<n;i++){
        scanf("%d:%d:%d %d",&t[i].hh,&t[i].mm,&t[i].ss,&t[i].process);
    }
    for(i=0;i<k;i++){
        windows[i].hh=8;
        windows[i].mm=0;
        windows[i].ss=0;
    }
    for(j=0;j<n;j++){
        for(i=0;i<k;i++){
            if(TimeCmp(mintime,windows[i])>0){
                TimeCpy(mintime,windows[i]);
                min_no=i;
            }
        }
        temp=dequesort(t+j,n-j);
        if(TimeCmp(temp,maxlimit)>0) break;
        if(TimeCmp(windows[min_no],temp)<0){
            TimeCpy(windows[min_no],temp);
            Process(windows[min_no]);
            TimeCpy(mintime,windows[min_no]);
        }
        else {
            wait=TimeCmp(windows[min_no],temp);
            sum+=wait;
            windows[min_no].process=temp.process;
            Process(windows[min_no]);
            TimeCpy(mintime,windows[min_no]);
        }
    }
    if(j!=0)average=(sum/60.0)/(float)j;
    else average=0;
    printf("%.1f",average);
    return 0;
}
