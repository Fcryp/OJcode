#include <cmath>
#include <cstdio>
#include<cstring>
using namespace std;
const long double EPS = 1e-12; //EPS用来控制精度，保证主元素不至于特别小，关于具体的精度问题详见https://wenku.baidu.com/view/7c69b72fff00bed5b9f31de2.html
int jnum, rnum;
int fSgn(double x)
{
    int res=(x > EPS) - (x < -EPS);
    return res;
}
typedef struct joint
{
    double x;
    double y;
    double z;
} Joint;
typedef struct rod
{
    int endpoint1;
    int endpoint2;
} Rod;
joint joints[110];
Rod temprod;
double coefficient[310][110];
double tempmatrix[310][110];
int varnum, equationnum, sculptureid;
int fInit()
{
    int i, j;
    for (i = 0; i < 310; i++)
    {
        for (j = 0; j < 110; j++)
        {
            coefficient[i][j] = 0;
        }
    }
    varnum = 1;
    equationnum = 0;
    sculptureid = 1;
    return 0;
}
bool fIsStatic(bool *istable)
{
    int row, col, maxrow;
    int i, j;
    double temp;
    double temprow[110];
    for (row = 0, col = 1; row < equationnum && col < varnum; row++, col++)
    {
        maxrow = row;
        for (i = row + 1; i < equationnum; i++)
        {
            if (fSgn(fabs(coefficient[i][col]) - fabs(coefficient[maxrow][col]))>0)
                maxrow = i;
        }
        if (maxrow != row)
        {
            memcpy(temprow, coefficient[row],sizeof(double)*varnum);
            memcpy(coefficient[row], coefficient[maxrow], sizeof(double)*varnum);
            memcpy(coefficient[maxrow], temprow, sizeof(double)*varnum);
        }
        if (fSgn(fabs(coefficient[row][col])) == 0)
        {
            row--;
            continue;
        }
        for (i = row + 1; i < equationnum; i++)
        {
            if (fSgn(coefficient[i][col]) != 0)
            {
                temp = coefficient[i][col] / coefficient[row][col];
                for (j = col; j < varnum; j++)
                {
                    coefficient[i][j] = coefficient[i][j] - coefficient[row][j] * temp;
                }
                coefficient[i][0] = coefficient[i][0] - coefficient[row][0] * temp;
            }
        }
    }
    for (i = row; i < equationnum; i++)
    {
        if (fSgn(coefficient[i][0]) != 0)
            return false;
    }
    for (i = 0; i < equationnum; i++)
    {
        for (j = 1; j < varnum; j++)
        {
            if (fSgn(coefficient[i][j]) != 0)
                break;
        }
        if (j == varnum)
        {
            *istable = false;
            break;
        }
    }
    if (i == equationnum)
        *istable = true;
    return true;
}
int main()
{
    int i, casenum = 1;
    bool newflag, stableflag;
    while (true)
    {
        fInit();
        scanf("%d %d", &jnum, &rnum);
        if (!jnum && !rnum)
            break;
        for (i = 1; i <= jnum; i++)
        {
            scanf("%lf %lf %lf", &joints[i].x, &joints[i].y, &joints[i].z);
        }
        for (i = 0; i < rnum; i++)
        {
            scanf("%d %d", &temprod.endpoint1, &temprod.endpoint2);
            newflag = false;
            if (joints[temprod.endpoint1].z)
            { //由于当节点在地上时会产生抵消力，所以方程一定有解故不讨论，这里只讨论空中节点
                tempmatrix[3 * temprod.endpoint1][varnum] = joints[temprod.endpoint1].x - joints[temprod.endpoint2].x;
                tempmatrix[3 * temprod.endpoint1 + 1][varnum] = joints[temprod.endpoint1].y - joints[temprod.endpoint2].y;
                tempmatrix[3 * temprod.endpoint1 + 2][varnum] = joints[temprod.endpoint1].z - joints[temprod.endpoint2].z;
                newflag = true;
            }
            if (joints[temprod.endpoint2].z)
            {
                tempmatrix[3 * temprod.endpoint2][varnum] = joints[temprod.endpoint2].x - joints[temprod.endpoint1].x;
                tempmatrix[3 * temprod.endpoint2 + 1][varnum] = joints[temprod.endpoint2].y - joints[temprod.endpoint1].y;
                tempmatrix[3 * temprod.endpoint2 + 2][varnum] = joints[temprod.endpoint2].z - joints[temprod.endpoint1].z;
                newflag = true;
            }
            if (newflag)
            {
                varnum++;
            }
        }
        for (i = 1; i <=jnum; i++)
        {
            if (joints[i].z > 0)
            {
                memcpy(coefficient[equationnum++], tempmatrix[3 * i], (varnum+1)*sizeof(double));
                memcpy(coefficient[equationnum++], tempmatrix[3 * i+1], (varnum+1)*sizeof(double));
                memcpy(coefficient[equationnum++], tempmatrix[3 * i+2], (varnum+1)*sizeof(double));
                coefficient[equationnum - 1][0] = 1;
            }
        }
        if (fIsStatic(&stableflag))
        {
            if (stableflag)
                printf("Sculpture %d: STABLE\n", casenum);
            else
                printf("Sculpture %d: UNSTABLE\n", casenum);
        }
        else
            printf("Sculpture %d: NON-STATIC\n", casenum);
        casenum++;
    }
    return 0;
}