#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
int search(int n,int k)
{
    if (n == 0)
        return -1;
    int pos = (int)pow(2, n - 1);
    if (k == pos)
        return n;
    if (k > pos)
        return search(n - 1, k - pos);
    if (k < pos)
        return search(n - 1, k);
}

signed main()
{ 
       cin >> n >> k;
       cout << search(n,k);
}