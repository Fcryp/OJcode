#include<cstdio>
#include<cstring>
void strrev_self(char s[]){
    int i;
    char temp;
    int n=strlen(s);
    for(i=0;i<(n/2);i++){
        temp=s[i];
        s[i]=s[n-1-i];
        s[n-1-i]=temp;
    }
}
void itoa(int n,char s[]){
    int i=0,sig=0;
    if(n<0){
        n=-n;
        sig=1;
    }
    do{
        s[i]='0'+n%10;
        i++;
    }while((n/=10)>0);
    if(sig==1)s[i]='-';
    s[++i]='\0';
    strrev_self(s);
}
int main(){
    int i,j,k,n,m,cnt=0;
    scanf("%d%d",&n,&m);
    char s[50]={0};
    n=n+m;
    itoa(n,s);
    printf("%s\n",s);
    if(n<0) k=1;
    else k=0;
    for(i=strlen(s)-1;i>k;i--){
        cnt++;
        if(cnt==3&&i!=k){
            s[strlen(s)]='\0';
            for(j=strlen(s);j>=i;j--){
                s[j+1]=s[j];
            }
            s[i]=',';
            cnt=0;
        }
    } 
    printf("%s",s);
}