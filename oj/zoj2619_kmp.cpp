#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
int nextpos[25][50];
bool free_var[25][50];
long long ans[25][50];

int fNextConstruct(int casenum,string str){
    int length=str.length(),j,nextj,k;
    nextpos[casenum][0]=-1;
    for(j=0,k=-1;j<length-1;){
        if(k==-1||str.at(j)==str.at(k)){
            nextpos[casenum][++j]=++k;
        }
        else{
            k=nextpos[casenum][k];
        }
    }
    for(j=0;j<length;j++){
        if(nextpos[casenum][j]!=-1&&str.at(nextpos[casenum][j])==str.at(j)){
            nextj=nextpos[casenum][j];
            nextpos[casenum][j]=nextpos[casenum][nextj];
        }
    }
    return 0;
}
int fEquationConstruct(string str,long long vector[][50],int n,int cases){
    int i,j,temp,next;
    int var=str.length();
    for(i=0;i<=var;i++){
        for(j=0;j<=var;j++){
            vector[i][j]=0;
        }
        vector[i][var+1]=n;
    }
    vector[var][var]=1;  //F[N]=1;
    vector[var][var+1]=0;
    for(i=0;i<var;i++){
        temp=0;
        vector[i][i]=n;
        vector[i][i+1]=-1;
        temp++;
        next=nextpos[cases][i];
        while(next!=-1){
            temp++;
            vector[i][next+1]-=1;
            next=nextpos[cases][next];
        }
        if(temp<n)vector[i][0]+=temp-n;
    }
    return 0;
}
long long LCM(long long a,long long b){
   return a/__gcd(a,b)*b;
}
int fGaussElimination(const int cases,long long vector[][50],int equ,int var){
    int i,j,row,col,ta,tb,max_row;
    int freevarnum=0;
    long long lcm,temp;
    for(i=0;i<=var;i++){
        ans[cases][i]=0;
        free_var[cases][i]=true;
    }
    for(row=0,col=0;row < equ && col < var;row++,col++){
        max_row=row;
        for(i=row+1;i<equ;i++){
            if(abs(vector[i][col])>abs(vector[max_row][col]))max_row=i;
        }
        if(max_row!=row){
            for(j=row;j<var+1;j++){
                swap(vector[row][j],vector[max_row][j]);
            }
        }
        if(vector[row][col]==0){
            free_var[cases][freevarnum++]=col;
            row--;
            continue;
        }
        for(i=row+1;i<equ;i++){
            if(vector[i][col]!=0){
                lcm=LCM(abs(vector[i][col]),abs(vector[row][col]));
                ta=lcm/abs(vector[i][col]);
                tb=lcm/abs(vector[row][col]);
                if(vector[i][col]*vector[row][col]<0)tb=-tb;
                for(j=col;j<var+1;j++){
                    vector[i][j]=vector[i][j]*ta-vector[row][j]*tb;
                }
            }
        }
    }
    for(i=row;i<equ;i++){
        if(vector[i][col]!=0) return -1; //无解
    }
    if(row<var) return var-row; //无穷多解，返回自由变量个数
    for(int i=var-1;i>=0;i--){
        temp=vector[i][var];
        for(j=i+1;j<var;j++){
            if(vector[i][j]!=0)temp-=vector[i][j]*ans[cases][j];
        }
        //if(temp%vector[i][i]!=0) return -2;
        ans[cases][i]=temp/vector[i][i];
    }
    return 0;
}
int main(int argc, char const *argv[])
{
    string pattern[25];
    int num[25],casenum,i,length;
    long long vector[50][50];
    cin>>casenum;
    for(i=0;i<casenum;i++){
        cin>>num[i];
        cin>>pattern[i];
    }
    for(i=0;i<casenum;i++){
        length=pattern[i].length();
        fNextConstruct(i,pattern[i]);
        fEquationConstruct(pattern[i],vector,num[i],i);
        fGaussElimination(i,vector,length+1,length+1);
        printf("Case %d:\n%lld",i+1,ans[i][0]);
        if(i!=casenum-1)printf("\n\n");
    }
    return 0;
}
