#include <cstdio>
#include <cstring>
#define MAXN 50000 + 10
int n, m;
int col[MAXN];
int cnt[MAXN];
int numerator,denominator;
int main()
{
    int l, r;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &col[i]);
    }
    memset(cnt, 0, MAXN*sizeof(int));
    for (int i = 1; i <= m; i++)
    {
        scanf("%d %d", &l, &r);
    }
    return 0;
}