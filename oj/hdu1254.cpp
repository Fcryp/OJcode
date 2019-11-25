/*
 * @Author: n0bdy
 * @Date: 2019-11-22 15:53:38
 * @LastEditTime: 2019-11-25 22:57:14
 * @FilePath: \OJcode\oj\hdu1254.cpp
 * @Source: http://acm.hdu.edu.cn/showproblem.php?pid=1254
 * @Discription: conbination of DFS and BFS
 */
#include <cstdio>
#include <cstring>
#include <queue>
typedef struct State
{
    int row;
    int col;
    int hamal_row;
    int hamal_col;
} state;
const int DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int t, m, n, minpath = 0;
int maze[10][10];
int push_row, push_col;
bool dfs_vis[10][10];
bool bfs_vis[10][10];
std::queue<state> que;
bool dfs(int row, int col) //find a way from (row,col) to (dst_x,dst_y)
{
    int dst_row, dst_col;
    //printf("[%d %d]", row, col);
    if (row == push_row && col == push_col)
        return true;
    dfs_vis[row][col] = true;
    for (int i = 0; i < 4; i++)
    {
        dst_row = row + DIR[i][0];
        dst_col = col + DIR[i][1];
        if (dst_row < 1 || dst_col < 1 || dst_row > m || dst_col > n || dfs_vis[dst_row][dst_col] || maze[dst_row][dst_col] == 1 || maze[dst_row][dst_col] == 2)
            continue;
        else if (dfs(dst_row, dst_col))
            return true;
        else
            continue;
    }
    dfs_vis[row][col] = false;
    return false;
}
void bfs(int row, int col, int hamal_start_row, int hamal_start_col)
{
    int dst_row, dst_col, hamal_row, hamal_col;
    int pre_row = row, pre_col = col;
    state temp;
    int cntdown = 1;
    temp.row = row;
    temp.col = col;
    temp.hamal_row = hamal_start_row;
    temp.hamal_col = hamal_start_col;
    que.push(temp);
    for (int i = 0; i < 10; i++)
    {
        memset(bfs_vis[i], false, sizeof(bfs_vis[i]));
    }
    while (!que.empty())
    {
        maze[pre_row][pre_col] = 0;
        maze[que.front().row][que.front().col] = 2;
        pre_row = que.front().row;
        pre_col = que.front().col;
        hamal_row = que.front().hamal_row;
        hamal_col = que.front().hamal_col;
        printf("(%d,%d):",pre_row, pre_col);
        for (int i = 0; i < 4; i++)
        {
            dst_row = pre_row + DIR[i][0];
            dst_col = pre_col + DIR[i][1];
            if (dst_row < 0 || dst_col < 0 || dst_row > m || dst_col > n || maze[dst_row][dst_col] == 1 || bfs_vis[dst_row][dst_col])
                continue;
            push_row = pre_row - DIR[i][0];
            push_col = pre_col - DIR[i][1];
            if (push_row < 0 || push_col < 0 || push_row > m || push_col > n || maze[push_row][push_col] == 1)
                continue;
            printf("[%d,%d](%d)", dst_row, dst_col,minpath);
            for (int j = 0; j < 10; j++)
            {
                memset(dfs_vis[j], false, sizeof(dfs_vis[j]));
            }
            if (dfs(hamal_row, hamal_col))
            {
                if (maze[dst_row][dst_col] == 3){
                    minpath++;
                    return;
                }
                temp.row = dst_row;
                temp.col = dst_col;
                temp.hamal_row = pre_row;
                temp.hamal_col = pre_col;
                que.push(temp);
            }
        }
        que.pop();
        cntdown--;
        if (!cntdown)
        {
            cntdown = que.size();
            hamal_row = push_row;
            hamal_col = push_col;
            minpath++;
        }
    }
    minpath = -1;
    return;
}
int main()
{
    int box_row, box_col, hamal_row, hamal_col;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        scanf("%d %d", &m, &n);
        minpath = 0;
        for (int j = 1; j <= m; j++)
        {
            for (int k = 1; k <= n; k++)
            {
                scanf("%d", &maze[j][k]);
                if (maze[j][k] == 2)
                {
                    box_row = j;
                    box_col = k;
                }
                else if (maze[j][k] == 4)
                {
                    hamal_row = j;
                    hamal_col = k;
                }
            }
        }
        bfs(box_row, box_col, hamal_row, hamal_col);
        printf("%d", minpath);
    }
    return 0;
}