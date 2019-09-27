#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;
const uint64_t UINT32_MAXLIMIT = (uint64_t)1 << 32;
const uint32_t MAX_UINT32 = (uint32_t)(-1);
long long seq[105][2];
class ubigint
{
public:
    ubigint()
    {
        digits.push_back(0);
    }
    ubigint(const uint32_t &uint)
    {
        digits.push_back(uint);
    }
    ubigint(const ubigint &ubint)
    {
        this->digits = ubint.digits;
    }
    ubigint(const vector<uint32_t> &vec)
    {
        digits = vec;
    }
    ubigint operator=(int)
    {
    }
    friend ubigint operator+(const ubigint &l, const ubigint &r)
    {
        int i;
        uint64_t temp = 0;
        uint32_t len = l.digits.size();
        vector<uint32_t> res;
        if (r.digits.size() < len)
            len = r.digits.size();
        for (i = 0; i < len; i++)
        {
            temp += l.digits[i] + r.digits[i];
            res.push_back(temp % UINT32_MAXLIMIT);
            temp >>= 32;
        }
        while (i < l.digits.size())
        {
            i++;
            temp += l.digits[i];
        }
        while (i < r.digits.size())
        {
            i++;
            temp += r.digits[i];
        }
        if (temp != 0)
        {
            res.push_back((uint32_t)temp);
        }
        return res;
    }
    friend ubigint operator-(const ubigint &l, const ubigint &r)
    {
        ubigint res;
        uint64_t borrow = 0;
        uint32_t r_len = r.digits.size();
        uint32_t l_len = l.digits.size();
        if (l_len < r_len)
        {
            printf("Error:left value is less than right value");
            return 0;
        }
        else if (l_len == r_len)
        {
            for (uint32_t i = l.digits.size() - 1; i != MAX_UINT32; i--)
            {
                if (l.digits[i] < r.digits[i])
                {
                    printf("Error:left value is less than right value");
                    return 0;
                }
            }
        }
        int64_t temp = 0;
        for (int i = 0; i < r_len; i++)
        {
            temp = (int64_t)l.digits[i] - (int64_t)r.digits[i] - borrow;
            if (temp < 0)
            {
                temp += UINT32_MAXLIMIT;
                borrow = 1;
            }
            else
                borrow = 0;
            res.digits.push_back((uint32_t)temp);
        }
        for (int i = r_len; i < l_len; i++)
        {
            temp = (int64_t)l.digits[i] - borrow;
            if (temp < 0)
            {
                temp += UINT32_MAXLIMIT;
                borrow = 1;
            }
            else
                borrow = 0;
            res.digits.push_back((uint32_t)temp);
        }
        return res;
    }
    friend ubigint operator-(const ubigint &l, const uint32_t &r)
    {
        ubigint res;
        uint64_t borrow = 0;
        uint32_t len = l.digits.size();
        int64_t temp;
        if (l.digits.size() == 1 && l.digits[0] < 1)
        {
            printf("Error:left value is less than right value");
            return 0;
        }
        temp = l.digits[0] - r - borrow;
        if(temp<0){
            borrow = 1;
            temp += UINT32_MAXLIMIT;
        }
        res.digits.push_back((uint32_t)temp);
        for (uint32_t i = 1; i < len; i++)
        {
            temp=l.digits[i] - borrow;
            if(temp<0){
                borrow = 1;
                temp += UINT32_MAXLIMIT;
            }
            else
                borrow = 0;
            res.digits.push_back((uint32_t)temp);
        }
        return res;
    }
    ubigint operator<<=(uint32_t shift){
        uint32_t len = digits.size();
        uint64_t temp=0;
        for (uint32_t i = len - 1; i != 0;i--){
            digits[i].
        }
    }
    ubigint operator=(const ubigint &ubint){
        digits=ubint.digits;
        return (ubigint)digits;
    }
    string to_string(){
        string str;
        
        return str;
    }
private:
    vector<uint32_t> digits;
};
int main()
{
    int n, k;
    long long sum, ans;
    seq[0][0] = 0; //H
    seq[0][1] = 1; //T
    while (scanf("%d %d", &n, &k) != EOF)
    {
        for (int i = 1; i <= n; i++)
        {
            sum = seq[i - 1][0] + seq[i - 1][1];
            seq[i][1] = sum;
            if (i <= k - 1)
                seq[i][0] = sum;
            else if (i == k)
                seq[i][0] = sum - 1;
            else if (i > k)
                seq[i][0] = sum - seq[i - k][1];
        }
        ans = seq[n][0] + seq[n][1];
        printf("%lld\n", (long long)pow(2, n) - ans);
    }
    return 0;
}