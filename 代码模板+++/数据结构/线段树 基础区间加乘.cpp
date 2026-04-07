#include <bits/stdc++.h>
// #define int long long
using namespace std;
using i64 = long long;
int P = 998244353;
struct SegmentTree
{
    int n;
    vector<int> mulTag, addTag, sum;
    SegmentTree(int n_) : n{n_}, mulTag(4 * n + 1, 1), addTag(4 * n + 1, 0), sum(4 * n + 1) {}
    void pull(int p)
    {
        sum[p] = (sum[2 * p] + sum[2 * p + 1]) % P;
    }
    void mul(int p,int v)
    {
        mulTag[p] = 1ll * mulTag[p] * v % P;
        addTag[p] = 1ll * addTag[p] * v % P;
        sum[p] = 1ll * sum[p] * v % P;
    }
    void push(int p,int l,int r)
    {
        if(mulTag[p] != 1)
        {
            mul(2 * p, mulTag[p]);
            mul(2 * p + 1,mulTag[p]);
            mulTag[p] = 1;
        }
        if(addTag[p] != 0)
        {
            int m = l + (r - l) / 2;
            applyAdd(2 * p, l, m, addTag[p]);
            applyAdd(2 * p + 1, m + 1, r, addTag[p]);
            addTag[p] = 0;
        }
    }
    int rangeQuery(int p,int l,int r,int x,int y)
    {
        if(l > y || r < x)
            return 0;
        if(l >= x && r <= y)
            return sum[p];
        int m = l + (r - l) / 2;
        push(p, l, r);
        return (rangeQuery(2 * p, l, m, x, y) % P + rangeQuery(2 * p + 1, m + 1, r, x, y) % P);
    }
    int rangeQuery(int x,int y)
    {
        return rangeQuery(1, 1, n, x, y) % P;
    }
    void rangeMul(int p,int l,int r,int x,int y,int v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
            return mul(p, v);
        int m = l + (r - l) / 2;
        push(p, l, r);
        rangeMul(2 * p, l, m, x, y, v);
        rangeMul(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    void rangeMul(int x,int y,int v)
    {
        rangeMul(1, 1, n, x, y, v);
    }
    void applyAdd(int p,int l,int r,int v)
    {
        addTag[p] = (1ll * addTag[p] + 1ll * v) % P;
        sum[p] = (1ll * sum[p] + 1ll * (r - l + 1) * v) % P;
    }
    void rangeAdd(int p,int l,int r,int x,int y,int v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            applyAdd(p, l, r, v);
            return;
        }
        int m = l + (r - l) / 2;
        push(p, l, r);
        rangeAdd(2 * p, l, m, x, y, v);
        rangeAdd(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    void rangeAdd(int x,int y,int v)
    {
        rangeAdd(1, 1, n, x, y, v);
    }
};

// signed main()
// {
//     int n, m;
//     cin >> n >> m >> P;
//     SegmentTree sg(n);
//     for (int i = 1; i <= n;i++)
//     {
//         int tp;
//         cin >> tp;
//         sg.add(i, i, tp);
//     }
//     int op, x, y, k;
//     while(m--)
//     {
//         if(op == 1)
//         {
//             cin >> x >> y >> k;
//             sg.rangeMul(x, y, k);
//         }
//         else if(op == 2)
//         {
//             cin >> x >> y >> k;
//             sg.add(x, y, k);
//         } 
//         else
//         {
//             cin >> x >> y;
//             cout << sg.query(x, y) % P << "\n";
//         }
//     }
// }