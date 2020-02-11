#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
const int MAXN = 1e5 + 10;
int n, r, t, cursor;
typedef struct Edge
{
    int y;
    int next;
} edge;
edge edges[MAXN];
int head[2 * MAXN];
std::queue<int> bfsq;
void init();
void addEdge(int x, int y)
{
    edges[++cursor].y = y;
    edges[cursor].next = head[x];
    head[x] = cursor;
}
/*
//method_1 O((n+m)logn)
int pa[MAXN][25], deep[MAXN], cnt[MAXN];
void init()
{
    cursor = 0;
}
void bfs()
{
    int x, count;
    bfsq.push(r);
    deep[r] = 1;
    while (!bfsq.empty())
    {
        x = bfsq.front();
        bfsq.pop();
        for (int i = head[x]; i; i = edges[i].next)
        {
            int y = edges[i].y;
            if (deep[y])
                continue;
            count = 0;
            bfsq.push(y);
            deep[y] = deep[x] + 1;
            pa[y][0] = x;
            for (int j = 1; pa[pa[y][j - 1]][j - 1]; j++)
            {
                pa[y][j] = pa[pa[y][j - 1]][j - 1];
                count++;
            }
            cnt[y] = count;
        }
    }
}
int lca(int x, int y)
{
    int count = 0;
    if (deep[x] > deep[y]) //keep y>=x
    {
        std::swap(x, y);
    }
    int diff = deep[y] - deep[x];
    while (diff != 0)
    {
        if (diff & 0x1)
            y = pa[y][count];
        count++;
        diff >>= 1;
    }
    printf("%d\n",y);
    if (x == y)
    {
        return y;
    }
    for (int i = cnt[x]; i >= 0; i--)
    {
        if (pa[x][i] != pa[y][i])
        {
            x = pa[x][i];
            y = pa[y][i];
        }
    }
    return pa[x][0];
}
*/
//method_2 Tarjan
typedef struct Query
{
    int num;
    int y;
    int next;
} query;
query queries[MAXN];
int queryhead[MAXN], querycursor;
int sig[MAXN], ans[MAXN], dsu[MAXN];
void init()
{
    cursor = 0;
    querycursor = 0;
    for (int i = 1; i <= n; i++)
    {
        dsu[i] = i;
    }
}
void addQuery(int x, int y, int num)
{
    queries[++querycursor].y = y;
    queries[querycursor].next = head[x];
    queries[querycursor].num = num;
    queryhead[x] = querycursor;
}
int find(int x)
{
    return dsu[x] == x ? x : (dsu[x] = find(dsu[x]));
}
void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    dsu[x] = y;
}
void tarjan(int r)
{
    if (!sig[r])
        sig[r] = 1;
    for (int i = head[r]; i; i = edges[i].next)
    {
        int y = edges[i].y;
        if (sig[y])
            continue;
        tarjan(y);
        merge(y, r);
    }
    sig[r] = 2;
    for (int i = queryhead[r]; i; i = queries[i].next)
    {
        int y = queries[i].y;
        int num = queries[i].num;
        if (sig[y] == 2)
        {
            ans[num] = find(y);
        }
    }
}
int main()
{
    int x, y, q1, q2, qnum;
    scanf("%d%d%d", &n, &r, &qnum);
    init();
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &x, &y);
        addEdge(x, y);
        addEdge(y, x);
    }
    //bfs();
    printf("start query:\n");
    for (int i = 1; i <= qnum; i++)
    {
        scanf("%d%d", &q1, &q2);
        addQuery(q1, q2, i);
        addQuery(q2, q1, i);
        //printf("%d\n", lca(q1, q2));
    }
    tarjan(1);
    for (int i = 1; i <= qnum; i++)
    {
        printf("%d ", ans[i]);
    }
}