/*
 * @Author: n0bdy
 * @Date: 2019-11-04 00:02:35
 * @LastEditTime: 2019-11-15 14:28:47
 * @FilePath: \OJcode\oj\hdu4747.cpp
 * @Source: http://acm.hdu.edu.cn/showproblem.php?pid=4747
 * @Discription: mex 1.iterative method2.segment-tree
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
const int MAXN = 200005;
int n;
/*iterative method*/
/*
int a[MAXN], last[MAXN], mp[MAXN];
int main()
{
    while (scanf("%d", &n) && n != 0)
    {
        for (int i = 1; i <= n; i++)
            scanf("%d", a + i);
        long long ans = 0;
        long long temp = 0, pre;
        memset(last, 0, sizeof(last));
        memset(mp, 0, sizeof(mp));
        for (int i = 1; i <= n; i++)
        {
            if (a[i] <= n) //in cases that greater than n,the mex doesn't change
            {
                pre = last[a[i]];
                last[a[i]] = i;
                for (int j = a[i]; j <= n; j++)
                {
                    if (j)
                        mp[j] = min(mp[j - 1], last[j]);
                    else
                        mp[j] = last[j];
                    if (mp[j] > pre)
                    {
                        temp += mp[j] - pre;
                    }
                    else
                        break;
                }
            }
            ans += temp;
        }
        printf("%I64d\n", ans);
    }
}
*/
/*segment-tree*/
int a[MAXN], vis[MAXN], mex[MAXN];
int head[MAXN], next[MAXN];
int maxmex[MAXN << 2], lazy[MAXN << 2];
long long sum[MAXN << 2];
void pushup(int rt)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    maxmex[rt] = std::max(maxmex[rt << 1], maxmex[rt << 1 | 1]);
}
void pushdown(int rt, int len)
{
    if (lazy[rt])
    {
        lazy[rt << 1] = lazy[rt << 1 | 1] = 1;
        sum[rt << 1] = (long long)maxmex[rt] * (len - (len >> 1));
        sum[rt << 1 | 1] = (long long)maxmex[rt] * (len >> 1);
        maxmex[rt << 1] = maxmex[rt << 1 | 1] = maxmex[rt];
        lazy[rt] = 0;
    }
}
void build(int l, int r, int rt)
{
    lazy[rt] = 0;
    if (l == r)
    {
        sum[rt] = maxmex[rt] = mex[l];
        return;
    }
    int m = (l + r) >> 1;
    build(l, m, rt << 1);
    build(m + 1, r, rt << 1 | 1);
    pushup(rt);
}
void update(int updatel, int updater, int val, int l, int r, int rt)
{
    if (updatel <= l && updater >= r)
    {
        lazy[rt] = 1;
        maxmex[rt] = val;
        sum[rt] = (long long)val * (r - l + 1);
        return;
    }
    pushdown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (updatel <= m)
        update(updatel, updater, val, l, m, rt << 1);
    if (updater > m)
        update(updatel, updater, val, m + 1, r, rt << 1 | 1);
    pushup(rt);
}
int query(int val, int l, int r, int rt)
{
    if (l == r)
        return l;
    pushdown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (val < maxmex[rt << 1])
        return query(val, l, m, rt << 1);
    else
        return query(val, m + 1, r, rt << 1 | 1);
}
int main()
{
    int cursor = 0;
    long long ans;
    memset(vis, 0, sizeof(vis));
    while (scanf("%d", &n) && n != 0)
    {
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", a + i);
            if (a[i] > n)
                a[i] = n + 1;
            vis[a[i]] = 1;
            for (int j = cursor; j <= n; j++)
            {
                if (!vis[j])
                {
                    mex[i] = j;
                    cursor = j;
                    break;
                }
            }
        }
        memset(head, 0x3f, sizeof(head)); //0x3f3f3f3f close to 0x7fffffff and 0x3f3f3f3f prevents overflows.
        for (int i = n; i > 0; i--)
        {
            next[i] = head[a[i]];
            head[a[i]] = i;
        }
        build(1, n, 1);
        ans = sum[1];
        for (int i = 1; i <= n; i++)
        {
            update(i, i, 0, 1, n, 1);
            if (maxmex[1] > a[i])
            {
                int pos = query(a[i], 1, n, 1);
                if (pos < next[i])
                    update(pos, next[i] - 1, a[i], 1, n, 1);
            }
            ans += sum[1];
        }
        printf("%lld\n", ans);
    }
    return 0;
}