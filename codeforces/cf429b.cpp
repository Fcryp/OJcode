#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
long long gym[1005][1005];
long long maxpath[4][1005][1005];
int main()
{
    int n, m;
    long long ans = 0;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%lld", &gym[i][j]);
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 1005; j++)
        {
            maxpath[i][j][0] = 0;
            maxpath[i][0][j] = 0;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            maxpath[0][i][j] = max(maxpath[0][i - 1][j], maxpath[0][i][j - 1]) + gym[i][j];
        }
    }
    for (int i = n; i >= 1; i--)
    {
        for (int j = 1; j <= m; j++)
        {
            maxpath[1][i][j] = max(maxpath[1][i + 1][j], maxpath[1][i][j - 1]) + gym[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = m; j >= 1; j--)
        {
            maxpath[2][i][j] = max(maxpath[2][i][j + 1], maxpath[2][i - 1][j]) + gym[i][j];
        }
    }
    for (int i = n; i >= 1; i--)
    {
        for (int j = m; j >= 1; j--)
        {
            maxpath[3][i][j] = max(maxpath[3][i + 1][j], maxpath[3][i][j + 1]) + gym[i][j];
        }
    }
    for (int i = 2; i < n; i++)
    {
        for (int j = 2; j < m; j++)
        {
            ans = max(ans, maxpath[0][i - 1][j] + maxpath[3][i + 1][j] + maxpath[1][i][j - 1] + maxpath[2][i][j + 1]);
            ans = max(ans, maxpath[0][i][j - 1] + maxpath[3][i][j + 1] + maxpath[1][i + 1][j] + maxpath[2][i - 1][j]);
        }
    }
    printf("%lld", ans);
}