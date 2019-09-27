#include <cstdio>
#include<stack>
using namespace std;
/*
stack<int> treestk;
int dandc()
{
    int test_case, start, end,top,count;
    scanf("%d", &test_case);
    for (int i = 0; i < test_case; i++)
    {
        scanf("%d", &start);
        scanf("%d", &end);
        count = 0;
        treestk.push(end);
        while(!treestk.empty()){
            top = treestk.top();
            treestk.pop();
            if((top-1)>start)
                treestk.push(top-1);
            else if((top-1)==start)
                count++;
            if((top-2)>start)
                treestk.push(top-2);
            else if((top-2)==start)
                count++;
        }
        printf("%d\n", count);
    }
    return 0;
}
*/
long long int res[60];
int dp(){
    int test_case, start, end;
    scanf("%d", &test_case);  
    for (int i = 0; i < test_case; i++)
    {
        scanf("%d", &start);
        scanf("%d", &end);
        int distance=end-start;
        res[1] = 1;
        res[2] = 2;
        for (int j = 3; j <=distance ;j++){
            res[j] = res[j - 1] + res[j - 2];
        }
        printf("%lld\n", res[distance]);
    }
    return 0;
}
int main(){
    dp();
    return 0;
}