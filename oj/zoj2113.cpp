#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MODULE = 32768;
char cSentence[300];
char cVars[25][25];
long long matrix[25][25];
long long vector[25];
int iCountOfVars;
int fInitPartialMatrix(){
    for (int i = 0; i <= iCountOfVars;i++){
        if(!matrix[i][i])
            matrix[i][i] = 1;
    }
    return 0;
}
int fMatrixMulti(long long a[][25],long long b[][25]){
    int i, j, k;
    long long res[25][25];
    for (i = 0; i <= iCountOfVars;i++){
        for (j = 0; j <= iCountOfVars;j++){
            res[i][j] = 0;
        }
    }
    for (i = 0; i <= iCountOfVars; i++)
    {
        for (j = 0; j <= iCountOfVars; j++)
        {
            for (k = 0; k <= iCountOfVars; k++)
            {
                res[i][j] = (res[i][j]+a[i][k] * b[k][j]%MODULE) % MODULE;
            }
        }
    }
    for (i = 0; i <= iCountOfVars;i++){
        for (j = 0; j <= iCountOfVars;j++){
            a[i][j] = res[i][j];
        }
    }
    return 0;
}
int fMatrixPower(int n){
    int i, j;
    long long ans[25][25];
    for (i = 0; i <= iCountOfVars; i++)
    {
        for (j = 0; j <= iCountOfVars; j++)
        {
            ans[i][j] = (i == j);
        }
    }
    while (n){
        if(n&1){
            fMatrixMulti(ans, matrix);
        }
            fMatrixMulti(matrix, matrix); 
            n >>= 1; 
        }
    for (i = 0; i <= iCountOfVars; i++)
    {
        for (j = 0; j <= iCountOfVars; j++)
        {
            matrix[i][j] = ans[i][j];
        }
    }
    return 0;
}
int fCtoi(char *num)
{
    int base = 1, res = 0, i;
    for (i = (strlen(num) - 1); i >= 0; i--, base *= 10)
    {
        res +=( num[i]-'0') * base;
    }
    return res;
}
int fAddVarToSet(char *var,bool *bIsAdd)
{
    int i;
    for (i = 1; i <= iCountOfVars; i++)
    {
        if (strcmp(var, cVars[i]) == 0)
            break;
    }
    if (i > iCountOfVars)
    {
        strcpy(cVars[i], var);
        iCountOfVars++;
        *bIsAdd = true;
    }
    else
        *bIsAdd = false;
    return i;
}
int fInitToE()
{
    int i, j;
    for (i = 0; i <= iCountOfVars; i++)
    {
        for (j = 0; j <= iCountOfVars; j++)
        {
            matrix[i][j] = (i==j);
        }
    }
    return 0;
}
int fExpandMatrix(){
    for (int i = 0; i < iCountOfVars;i++){
        matrix[iCountOfVars][i] = 0;
        matrix[i][iCountOfVars] = 0;
    }
    matrix[iCountOfVars][iCountOfVars] = 1;
    return 0;
}
int fAnalysisSentence(int *status,int *looptimes)
{
    int l, r, i = 0,j,k;
    int length, lindex;
    volatile long long ans = 0;
    bool strflag = false, lflag = true, numflag = false, plusflag = true, loopflag = false,newflag=false,bracketflag=false;
    char tempstr[30];
    while (cSentence[i]!='\0')
    {
        if (cSentence[i] <= 'Z' && cSentence[i] >= 'A')
        {
            if (strflag == false)
            {
                strflag = true;
                l = i;
            }
            
        }
        else if (cSentence[i] <= '9' && cSentence[i] >= '0')
        {
            if (strflag == true)
            {
                fInitToE();
                strflag = false;
                numflag = true;
                l = i;
                *status = 1;
                loopflag = true;
            }
            else if (numflag == false)
            {
                l = i;
                numflag = true;
            }
        }
        else
        {
            switch (cSentence[i])
            {
            case '=':
                lflag = false;
                if (strflag)
                {
                    strflag = false;
                    r = i - 1;
                    length = r - l + 1;
                    memcpy(tempstr, &cSentence[l], length);
                    tempstr[length] = '\0';
                    lindex = fAddVarToSet(tempstr,&newflag);
                    if(*status&&newflag)
                        fExpandMatrix();
                   
                }
                if(*status)
                    matrix[lindex][lindex] = 0;
                break;
            case '+':
                if(strflag){
                    strflag = false;
                    r = i - 1;
                    length = r - l + 1;
                    memcpy(tempstr, &cSentence[l], length);
                    tempstr[length] = '\0';
                    if(*status){
                        if(plusflag){
                            matrix[fAddVarToSet(tempstr, &newflag)][lindex] = (matrix[fAddVarToSet(tempstr, &newflag)][lindex] +1)%MODULE;
                        }
                        else{
                            matrix[fAddVarToSet(tempstr, &newflag)][lindex] =(matrix[fAddVarToSet(tempstr, &newflag)][lindex] -1 + MODULE)%MODULE;
                        }
                    }
                    else{ 
                        if(plusflag)
                            ans=(ans+vector[fAddVarToSet(tempstr, &newflag)])%MODULE;
                        else
                            ans = (ans - vector[fAddVarToSet(tempstr, &newflag)] + MODULE) % MODULE; 
                    }
                }
                else if(numflag){
                    numflag = false;
                    r = i - 1;
                    length = r - l + 1;
                    memcpy(tempstr, &cSentence[l], length);
                    if(*status){
                        if(plusflag){
                            matrix[0][lindex] = (matrix[0][lindex] + fCtoi(tempstr)) % MODULE;
                        }
                        else{
                            matrix[0][lindex] = (matrix[0][lindex] - fCtoi(tempstr) + MODULE) % MODULE;
                        }
                    }
                    else{
                        if(plusflag)
                            ans = (ans + fCtoi(tempstr)) % MODULE;
                        else
                            ans = (ans - fCtoi(tempstr) + MODULE) % MODULE;
                    }               
                }
                plusflag = true;
                break;
            case '-':
                if(strflag){
                    strflag = false;
                    r = i - 1;
                    length = r - l + 1;
                    memcpy(tempstr, &cSentence[l], length);
                    tempstr[length] = '\0';
                    if(*status){
                        if(plusflag){
                            matrix[fAddVarToSet(tempstr, &newflag)][lindex] = (matrix[fAddVarToSet(tempstr, &newflag)][lindex] +1)%MODULE;
                        }
                        else{
                            matrix[fAddVarToSet(tempstr, &newflag)][lindex] =(matrix[fAddVarToSet(tempstr, &newflag)][lindex] -1 + MODULE)%MODULE;
                        }
                    }
                    else{ 
                        if(plusflag)
                            ans=(ans+vector[fAddVarToSet(tempstr, &newflag)])%MODULE;
                        else
                            ans = (ans - vector[fAddVarToSet(tempstr, &newflag)] + MODULE) % MODULE; 
                    }
                }
                else if(numflag){
                    numflag = false;
                    r = i - 1;
                    length = r - l + 1;
                    memcpy(tempstr, &cSentence[l], length);
                    tempstr[length] = '\0';
                    if(*status){
                        if(plusflag){
                            matrix[0][lindex] = (matrix[0][lindex] + fCtoi(tempstr)) % MODULE;
                        }
                        else{
                            matrix[0][lindex] = (matrix[0][lindex] - fCtoi(tempstr) + MODULE) % MODULE;
                        }
                    }
                    else{
                        if(plusflag)
                            ans = (ans + fCtoi(tempstr)) % MODULE;
                        else
                            ans = (ans - fCtoi(tempstr) + MODULE) % MODULE;
                    }               
                }
                plusflag = false;
                break;
            case '{':
                *status = 2;
                bracketflag = true;
                break;
            case '}':
                fMatrixPower(*looptimes);
                for (j = 0; j <= iCountOfVars;j++)
                {
                    ans = 0;
                    for (k = 0; k <= iCountOfVars; k++)
                    {
                        ans=(ans+vector[k] * matrix[k][j]%MODULE)%MODULE;
                    }
                    vector[j] = ans;
                }
                *looptimes = 0;
                *status = 0;
                break;
            case ' ':
            case '\n':
                if (strflag)
                {
                    strflag = false;
                    r = i - 1;
                    length = r - l + 1;
                    memcpy(tempstr, &cSentence[l], length);
                    tempstr[length] = '\0';
                    if (!strcmp(tempstr, "LOOP"))
                    {
                        fInitToE();
                        loopflag = true;
                        *status = 1;
                    }
                    else if(lflag)
                        lindex = fAddVarToSet(tempstr,&newflag);
                    else if(*status){
                        if(plusflag){
                            matrix[fAddVarToSet(tempstr, &newflag)][lindex] = (matrix[fAddVarToSet(tempstr, &newflag)][lindex] +1)%MODULE;
                        }
                        else{
                            matrix[fAddVarToSet(tempstr, &newflag)][lindex] =(matrix[fAddVarToSet(tempstr, &newflag)][lindex] -1 + MODULE)%MODULE;
                        }
                    }
                    else{ 
                        if(plusflag)
                            ans=(ans+vector[fAddVarToSet(tempstr, &newflag)])%MODULE;
                        else
                            ans = (ans - vector[fAddVarToSet(tempstr, &newflag)] + MODULE) % MODULE; 
                    }
                    if(*status&&newflag)
                        fExpandMatrix();
                    
                }
                else if (numflag)
                {
                    numflag = false;
                    r = i - 1;
                    length = r - l + 1;
                    memcpy(tempstr, &cSentence[l], length);
                    tempstr[length] = '\0';
                    if (loopflag)
                        *looptimes = fCtoi(tempstr);
                    else if (*status)
                    {
                        if(plusflag)
                            matrix[0][lindex] =(matrix[0][lindex]+fCtoi(tempstr))%MODULE;
                        else
                            matrix[0][lindex] = (matrix[0][lindex] + fCtoi(tempstr) + MODULE) % MODULE;
                    }
                    else
                    {
                        if (plusflag)
                            ans = (ans + fCtoi(tempstr)) % MODULE;
                        else
                            ans = (ans - fCtoi(tempstr) + MODULE) % MODULE;
                    }
                }
                break;
            }
        }
        i++;
    }
    if(!loopflag&&!*status&&!bracketflag)
        vector[lindex] = ans;
    if (!loopflag && *status == 1)
    {
        fMatrixPower(*looptimes);
            for (j = 0; j <= iCountOfVars;j++)
            {
                ans = 0;
                for (k = 0; k <= iCountOfVars; k++)
                {
                    ans=(ans+vector[k] * matrix[k][j]%MODULE)%MODULE;
                }
                vector[j] = ans;
            }
        *looptimes = 0;
        *status = 0;
    }
    return 0;
}
int fCompile(int length)
{
    int i,flag = 0,looptimes=0;
    while (length--)
    {
        fgets(cSentence, 255,stdin);
        fAnalysisSentence(&flag,&looptimes);
    }
    for (i = 1; i <= iCountOfVars;i++){
        printf("%s:%lld\n", cVars[i], vector[i]);
    }
    return 0;
}
int main()
{
    int iNumOfProgram, iLenthOfProgram;
    scanf("%d", &iNumOfProgram);
    while (iNumOfProgram--)
    {
        iCountOfVars = 0;
        scanf("%d", &iLenthOfProgram);
        fflush(stdin);
        vector[0] = 1;
        fCompile(iLenthOfProgram);
    }
    return 0;
}