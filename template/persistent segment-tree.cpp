/*
 * @Author: n0bdy
 * @Date: 2019-10-29 10:24:11
 * @LastEditTime: 2019-11-03 18:58:19
 * @FilePath: \OJcode\template\persistent segment-tree.cpp
 * @Discription: Persistent segment-tree
 */
#include <algorithm>
#include <cstdio>
using namespace std;
const int MAXN = 200005;
int n, sz;
int a[MAXN], b[MAXN], rt[MAXN << 5], rc[MAXN << 5], lc[MAXN << 5], sum[MAXN << 5];
/**
 * @description:init a null segment-tree
 * @param {int &,int,int}
 * @return:void
 */
void build(int &rt, int l, int r)
{
    rt = ++sz; //start with 1
    sum[rt] = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc[rt], l, mid);
    build(rc[rt], mid + 1, r);
}
/**
 * @description:add an element to the segment-tree to form a new segment-tree
 * @param {int,int,int,int} 
 * @return:{int} return the index of added segment-tree
 */
int update(int prert, int l, int r, int p)
{
    int rt = ++sz;
    sum[rt] = sum[prert] + 1;
    rc[rt] = rc[prert];
    lc[rt] = lc[prert];
    if (l == r)
        return rt;
    int mid = (l + r) >> 1;
    if (mid >= p)
        lc[rt] = update(lc[rt], l, mid, p);
    else
        rc[rt] = update(rc[rt], mid + 1, r, p);
    return rt;
}
/**
 * @description: customized function
 * @param {type} 
 * @return: 
 */
void query(int q, int l, int r)
{
}
int main()
{
    int rlimit, pos;
    while (scanf("%d", &n) && n != 0)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d", a + i);
            b[i] = a[i];
        }
        sort(b, b + n - 1);
        rlimit = unique(b, b + n - 1) - b;
        build(rt[0], 0, rlimit);
        for (int i = 0; i < n; i++)
        {
            pos = lower_bound(b, b + n - 1, a[i]) - b;
            rt[i] = update(rt[i - 1], 1, rlimit, pos);
        }
    }
}