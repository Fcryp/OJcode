#include <algorithm>
#include <cstdio>
#include <ctime>
long long n, k;
char reply[10];
int main()
{
    srand(time(0));
    int count = 0;
    long long l, r, mid, rad;
    scanf("%lld %lld", &n, &k);
    l = 1;
    r = n;
    while (true)
    {
        count++;
        mid = (l + r) / 2;
        if (r - l <= 4 * k)
        {
            rad = rand() % (r - l + 1) + l;
            printf("%lld %lld\n", rad, rad);
            fflush(stdout);
            scanf("%s", reply);
            fflush(stdin);
            if (reply[0] == 'Y' || reply[0] == 'B')
                return 0;
            l = std::max((long long)1, l - k);
            r = std::min(n, r + k);
            continue;
        }
        printf("%lld %lld\n", l, mid);
        fflush(stdout);
        scanf("%s", reply);
        fflush(stdin);
        if (reply[0] == 'Y')
        {
            if (l == r)
                return 0;
            l = std::max((long long)1, l - k);
            r = std::min(n, mid + k);
        }
        else if (reply[0] == 'N')
        {
            l = std::max((long long)1, mid + 1 - k);
            r = std::min(n, r + k);
        }
        else
        {
            return 0;
        }
    }
}