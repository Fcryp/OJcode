/*
 * @Author: n0bdy
 * @Date: 2019-12-03 14:42:56
 * @LastEditTime : 2019-12-19 10:58:21
 * @FilePath: \OJcode\codeforces\cf961d.cpp
 * @Source: https://codeforces.com/contest/961/problem/E
 * @Discription: geometry
 */
#include <cstdio>
typedef struct coordinate
{
    long long x;
    long long y;
} coord;
int n;
const int MAXN = 1e5 + 10;
coord points[MAXN];
bool isOntheSameline(int pointa, int pointb, int pointc)
{
    long long dx1 = points[pointb].x - points[pointa].x;
    long long dy1 = points[pointb].y - points[pointa].y;
    long long dx2 = points[pointc].x - points[pointb].x;
    long long dy2 = points[pointc].y - points[pointb].y;
    return (dy1 * dx2 == dy2 * dx1);
}
bool judge(int pointa, int pointb, int pointc)
{
    int c = pointc;
    int d = -1;
    for (int i = 0; i < n; i++)
    {
        if (!isOntheSameline(pointa, pointb, i))
        {
            if (d == -1 && i != c)
            {
                d = i;
            }
            else if (!isOntheSameline(c, d, i))
            {
                return false;
            }
        }
    }
    return true;
}
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%lld %lld", &points[i].x, &points[i].y);
    }
    int a = 0;
    int b = 1;
    int c = -1;
    for (int i = 2; i < n; i++)
    {
        if (!isOntheSameline(a, b, i))
        {
            c = i;
            break;
        }
    }
    if (c == -1)
    {
        printf("YES");
        return 0;
    }
    if (judge(a, b, c) || judge(b, c, a) || judge(a, c, b))
        printf("YES");
    else
        printf("NO");
    return 0;
}