#include <cstdio>
#define EPS 1e-8
double x1, y1, x2, y2, x3, y3, x4, y4;
int main()
{
    int r = 0;
    double a[2][3];
    printf("line1:");
    scanf("(%lf,%lf)-(%lf,%lf)", &x1, &y1, &x2, &y2);
    fflush(stdin);
    printf("line2:");
    scanf("(%lf,%lf)-(%lf,%lf)", &x3, &y3, &x4, &y4);
    if (y1 != y2 && x1 != x2)
    {
        a[0][2] = y1 / (y1 - y2) + x1 / (x2 - x1);
        a[0][0] = 1 / (x1 - x2);
        a[0][1] = 1 / (y2 - y1);
    }
    else if (y1 == y2 && x1 != x2)
    {
        a[0][2] = y1;
        a[0][0] = 0;
        a[0][1] = 1;
    }
    else if (y1 != y2 && x1 == x2)
    {
        a[0][2] = x1;
        a[0][0] = 1;
        a[0][1] = 0;
    }
    else
    {
        printf("Error:line1 is not a line;");
        return -1;
    }
    if (y3 != y4 && x3 != x4)
    {
        a[1][2] = y3 / (y3 - y4) + x3 / (x4 - x3);
        a[1][0] = 1 / (x3 - x4);
        a[1][1] = 1 / (y4 - y3);
    }
    else if (y3 == y4 && x3 != x4)
    {
        a[1][2] = -y3;
        a[1][0] = 0;
        a[1][1] = 1;
    }
    else if (y3 != y4 && x3 == x4)
    {
        a[1][2] = -x3;
        a[1][0] = 1;
        a[1][1] = 0;
    }
    else
    {
        printf("Error:line2 is not a line;");
        return -1;
    }
    double temp;
    for (int j = 0; j < 2; j++)
    {
        for (int i = j; i < 2; i++)
        {
            if (a[i][j] > EPS || a[i][j] < -EPS)
            {
                for (int k = 2; k >= j; k--)
                {
                    a[i][k] /= a[i][j];
                }
                if(r!=i){
                    for (int s = 0; s < 3; s++)
                    {
                        temp = a[r][s];
                        a[r][s] = a[i][s];
                        a[i][s] = temp;
                    }
                }
                for (int t = r + 1; t < 2;t++){
                    if(a[t][j] > EPS || a[t][j] < -EPS)   
                        for (int k = 2; k >= j;k--){
                            a[t][k] -= a[r][k] * a[t][j];
                        }
                }
                r++;
                break;
            }
        }
    }
    if(r<2){
        printf("no point\n");
        return 0;
    }
    double px, py;
    py = -a[1][2];
    px = -a[0][2]-py*a[0][1];
    /*
    for (int i = 0; i < 2;i++){
        for (int j = 0; j < 3;j++)
            printf("%lf ", a[i][j]);
        printf("\n");
    }
    */
    printf("x:%lf\n", px);
    printf("y:%lf", py);
    return 0;
}