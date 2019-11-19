/*
 * @Author: n0bdy
 * @Date: 2019-11-16 20:13:38
 * @LastEditTime: 2019-11-20 01:09:58
 * @FilePath: \OJcode\oj\poj3009.cpp
 * @Source: http://poj.org/problem?id=3009
 * @Discription: DFS or BFS
 */
#include <cstdio>
const int MAXN = 25;
const int way[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int width, height, minmoves;
int sx, sy;
int board[MAXN][MAXN];
void DFS(int x, int y, int cnt)
{
    if (cnt >= 10)
        return;
    int dx, dy, flag;
    for (int i = 0; i < 4; i++)
    {
        dx = x + way[i][0];
        dy = y + way[i][1];
        while (1)
        {
            if (dx < 1 || dx > width || dy < 1 || dy > height)
            {
                flag = 0;
                break;
            }
            else if (board[dy][dx] == 1)
            {
                flag = 1;
                break;
            }
            else if (board[dy][dx] == 3)
            {
                if (++cnt < minmoves)
                    minmoves = cnt;
                return;
            }
            dx += way[i][0];
            dy += way[i][1];
        }
        if(!flag)
            continue;
        if(flag){
            board[dy][dx] = 0;
            dx -= way[i][0];
            dy -= way[i][1];
            if(dx==x&&dy==y){       //When the stone stands still, you can make it moving by throwing it. You may throw it to any direction unless it is blocked immediately
                board[dy+way[i][1]][dx+way[i][0]] = 1;
                continue;
            }
            DFS(dx, dy, cnt+1);
            board[dy+way[i][1]][dx+way[i][0]] = 1;
        }
    }
}
int main()
{
    while (scanf("%d %d", &width, &height) == 2 && width != 0 && height != 0)
    {
        minmoves = 11;
        for (int i = 1; i <= height; i++)
        {
            for (int j = 1; j <= width; j++)
            {
                scanf("%d", &board[i][j]);
                if (board[i][j] == 2)
                {
                    sx = j;
                    sy = i;
                }
            }
        }
        //printf("x:%d\ny:%d\n", sx,sy);
        DFS(sx, sy, 0);
        if(minmoves>=11)
            printf("-1\n");
        else
        {
            printf("%d\n",minmoves);
        }
    }
}