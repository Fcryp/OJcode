#include <algorithm>
#include <cstdio>
const int MAXN = 2e5 + 50;
int n;
int x[MAXN];
long long t;
long long a[MAXN];
long long ans[MAXN];
int main()
{
    int pre = 1, temp;
    scanf("%d %lld", &n, &t);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x[i]);
        if (x[i] < pre || x[i] < i)
        {
            printf("No\n");
            return 0;
        }
        pre = x[i];
    }
    x[0] = x[n + 1] = 0;
    a[n + 1] = a[n] + 2;
    temp = 0;
    for (int i = n; i >= 0; i--)
    {
        if (x[i] != x[i + 1])
        {
            ans[i] = a[i + 1] + t - 1;
            if (x[i + 1] != temp)
            {
                printf("No\n");
                return 0;
            }
            temp = i;
        }
        else
        {
            ans[i] = a[i + 1] + t;
            if (ans[i] >= ans[i + 1])
            {
                printf("No\n");
                return 0;
            }
        }
    }
    printf("Yes\n%lld", ans[1]);
    for (int i = 2; i <= n; i++)
    {
        printf(" %lld", ans[i]);
    }
    return 0;
}