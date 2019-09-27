#include<cstdio>
#include<cstring>
using namespace std;
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
int main(){
    int i,j=0,sum=0;
    char digits[105];
    char ch;
    scanf("%s",digits);
    for(i=0;i<strlen(digits);i++){
        sum+=digits[i]-'0';
    }
    do{
        digits[j]=sum%10+'0';
        j++;
    }while((sum/=10)>0);
    digits[j]='\0';
    strrev_self(digits);
    for(i=0;i<strlen(digits);i++){
        switch(digits[i]){
            case('0'):{
                printf("zero");
                break;
            }
            case('1'):{
                printf("one");
                break;
            }
            case('2'):{
                printf("two");
                break;
            }
            case('3'):{
                printf("three");
                break;
            }
            case('4'):{
                printf("four");
                break;
            }
            case('5'):{
                printf("five");
                break;
            }
            case('6'):{
                printf("six");
                break;
            }
            case('7'):{
                printf("seven");
                break;
            }
            case('8'):{
                printf("eight");
                break;
            }
            case('9'):{
                printf("nine");
                break;
            }
        }
        if(i<strlen(digits)-1) printf(" ");
    }
}