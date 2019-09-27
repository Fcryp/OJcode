#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const double EPS = 1e-8;
const double INF = 1e100;
const int MAXN = 210;
const int MAXM = 5;
/*
这种单纯形法实现不同于常规的方法，在存储和转换方面都做了一定的优化
主要区别如下：
1、没有将基变量放在等式左边，而是采用同在等式一边的方式，这样不用在系数矩阵输入的时候移项取负
2、取得结果之后系数需要移项，所以结果取负数
3、没有采用辅助变元的方法得到初始可行基，但是采用了类似的思路
4、由于基变量系数矩阵永远是0/1，所以不作记录，只记录非基变量的系数矩阵，同时采用B,N存储基变量和非基变量
*/
//m是总行数，n是总列数，存储的时候从1开始存储，0行存储目标函数，0列存储约束常量，row是出基变量，col是入基变量
void pivot(int m, int n, double matrix[MAXM][MAXN], int B[MAXM], int N[MAXN], int row, int col)
{
    int i, j;
    swap(B[row], N[col]);
    matrix[row][col] = 1 / matrix[row][col];
    for (j = 0; j <= n; j++)
    {
        if (j != col)
            matrix[row][j] *= matrix[row][col];
    }
    for (i = 0; i <= m; i++)
    {
        if (i != row)
        {
            for (j = 0; j <= n; j++)
            {
                if (j != col)
                {
                    matrix[i][j] -= matrix[i][col] * matrix[row][j];
                }
            }
            matrix[i][col] = -matrix[i][col] * matrix[row][col];
        }
    }
}
int feasible(int m, int n, double matrix[MAXM][MAXN], int B[MAXM], int N[MAXN])
{
    int i, j;
    int minrow=0, mincol=0;
    double p,v;
    for (i = 1, p = INF; i <= m; i++)
    {
        //rand()%1是为了防止退化无限迭代
        if (matrix[i][0] < p &&(!minrow||rand()&1))
            p = matrix[minrow = i][0];
    }
    if (p > EPS)
        return 1; //初始可行基建立完毕
    for (j = 1, p = 0; j <= n; j++)
    {
        if (matrix[minrow][j] < p && (!mincol||rand()&1))
            p = matrix[minrow][mincol = j];
    }
    if(p>-EPS)
        return 0; //问题无解
    /*另一种初始可行基实现
        pivot(m,n,matrix,B,N,minrow,mincol);
    */
    p = matrix[minrow][0] / matrix[minrow][mincol];
    while(1){
        for (i = minrow+1; i <= m;i++){
            if(matrix[i][mincol]>EPS){
                v = matrix[i][0] / matrix[i][mincol];
                if(v<p){
                    p = v;
                    minrow = i;
                }
            }
        }
        pivot(m,n,matrix,B,N,minrow,mincol);
    }
}
/*
soulution返回所有变量的解，res返回最优值
返回值为1，表示存在有限最优解
返回值为0，表示约束条件不可行
返回值为-1，表示存在无限最优解
*/
int simplex(int m,int n,double matrix[MAXM][MAXN],double solution[MAXM+MAXN],double &res)
{
    int B[MAXM], N[MAXN], row=0, col=0, i;
    double v, p;
    for (i = 1; i <= n;i++){
        N[i] = i;
    }
    for (i = 1; i <= m;i++){
        B[i] = i + n;
    }
    if(!feasible(m,n,matrix,B,N)){
        printf("Infesible");
        return 0;
    }
    while(1){
        for (i = 1; i <= n;i++){
            if(matrix[0][i]>EPS){
                col = i; //blande规则
                break;
            }
        }
        if(!col){
            for (i = 1; i <= n;i++){
                solution[N[i]] = 0;
            }
            for (i = 1; i <= m;i++){
                solution[B[i]] = matrix[i][0];
            }
            res = -matrix[0][0];
            return 1;
        }
        for (p = INF, i = 1; i <= m;i++){
            if(matrix[i][col]>EPS){
                v = matrix[i][0] / matrix[i][col];
                if(v<p){
                    p = v;
                    row = i;
                }
            }
        }
        if(p==INF){
            return -1;
        }
        pivot(m, n, matrix, B, N, row, col);
    }
}