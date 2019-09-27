#include<cstdio>
using namespace std;
int main(){
    int i,j,maxno=0,minno=0;
    float odd[3][3],max,min,profit=1;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            scanf("%f",&odd[i][j]);
        }
    }
    for(i=0;i<3;i++){
        max=0;
        min=__FLT_MAX__;
        for(j=0;j<3;j++){
            if(odd[i][j]>max){
                max=odd[i][j];
                maxno=j;
            }
        }
        switch(maxno){
            case(0):{
                printf("W ");
                break;
            }
            case(1):{
                printf("T ");
                break;
            }
            case(2):{
                printf("L ");
                break;
            }
        }
        profit*=max;
    }
    printf("%.2f",(profit*0.65-1.0)*2.0);
}