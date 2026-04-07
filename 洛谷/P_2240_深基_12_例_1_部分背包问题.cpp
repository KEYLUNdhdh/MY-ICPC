#include <bits/stdc++.h>
#define ld long double
using namespace std;

typedef struct jin{
    ld m, v;
    ld xing;
} jin;

bool comp(jin j1,jin j2)
{
    return j1.xing > j2.xing;
}
int main()
{
    int n;
    ld t;
    cin >> n >> t;
    vector<jin> coin;
    jin temp;
    for (int i = 0; i < n;i++)
    {
        cin >> temp.m >> temp.v;
        coin.push_back(temp);
    }
    for (auto& it : coin)
    {
        it.xing = it.v / it.m;
    }
    sort(coin.begin(), coin.end(), comp);
    ld ans = 0;
    for (auto it : coin)
    {
        if (it.m <= t)
        {
            t -= it.m;
            ans += it.v;
        }
        else
        {
            ans += it.xing * t;
            break;
        }
    }
    cout << fixed << setprecision(2) << ans;
    return 0;
}