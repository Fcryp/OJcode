#include<cstdio>
using namespace std;
int test_case;
long long way[50];
int main(){
    int m;
    way[1] = 0;
    way[2] = 1;
    way[3] = 2;
    for (int i = 4; i <= 40;i++){
        way[i] = way[i - 1] + way[i - 2];
    }
    scanf("%d", &test_case);
    for (int i = 0; i < test_case;i++){
        scanf("%d", &m);
        printf("%lld\n", way[m]);
    }
    return 0;
}