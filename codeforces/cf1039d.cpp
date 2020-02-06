//referenced from https://www.cnblogs.com/Parsnip/p/11415261.html
#include <algorithm>
#include <cstdio>
#include <cstring>
int n;
const int MAXN = 1e5 + 10;
int ver[MAXN], head[MAXN], dp[MAXN], ans[MAXN];
int cursor = 0, cnt;
struct edge
{
    int first;
    int second;
};
struct edge edges[MAXN * 2]; //adjacency table
void treedp(int x, int p, int k)
{
    int max = 0, sec = 0;
    for (int i = head[x]; i > 0; i = edges[i].second)
    {
        int y = edges[i].first;
        if (y== p)
            continue;
        treedp(edges[i].first, x, k);
        if (dp[y] > max)
        {
            sec = max;
            max = dp[y];
        }
        else if (dp[y] > sec)
        {
            sec = dp[y];
        }
    }
    if (max + sec + 1 >= k)
    {
        dp[x] = 0;
        cnt++;
    }
    else
        dp[x] = max + 1;
}
void divide(int st, int ed, int l, int r)
{
    int mid;
    if (st > ed || l > r)
        return;
    if (l == r)
    {
        for (int i = st; i <= ed; i++)
            ans[i] = l;
        return;
    }
    mid = (st + ed) >> 1;
    cnt = 0;
    treedp(1, 0, mid);
    ans[mid] = cnt;
    divide(st, mid - 1, cnt, r);
    divide(mid + 1, ed, l, cnt);
}
void addEdge(int x, int y)
{
    edges[++cursor].first = y;
    edges[cursor].second = head[x];
    head[x] = cursor;
    edges[++cursor].first = x;
    edges[cursor].second = head[y];
    head[y] = cursor;
}
void init()
{
    memset(ver, 0, sizeof(ver));
    memset(head, 0, sizeof(head));
    memset(edges, 0, sizeof(edges));
    memset(dp, 0, sizeof(dp));
    memset(ans, 0, sizeof(ans));
}
int main()
{
    init();
    scanf("%d", &n);
    int x, y;
    for (int i = 1; i < n; i++)
    {
        scanf("%d %d", &x, &y);
        addEdge(x, y);
    }
    divide(1, n, 0, n);
    for (int i = 1; i <= n; i++)
    {
        printf("%d\n", ans[i]);
    }
    return 0;
}