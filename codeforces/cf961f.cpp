/*
 * @Author: n0bdy
 * @Date: 2019-12-31 14:54:15
 * @LastEditTime : 2019-12-31 16:16:43
 * @FilePath: \OJcode\codeforces\cf961f.cpp
 * @Source: https://codeforces.com/contest/961/problem/F
 * @Discription: string hash,BiS
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
const int MAXN = 1e6 + 100;
const long long MOD = 1e18 + 3;
const long long BASE = 1009;
int n;
char s[MAXN];
long long h[MAXN], pow[MAXN];
int l[MAXN], mx[MAXN];
long long norm(long long num)
{
    while (num >= MOD)
    {
        num -= MOD;
    }
    while (num < 0)
    {
        num += MOD;
    }
    return num;
}
long long mul(long long a, long long b)
{
    long long quotient = (long double)(a)*b / MOD;
    return norm(a * b - quotient * MOD);
}
void preCalc()
{
    h[0] = 0;
    for (int i = 0; i < n; i++) //BKDRhash
    {
        h[i + 1] = norm(mul(h[i], BASE) + s[i] - 'a' + 1);
    }
    pow[0] = 1;
    for (int i = 1; i < n; i++)
    {
        pow[i] = mul(pow[i - 1], BASE); //if we do not use mul(),pw[i-1]*BASE will overflow
    }
}
long long getHash(int l, int r)
{
    return norm(h[r] - mul(h[l], pow[r - l]));
}
/*
void solve(){       //solution-1
    int c1, c2, lf, rg, mid;
    memset(mx, 0, sizeof(mx));
    for (int i = 0; i < n / 2; i++)
    {
        c1 = i;
        c2 = n - i - 1;
        if (s[c1] != s[c2])
        {
            l[i] = -1;
            continue;
        }
        lf = 0, rg = i + 1;
        while (rg - lf > 1)
        {
            mid = (lf + rg) >> 1;
            if (getHash(c1 - mid, c1 + mid + 1) != getHash(c2 - mid, c2 + mid + 1))
                rg = mid;
            else
                lf = mid;
        }
        l[i] = lf;
    }
    for (int i = 0; i < n / 2; i++) //multi-center cases
    {
        if (l[i] < 0)
            continue;
        mx[i - l[i]] = std::max(mx[i - l[i]], 2 * l[i] + 1);
    }
    for (int i = 1; i < n / 2; i++) //covering cases
    {
        mx[i] = std::max(mx[i], mx[i - 1] - 2);
    }
    for (int i = 0; i < (n + 1) / 2; i++)
    {
        if (i)
            printf(" ");
        if (!mx[i])
            mx[i] = -1;
        printf("%d", mx[i]);
    }
    puts("");
}
*/
void solve() //solution-2
{
    int i;
    int c1 = (n - 1) / 2, c2 = n / 2;
    mx[0] = -1;
    for (i = 0; i < (n + 1) / 2; i++)
    {
        int lf = c1 - i, rg = c2 + i;
        mx[i + 1] = mx[i] + 2;
        while (mx[i + 1] > 0)
        {
            if (lf == rg)
            {
                mx[i + 1] = -1;
                continue;
            }
            if (getHash(lf, lf + mx[i + 1]) != getHash(rg - mx[i + 1] + 1, rg + 1))
            {
                mx[i + 1] -= 2;
            }
            else
            {
                break;
            }
        }
    }
    for (int j = i; j > 0; j--)
    {
        if (j != i)
            printf(" ");
        printf("%d", mx[j]);
    }
    puts("");
}
int main()
{
    scanf("%d\n%s", &n, s);
    preCalc();
    solve();
    return 0;
}