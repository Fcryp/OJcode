#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int strrev_self(char s[]){
    int i;
    char temp;
    int n=strlen(s);
    for(i=0;i<(n/2);i++){
        temp=s[i];
        s[i]=s[n-1-i];
        s[n-1-i]=temp;
    }
    return 0;
}
int is_prime(int num){
    int i,top=sqrt(num);
    for(i=2;i<=top;i++){
        if(num%i==0)return 0;
    }
    return 1;
}
int atoi(char num[],int radix){
    int i,n=0;
    int expon;
    for(i=0;i<strlen(num);i++){
        expon=strlen(num)-i-1;
        n+=(num[i]-'0')*pow(radix,expon);
    }
    return n;
}
int itoa(int num,int radix,char n_rev[]){
    int i=0;
    do{
        n_rev[i]=num%radix+'0';
        i++;
    }while((num/=radix)>0);
    n_rev[i]='\0';
    return 0;
}
int main(int argc, char const *argv[])
{
    int i,j,n,d,reverse;
    char n_re[100]={0};
    while(true){
        scanf("%d",&n);
        if(n<0) break;
        scanf("%d",&d);
        if(n==0||n==1){
            printf("No\n");
            continue;
        }
        if(!is_prime(n))printf("No\n");
        else{
           itoa(n,d,n_re);
           reverse=atoi(n_re,d);
            if(reverse==0||reverse==1){
                printf("No\n");
                continue;
            }
           if(!is_prime(reverse))printf("No\n");
           else printf("Yes\n"); 
        }
    }
    return 0;
}
