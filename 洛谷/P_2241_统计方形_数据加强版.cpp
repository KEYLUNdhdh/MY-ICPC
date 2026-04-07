#include <iostream>
#include <cmath>
#define int long long
using namespace std;

signed main()
{
    int square = 0;
    int sq = 0;
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n;++i)
        for (int j = 1; j <= m;++j)
        {
            square += min(i, j);
            sq += i * j;
        }
    cout << square << " " << sq - square;
}