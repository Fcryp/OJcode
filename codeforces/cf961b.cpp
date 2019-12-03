/*
 * @Author: n0bdy
 * @Date: 2019-11-28 00:17:35
 * @LastEditTime: 2019-12-03 14:38:06
 * @FilePath: \OJcode\codeforces\cf961b.cpp
 * @Source: https://codeforces.com/contest/961/problem/C
 * @Discription: dp implementation
 */
#include <cstdio>
const int MAXN = 100005;
int n, k;
int a[MAXN], t[MAXN];
int maxtheorems = 0;
int main()
{
    int temp_theorems = 0, temp_diff, max_diff, use_time = 1;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &t[i]);
    }
    for (int i = 1; i <= k; i++)
    {
        temp_theorems += a[i];
        if (t[i])
            maxtheorems += a[i];
    }
    temp_diff = temp_theorems - maxtheorems;
    max_diff = temp_diff;
    for (int i = k + 1; i <= n; i++)
    {
        if (t[i])
            maxtheorems += a[i];
    }
    for (int i = 2; i <= n - k + 1; i++)
    {
        if (!t[i - 1])
            temp_diff -= a[i - 1];
        if (!t[i + k - 1])
            temp_diff += a[i + k - 1];
        if (temp_diff > max_diff)
        {
            use_time = i;
            max_diff = temp_diff;
        }
    }
    maxtheorems += max_diff;
    printf("%d", maxtheorems);
}