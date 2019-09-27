#include<cstdio>
using namespace std;
const int MAXN = 64;
int dimension;
double lmatrix[MAXN][MAXN],rmatrix[MAXN][MAXN];
//strassen算法局限性很大，只能适用于阶为2的幂次的矩阵，原因也很显然。分治算法每次递归将矩阵切分为1/2大小的子矩阵，一旦阶出现奇数因子则
int matrixMulti(int dimen,double *lmatrix,double *rmatrix){
    if(dimen<0){
        printf("ERROR:Dimension of Matrix Must be Non-negative");
        return 0;
    }
    int temp_dimen = dimen;
    while(!(temp_dimen&1)){
        temp_dimen >>= 1;
    }
    if(temp_dimen!=1){
        printf("ERROR:Dimension of Matrix Must be a power of 2");
        return 0;
    }
    //construct subMatrix
}
int main(){
    scanf("%d",dimension);
    for (int i = 0; i < dimension;i++){
        for (int j = 0; j < dimension;j++){
            scanf("%lf",lmatrix[i][j]);
        }
    }
    for (int i = 0; i < dimension;i++){
        for (int j = 0; j < dimension;j++){
            scanf("%lf",rmatrix[i][j]);
        }
    }
}