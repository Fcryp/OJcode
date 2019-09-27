#include <stdio.h>
#include <algorithm> 
using namespace std; 
#define LL long long 
#define mod 1000000007
LL dp[1000009][3];   //G:0 R:1 P:2 
LL N,M,K;
LL fun(LL u,LL v)
{
    int i,j;
    dp[0][1]=dp[0][0]=0;
    dp[0][2]=1;
    for(i=1;i<=N;i++)
    {
        LL sum=(dp[i-1][0]+dp[i-1][1]+dp[i-1][2])%mod;
        dp[i][2]=sum;
        if(i<=u)dp[i][0]=sum;
        else if(i==u+1)dp[i][0]=(sum-1)%mod;
        else dp[i][0]=(sum-dp[i-u-1][1]-dp[i-u-1][2])%mod;
        if(i<=v)dp[i][1]=sum;
        else if(i==v+1)dp[i][1]=(sum-1)%mod;
        else dp[i][1]=(sum-dp[i-v-1][0]-dp[i-v-1][2])%mod;
    }
    return (dp[N][0]+dp[N][1]+dp[N][2])%mod;
}
int main()
{
    while(scanf("%lld%lld%lld",&N,&M,&K)!=EOF)
    {
        LL ans=fun(N,K);
        ans=((ans-fun(M-1,K))%mod+mod)%mod;  //注意减法可能出现负数，这儿坑了好几次，取模的时候要特别处理一下。
        printf("%lld\n",ans);
    }
    return 0;
}