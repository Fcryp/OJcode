/*
 * @Author: n0bdy
 * @Date: 2019-11-04 00:02:35
 * @LastEditTime: 2019-11-06 16:08:45
 * @FilePath: \OJcode\oj\hdu4747.cpp
 * @Source: http://acm.hdu.edu.cn/showproblem.php?pid=4747
 * @Discription: mex segment-tree
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 200005;
int n;
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