#include <cstdio>
using namespace std;
long long a2, n, m;
long long vector[4];
long long matrix[4][4];
int init(long long *p)
{
    vector[0] = ((*p) * (*p)) % m;
    vector[1] = 1;
    vector[2] = (*p) % m;
    vector[3] = (1 + vector[0]) % m;
    *p =(*p*2)%m;
    matrix[0][0] = ((*p) * (*p)) % m;
    matrix[0][1] = 1;
    matrix[0][2] = (*p) % m;
    matrix[0][3] = matrix[0][0];
    matrix[1][0] = 1;
    matrix[1][1] = 0;
    matrix[1][2] = 0;
    matrix[1][3] = 1;
    matrix[2][0] = (-2 * (*p) % m + m) % m;
    matrix[2][1] = 0;
    matrix[2][2] = -1 + m;
    matrix[2][3] = (-2 * (*p) % m + m) % m;
    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;
    return 0;
}
int matrixmuti(long long a[][4], long long b[][4])
{
    int i, j, k;
    long long ans[4][4];
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            ans[i][j] = 0;
            for (k = 0; k < 4; k++)
            {
                ans[i][j] = (ans[i][j]+a[i][k] * b[k][j]) % m;
            }
        }
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            a[i][j] = ans[i][j];
        }
    }
    return 0;
}
int pow(long long x[][4], long long n)
{
    long long ans[4][4];
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (i == j)
                ans[i][j] = 1;
            else
                ans[i][j] = 0;
        }
    }
    while (n != 0)
    {
        if (n & 1)
        {
            matrixmuti(ans, x);
        }
        matrixmuti(x, x); //指数每次循环都将基数递增，分别是x^(2^0),x^(2^1),x^(2^2)...以此类推
        n >>= 1;
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            x[i][j] = ans[i][j];
        }
    }
    return 0;
}
int main(int argc, char const *argv[])
{
    int num;
    int ans = 0;
    scanf("%d", &num);
    for (int i = 0; i < num; i++)
    {
        ans = 0;
        scanf("%lld%lld%lld", &a2, &n, &m);
        init(&a2);
        pow(matrix, n - 2);
        for (int j = 0; j < 4; j++)
        {
            ans = (ans+vector[j] * matrix[j][3])%m;
        }
        ans = (ans % m + m) % m;
        printf("%d\n", ans);
    }
    return 0;
}