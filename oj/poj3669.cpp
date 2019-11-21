/*
 * @Author: n0bdy
 * @Date: 2019-11-20 01:13:15
 * @LastEditTime: 2019-11-22 02:05:33
 * @FilePath: \OJcode\oj\poj3669.cpp
 * @Source: http://poj.org/problem?id=3669
 * @Discription: 
 */
#include <cstdio>
#include <cstring>
#include <queue>
const int FOREVER = 0x3f3f3f3f;
typedef struct Coordinate
{
    int x;
    int y;
} coordinate;
int m, time = 0;
int ST[305][305], EAT[305][305]; //strike time(ST) earliest arrival time(EAT)
int dir[5][2] = {{0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}};
std::queue<coordinate> q;
void bfs()
{
    int x, y, nextstep = 1;
    coordinate temp;
    while (!q.empty())
    {
        nextstep--;
        for (int i = 1; i <= 4; i++)
        {
            x = q.front().x + dir[i][0];
            y = q.front().y + dir[i][1];
            if (x < 0 || y < 0)
                continue;
            if (ST[y][x] > time + 1 && time + 1 < EAT[y][x])
            {
                temp.x = x;
                temp.y = y;
                q.push(temp);
                EAT[y][x] = time + 1;
                if (ST[y][x] == FOREVER)
                {
                    time++;
                    return;
                }
            }
        }
        q.pop();
        if (nextstep==0)
        {
            nextstep = q.size();
            time++;
        }
    }
    time = -1;
    return;
}
int main()
{
    int strike_x, strike_y, strike_time;
    scanf("%d", &m);
    for (int i = 0; i < 305; i++)
    {
        memset(ST[i], FOREVER, sizeof(ST[i]));
        memset(EAT[i], FOREVER, sizeof(EAT[i]));
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &strike_x, &strike_y, &strike_time);
        for (int j = 0; j <= 4; j++)
            if ((strike_x + dir[j][0] >= 0) && (strike_y + dir[j][1] >= 0) && (strike_time < ST[strike_y + dir[j][1]][strike_x + dir[j][0]]))
                ST[strike_y + dir[j][1]][strike_x + dir[j][0]] = strike_time;
    }
    coordinate origin;
    origin.x = 0;
    origin.y = 0;
    q.push(origin);
    if (ST[0][0] <= 0)
    {
        printf("-1");
        return 0;
    }
    bfs();
    printf("%d", time);
    return 0;
}