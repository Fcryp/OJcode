#include <algorithm>
#include <cstdio>
using namespace std;
int seq[100005];
int mergetree[18][100005];
void build(int deep, int lft, int rht)
{
    if (lft >= rht)
    {
        mergetree[deep][lft] = seq[lft];
        return;
    }
    int mid = (lft + rht) >> 1;
    build(deep + 1, lft, mid);
    build(deep + 1, mid + 1, rht);
    int i = lft, j = mid + 1, k = lft;
    while (i <= mid && j <= rht)
    {
        if (mergetree[deep + 1][i] < mergetree[deep + 1][j])
            mergetree[deep][k++] = mergetree[deep + 1][i++];
        else
            mergetree[deep][k++] = mergetree[deep + 1][j++];
    }
    while (i <= mid)
        mergetree[deep][k++] = mergetree[deep + 1][i++];
    while (j <= rht)
        mergetree[deep][k++] = mergetree[deep + 1][j++];
}
int query(int deep, int lft, int rht, int qlft, int qrht, int key)
{
    if (lft > qrht || qlft > rht)
    {
        return 0;
    }
    if (qlft <= lft && qrht >= rht)
    {
        return lower_bound(&mergetree[deep][lft], &mergetree[deep][rht] + 1, key) - &mergetree[deep][lft];
    }
    int mid = (lft + rht) >> 1;
    return query(deep + 1, lft, mid, qlft, qrht, key) + query(deep + 1, mid + 1, rht, qlft, qrht, key);
}
int solve(int n, int qlft, int qrht, int k)
{
    int low = 1, high = n, mid;
    while (low < high)
    {
        mid = (low + high + 1) >> 1;
        int cnt = query(0, 1, n, qlft, qrht, mergetree[0][mid]);
        if (cnt <= k)
            low = mid;
        else
            high = mid - 1;
    }
    return mergetree[0][low];
}
int main()
{
    int n, m;
    int l, r, k;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &seq[i]);
    }
    build(0, 1, n);
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", solve(n, l, r, k - 1));
    }
    return 0;
}