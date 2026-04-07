#include <bits/stdc++.h>
using namespace std;
#define int long long
//n stand for num.k is used to calculate len
map<int, int> length;
int getlen(int n)
{
    if (n <= 1)
        return 1;
    if (length.count(n))
        return length[n];
    length[n] = 2 * getlen(n / 2) + 1;
    return length[n];
}

int count(int n,int l,int r)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    int lenhalf = getlen(n / 2);
    int mid = getlen(n / 2) + 1;
    if (l > r)
        return 0;
    if (r  < mid)
    {
        return count(n / 2, l,r);
    }
    else if (r == mid)
    {
        return count(n / 2, l, r - 1) + n % 2;
    }
    else if (r > mid && l < mid)
    {
        int right =  count(n / 2, 1, min(lenhalf,r - mid));
        int left = count(n / 2, l, mid - 1);
        return left + right + n % 2;
    }
    else if (r > mid && l == mid)
    {
        return count(n / 2,1, min(lenhalf,r - mid)) + n % 2;
    }
    else
    {
        return count(n / 2, max(1ll,l - mid), min(lenhalf,r - mid));
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    int n, l, r;
    cin >> n >> l >> r;
    cout << count(n, l, r);
}

