#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, k;
vector<int> a(N);
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n >> k;

        vector<int> first(k + 1, 0x3f3f3f3f);
        vector<int> last(k + 1, -1);
        for (int i = 1; i <= n;i++)
        {
            cin >> a[i];
        }
        for (int i = 1; i <= n;i++)
        {
            if(first[a[i]] == 0x3f3f3f3f)
            {
                first[a[i]] = i;
            }
        }
        for (int i = n; i >= 1;i--)
        {
            if(last[a[i]] == -1)
            {
                last[a[i]] = i;
            }
        }
        vector<int> minn(k + 1);
        vector<int> maxx(k + 1);
        minn[k] = first[k];
        maxx[k] = last[k];
        for (int i = k - 1; i >= 1;i--)
        {
            minn[i] = min(first[i],minn[i + 1]);
            maxx[i] = max(last[i], maxx[i + 1]);
        }
        for (int i = 1; i <= k;i++)
        {
            if(first[i] != 0x3f3f3f3f && last[i] != -1)
                cout << 2 * (maxx[i] - minn[i] + 1) << " ";
            else
                cout << 0 << " ";
        }
        cout << "\n";
    }
}