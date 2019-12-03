/*
 * @Author: n0bdy
 * @Date: 2019-11-28 11:37:49
 * @LastEditTime: 2019-12-03 14:40:08
 * @FilePath: \OJcode\codeforces\cf961c.cpp
 * @Source: https://codeforces.com/contest/961/problem/C
 * @Discription: implementation
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
const int MAXN = 105;
int n;
int chessboard[4][MAXN][MAXN];
int recolor[4][2];
int main()
{
    int tempval = 1, temprecolor = 0, minrecolor = 400000;
    char tempchar;
    scanf("%d", &n);
    for (int i = 0; i < 4; i++)
    {
        memset(recolor[i], 0, sizeof(recolor[i]));
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= n; k++)
            {
                scanf(" %c", &tempchar);
                if (tempchar == '1')
                    chessboard[i][j][k] = 1;
                else if (tempchar == '0')
                    chessboard[i][j][k] = 0;
                else
                    printf("error:%x\n", tempchar);
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        tempval = 1;
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= n; k++)
            {
                if (chessboard[i][j][k] == tempval)
                    recolor[i][0]++;
                else
                    recolor[i][1]++;
                tempval = !tempval;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            temprecolor += recolor[i][1] + recolor[j][1];
            for (int k = 0; k < 4; k++)
            {
                if (k != i && k != j)
                {
                    temprecolor += recolor[k][0];
                }
            }
            if (temprecolor < minrecolor)
            {
                minrecolor = temprecolor;
            }
            temprecolor = 0;
        }
    }
    printf("%d", minrecolor);
    return 0;
}