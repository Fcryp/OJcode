#include<cstdio>
#include<cstring>
using namespace std;
/*

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long int LL;
LL Map[256];//0~9、a~z与0~35的对应
LL inf = (1LL << 63) - 1;//long long的最大值2^63-1,注意加括号
 
void init()
{
	for (char c = '0'; c <= '9'; c++)
	{
		Map[c] = c - '0';
	}
	for (char c = 'a'; c <= 'z'; c++)
	{
		Map[c] = c - 'a' + 10;//将'a'~'z'映射到10~35
	}
}
LL convertNum10(char a[], LL radix, LL t)//将a转换为十进制，t为上界
{
	LL ans = 0;
	int len = strlen(a);
	for (int i = 0; i < len; i++)
	{
		ans = ans*radix + Map[a[i]];//进制转换
		if (ans<0 || ans>t) return -1;//溢出或超过N1的十进制
	}
	return ans;
}
int cmp(char N2[], LL radix, LL t)//N2的十进制与t进行比较
{
	int len = strlen(N2);
	LL num = convertNum10(N2, radix, t);//将N2转换为十进制
	if (num < 0) return 1;//溢出肯定是N2>t;
	if (t > num)return -1;//t较大，返回-1
	else if (t == num)return 0;//相等，返回0
	else return 1;//num较大，返回1
}
LL binarySearch(char N2[], LL left, LL right, LL t)//二分求解N2的进制
{
	LL mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		int flag = cmp(N2, mid, t);//判断N2转换为十进制后与t比较
		if (flag == 0)return mid;//找到解，返回mid
		else if (flag == -1)left = mid + 1;//往右子区间继续查找
		else right = mid - 1;//往左子区间继续查找
	}
	return -1;
}
int findLargestDigit(char N2[])//求最大的数位
{
	int ans = -1, len = strlen(N2);
	for (int i = 0; i < len; i++)
	{
		if (Map[N2[i]] > ans)
		{
			ans = Map[N2[i]];
		}
	}
	return ans + 1;//最大的数位为ans，说明进制数的底线是ans+1
}
char N1[20], N2[20], temp[20];
int tag, radix;
int main()
{
	init();
	scanf("%s %s %d %d", N1, N2, &tag, &radix);
	if (tag == 2)
	{
		strcpy(temp, N1);
		strcpy(N1, N2);
		strcpy(N2, temp);
	}
	LL t = convertNum10(N1, radix, inf);//将N1从radix进制转换为十进制
	LL low = findLargestDigit(N2);//找到N2中数位最大的位加1，当成二分下界
	LL high = max(low, t) + 1;//上界
	LL ans = binarySearch(N2, low, high, t);//二分
	if (ans == -1)printf("Impossible\n");
	else printf("%lld\n", ans);
	return 0;
}
*/
int main(){
    int i,j;
    int tag;
    long long value=0,tempvalue=0,exponent=1,tempradix=1,left,right,mid,radix;
    char n[2][15]={"",""};
    int len1,len2;
    long long i_n[2][15]={{0},{0}};
    scanf("%s %s %d %lld",&n[0],&n[1],&tag,&radix);
    len1=strlen(n[0]);
    len2=strlen(n[1]);
    for(i=0;i<len1;i++){ 
        if(n[0][i]<='z'&&n[0][i]>='a'){
            i_n[0][i]=n[0][i]-'a'+10;
        }
        else i_n[0][i]=n[0][i]-'0';
        if(tag==2&&i_n[0][i]>left)left=i_n[0][i];
    }
    for(i=0;i<len2;i++){
        if(n[1][i]<='z'&&n[1][i]>='a'){
            i_n[1][i]=n[1][i]-'a'+10;
        }
        else i_n[1][i]=n[1][i]-'0';
        if(tag==1&&i_n[1][i]>left)left=i_n[1][i];
    }
    left++;
    if(tag==1){
        for(i=len1-1;i>=0;i--,exponent*=radix){
            value+=i_n[0][i]*exponent;
        }
        right=value+1;
        while(left<=right){
            tempradix=1;
            tempvalue=0;
            mid=(right-left)/2+left;
            for(i=len2-1;i>=0;i--,tempradix*=mid){
                tempvalue+=i_n[1][i]*tempradix;
            }
            if(tempvalue<value){
                left=mid+1;
            }
            else if(tempvalue==value){
                printf("%lld",mid);
                return 0;
            }
            else{
                right=mid-1;
            }
        }
        printf("Impossible");
        return 0;
    }
    else{
        for(i=len2-1;i>=0;i--,exponent*=radix){
            value+=i_n[1][i]*exponent;
        }
        right=value+1;
        while(left<=right){
            tempradix=1;
            tempvalue=0;
            mid=(right+left)/2;
            for(i=len1-1;i>=0;i--,tempradix*=mid){
                tempvalue+=i_n[0][i]*tempradix;
            }
            if(tempvalue<value){
                left=mid+1;
            }
            else if(tempvalue==value){
                printf("%lld",mid);
                return 0;
            }
            else{
                right=mid-1;
            }
        }
        printf("Impossible");
        return 0;
    }
}