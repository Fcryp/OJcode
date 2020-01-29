#include <algorithm>
#include <cstdio>
#include <cstring>
const int MAXN = 6010;
int n;
int dp[MAXN][2], pa[MAXN];
bool vis[MAXN];
void tree_dp(int index)
{
    vis[index] = true;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i] && pa[i] == index)
        {
            tree_dp(i);
            dp[index][0] += std::max(dp[i][1], dp[i][0]);
            dp[index][1] += dp[i][0];
        }
    }
}
int main()
{
    int l, k, root = 0;
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 0;
            dp[i][1] = 1;
        }
        memset(pa, 0, sizeof(pa));
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &dp[i][1]);
        }
        while (scanf("%d %d", &l, &k) && (l || k))
        {
            root = pa[l] = k;
        }
        while (pa[root])
        {
            root = pa[root];
        }
        tree_dp(root);
        printf("%d\n", std::max(dp[root][0], dp[root][1]));
    }
}