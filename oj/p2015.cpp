#include <algorithm>
#include <cstdio>
#include <cstring>
const int MAXN = 105;
int n, q;
int tree[MAXN][MAXN], dp[MAXN][MAXN], fork[MAXN][5], vis[MAXN], apples[MAXN];
void init()
{
    for (int i = 0; i < MAXN; i++)
    {
        for (int j = 0; j < MAXN; j++)
        {
            tree[i][j] = -1;
            dp[i][j] = 0;
        }
        for (int j = 0; j < 5; j++)
        {
            fork[i][j] = -1;
        }
    }
    memset(vis, 0, sizeof(vis));
}
void buildtree(int i)
{
    int isfork = 0;
    vis[i] = 1;
    for (int j = 1; j <= n; j++)
    {
        if (tree[i][j] >= 0 && !vis[j])
        {
            isfork++;
            fork[i][isfork] = j;
            apples[j] = tree[i][j];
            buildtree(j);
            if (isfork == 2)
                return;
        }
    }
    return;
}
void treedp(int rt, int cnt)
{
    if (cnt <= 0)
        return;
    else if (fork[rt][1] == -1 && fork[rt][2] == -1)
        dp[rt][cnt] = apples[rt];
    else
        for (int i = 0; i < cnt; i++)
        {
            treedp(fork[rt][1], i);
            treedp(fork[rt][2], cnt - i - 1);
            dp[rt][cnt] = std::max(dp[rt][cnt], dp[fork[rt][1]][i] + dp[fork[rt][2]][cnt - i - 1] + apples[rt]);
        }
}
int main()
{
    int src, dst, weight;
    scanf("%d %d", &n, &q);
    init();
    for (int i = 1; i < n; i++)
    {
        scanf("%d %d %d", &src, &dst, &weight);
        tree[src][dst] = weight;
        tree[dst][src] = weight;
    }
    buildtree(1);
    treedp(1, q + 1);
    printf("%d", dp[1][q + 1]);
}