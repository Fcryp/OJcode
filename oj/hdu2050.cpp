#include <cstdio>
using namespace std;
int main()
{
    int test_case, n;
    long long splitway[10005];
    scanf("%d", &test_case);
    splitway[0] = 1;
    for (size_t j = 1; j <= 10000; j++)
    {
        splitway[j] = 4 * (j - 1) + splitway[j - 1] + 1;
    }
    for (size_t i = 0; i < test_case; i++)
    {
        scanf("%d", &n);
        printf("%lld\n", splitway[n]);
    }
    return 0;
}