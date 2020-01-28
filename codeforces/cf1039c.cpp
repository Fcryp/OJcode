#include <algorithm>
#include <cstdio>
#include <map>
const long long MOD = 1e9 + 7;
const int MAXN = 500010;
int n, k, m;
long long key[MAXN];
std::map<long long, int> groupmap[MAXN];
long long pow(int x)
{
    int temp = x;
    long long ans = 1;
    long long base = 2;
    while (temp != 0)
    {
        if (temp & 1)
        {
            ans = (ans * base) % MOD;
        }
        base = (base * base) % MOD;
        temp >>= 1;
    }
    return ans;
}
int find(int x, long long key)
{
    return groupmap[x][key] == x ? x : groupmap[x][key] = find(groupmap[x][key], key);
}
int main()
{
    std::map<long long, int> xmap;
    std::map<long long, int>::iterator iter;
    int u, v, gu, gv;
    long long x, ans = 0;
    scanf("%d %lld %d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &key[i]);
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);
        x = key[u] ^ key[v];
        iter = xmap.find(x);
        if (groupmap[u][x] == 0)
            groupmap[u][x] = u;
        if (groupmap[v][x] == 0)
            groupmap[v][x] = v;
        if (iter == xmap.end())
        {
            xmap.insert(std::map<long long, int>::value_type(x, n - 1));
            groupmap[v][x] = u;
        }
        else
        {
            gu = find(u, x);
            gv = find(v, x);
            if (gu != gv)
            {
                if (iter->second > 1)
                {
                    iter->second--;
                    groupmap[find(v, x)][x] = find(u, x);
                }
            }
        }
    }
    for (iter = xmap.begin(); iter != xmap.end(); iter++)
    {
        ans = (ans + pow(iter->second) % MOD) % MOD;
    }
    ans = (ans + pow(n) * (pow(k) - xmap.size() + MOD) % MOD) % MOD;
    printf("%lld\n", ans);
}