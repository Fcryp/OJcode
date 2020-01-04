#include <algorithm>
#include <cstdio>
#include <cstring>
const int MOD = 1e9 + 7;
const int MAXN = 2 * 1e5 + 50;
int f[MAXN];
int inf[MAXN];
int w[MAXN];
int num, k;
inline int norm(long long n)
{
    long long ret = n;
    while (ret >= MOD)
    {
        ret -= MOD;
    }
    while (ret < 0)
    {
        ret += MOD;
    }
    return int(ret);
}
inline int mul(int a, int b)
{
    return norm((long long)a * b);
}
inline int pow(int n, int e)
{
    long long ret = 1;
    while (e > 0)
    {
        if (e & 1)
            ret = mul(ret, n);
        n = mul(n, n);
        e = e >> 1;
    }
    return ret;
}
inline int c(int n, int m)
{
    if (n < m || n < 0)
        return 0;
    if (m == 0 || n == m)
        return 1;
    int ret = mul(f[n], mul(inf[m], inf[n - m]));
    return ret;
}
inline int s(int n, int m)
{
    long long ret = 0, temp;
    int sig;
    for (int i = 0; i <= m; i++)
    {
        if (i % 2 == 0)
        {
            sig = 1;
        }
        else
            sig = -1;
        temp = pow(m - i, n);
        ret += sig * mul(c(m, i), temp);
    }
    return mul(ret, inf[m]);
}
void solve()
{
    int p = norm((long long)s(num, k) + mul(num - 1, s(num - 1, k)));
    int sum = 0;
    for (int i = 1; i <= num; i++)
    {
        sum = norm((long long)sum + w[i]);
    }
    printf("%d", mul(p, sum));
}
void precalc()
{
    f[0] = 1;
    inf[0] = 1;
    for (int i = 1; i < MAXN; i++)
    {
        f[i] = mul(f[i - 1], i);
        inf[i] = mul(inf[i - 1], pow(i, MOD - 2)); //Fermat's little theorem
    }
}
int main()
{
    scanf("%d %d", &num, &k);
    for (int i = 1; i <= num; i++)
    {
        scanf("%d", &w[i]);
    }
    precalc();
    solve();
    return 0;
}