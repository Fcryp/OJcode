/*
 * @Author: n0bdy
 * @Date: 2019-11-27 15:11:09
 * @LastEditTime: 2019-11-27 23:59:05
 * @FilePath: \OJcode\codeforces\cf961a.cpp
 * @Source: https://codeforces.com/contest/961/problem/A
 * @Discription: implementation
 */
#include <cstdio>
#include <cstring>
int n, m;
int squarescount_col[1005], squarescount_row[1005];
int main()
{
    int col, point = 0;
    scanf("%d %d", &n, &m);
    memset(squarescount_col, 0, sizeof(squarescount_col));
    memset(squarescount_row, 0, sizeof(squarescount_row));
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &col);
        squarescount_col[col]++;
        squarescount_row[squarescount_col[col] + point]++;
        if (squarescount_row[1 + point] == n)
        {
            point++;
            for (int j = 1; j <= n; j++)
            {
                squarescount_col[j]--;
            }
        }
    }
    printf("%d", point);
}