#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
const int MAXA = 1e6 + 5;
int cnt[MAXA];
int maxx;
// vector<int> gr;
map<int, int> mp;
void ela()
{
    for(auto i : mp)
    {
        int it = i.first;
        int ct = i.second;
        for (int j = 1;it * j <= maxx;j++)
        {
            cnt[it * j] += ct;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n;i++)
    {
        cin >> vec[i];
        mp[vec[i]]++;
        maxx = max(maxx, vec[i]);
    }
    // gr = vec;
    // sort(gr.begin(), gr.end());
    // gr.erase(unique(gr.begin(), gr.end()), gr.end());
    ela();
    for(auto i : vec)
    {
        cout << cnt[i] - 1<< "\n";
    }
    return 0;
}