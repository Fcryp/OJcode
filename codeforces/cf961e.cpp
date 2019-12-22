/*
 * @Author: n0bdy
 * @Date: 2019-12-19 11:02:02
 * @LastEditTime : 2019-12-22 14:51:08
 * @FilePath: \OJcode\codeforces\cf961e.cpp
 * @Source: http:https://codeforces.com/contest/961/problem/F
 * @Discription：segment-tree,B.I.T(Binary Indexed Tree)
 */
#include <algorithm>
#include <cstdio>
#include <vector>
const int MAXN = 2e5 + 10;
int n;
int a[MAXN],c[MAXN];
std::vector<int> v[MAXN];
long long sum(int i)
{
    long long res=0;
    while(i){
        res += c[i];
        i -= i & (-i);
    }
    return res;
}
void update(int i, int x)
{
    while (i <= n)
    {
        c[i] += x;
        i += i & (-i);
    }
}
int main()
{
    long long ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        if (a[i] > n)
            a[i] = n;
        v[std::min(i - 1, a[i])].push_back(i);
    }
    for (int i = 1; i <= n; i++)
    {
        update(a[i],1);
        for (std::vector<int>::iterator iter = v[i].begin(); iter != v[i].end();iter++){
            ans += sum(n) - sum(*iter-1);
        }
    }
    printf("%lld", ans);
    return 0;
}