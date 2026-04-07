#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    ll res;
    cin >> res;
    ll mask = ~((1 << 16) - 1);
    ll ma = (1 << 16) - 1;
    ll high = mask & res;
    ll low = ma & res;
    ll rlow = high >> 16;
    ll rhigh = low << 16;
    cout << rlow + rhigh;
}