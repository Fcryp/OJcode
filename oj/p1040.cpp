#include <algorithm>
#include <cstdio>
#include <cstring>
const int MAXN = 45;
const long long LL_LOW_LIMIT = 0x8000000000000000;
int n, count;
int rt[MAXN][MAXN];
long long dp[MAXN][MAXN];
void preorder(int l, int r)
{
    count = 0;
    if (l == r)
    {
        count++;
        printf("%d", l);
        if (count != n)
        {
            printf(" ");
            return;
        }
    }
    else if (l > r)
        return;
    count++;
    printf("%d", rt[l][r]);
    if (count != n)
        printf(" ");
    preorder(l, rt[l][r] - 1);
    preorder(rt[l][r] + 1, r);
}
int main()
{
    scanf("%d", &n);
    for (int i = 0; i <= MAXN; i++)
    {
        for (int j = 0; j <= MAXN; j++)
        {
            dp[i][j] = 1;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &dp[i][i]);
    }
    for (int len = 1; len < n; len++)
    {
        for (int i = 1; i <= n; i++)
        {
            long long temp = LL_LOW_LIMIT;
            int j = i + len;
            if (j <= n)
            {
                for (int k = i; k <= j; k++)
                    if (temp < dp[i][k - 1] * dp[k + 1][j])
                    {
                        temp = dp[i][k - 1] * dp[k + 1][j] + dp[k][k];
                        rt[i][j] = k;
                    }
                dp[i][j] = temp;
            }
            else
                break;
        }
    }
    printf("%lld\n", dp[1][n]);
    preorder(1, n);
}