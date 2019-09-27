#include <cstdio>
using namespace std;
int test_num, tower_height;
int tower[105][105];
int tempmax[105];
/*递归调用版本
int FindMaxPath(const int &height, const int &current_height, int index)
{
    if (height == 1)
        return tower[index];
    int ltemp,lchild,rtemp;
    lchild = index - edge[current_height - 1] + edge[current_height];
    ltemp=FindMaxPath(height - 1, current_height + 1, lchild);
    rtemp=FindMaxPath(height - 1, current_height + 1, lchild+1);
    if(ltemp>rtemp)
        return ltemp+tower[index];
    else
        return rtemp+tower[index];
}
*/
int main()
{
    int count;
    scanf("%d", &test_num);
    for (count = 0; count < test_num; count++)
    {
        scanf("%d", &tower_height);
        for (int i = 1; i <= tower_height; i++)
        {
            for (int j = 0; j < i;j++){
                scanf("%d", &tower[i][j]);
            }
        }
        for (int i = 0; i < tower_height;i++){
            tempmax[i] = tower[tower_height][i];
        }
        for (int i = tower_height-1; i >= 1; i--)
        {
            for (int j = 0; j < i; j++)
            {
                if(tempmax[j]<tempmax[j+1])
                    tempmax[j] = tempmax[j + 1]+tower[i][j];
                else
                    tempmax[j] += tower[i][j];
            }
        }
        printf("%d\n", tempmax[0]);
    }
}