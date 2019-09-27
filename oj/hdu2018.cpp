#include<cstdio>
using namespace std;
int main(){
    int n;
    int tempsum[60],tempindex=0;
    while(scanf("%d",&n)){
        if(n==0)
            break;
        else
        {
            if(n>tempindex){
                for (size_t i = tempindex; i <=n ; i++)
                {
                    switch(i){
                        case 1:
                        case 2:
                        case 3:
                            tempsum[i] = i;
                            break;
                        default:
                            tempsum[i] = tempsum[i-1]+tempsum[i-3];
                    }
                }
                printf("%d\n",tempsum[n]);
                tempindex = n;
            }
            else
                printf("%d\n",tempsum[n]);
        }
    }
    return 0;
}