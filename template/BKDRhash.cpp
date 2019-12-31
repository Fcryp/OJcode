#include <algorithm>
#include <cstdio>
#include <cstring>
const int MAXN = 1e6;
const int MOD = 1e18 + 3;
const int BASE = 1009;
int n;        //length of string
char s[MAXN]; //input string
int h[MAXN], pow[MAXN];
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
    long long quotient = ((long double)a * b) / MOD;
    return norm(a * b - quotient * MOD);
}
void preCalc()
{
    n = std::strlen(s);
    h[0] = 0;
    for (int i = 0; i < n; i++)
    {
        h[i + 1] = norm(mul(h[i], BASE) + s[i] - 'a' + 1);
    }
    pow[0] = 1;
    for (int i = 1; i < n; i++)
    {
        pow[i] = mul(pow[i - 1], BASE);
    }
}
long long getHash(int l, int r) //l=left limit in string s(starting from 0),r=right limit add one in string s
{
    return norm(h[r] - mul(h[l], pow[r - l]));
}