#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int main()
{
    int n;
    cin >> n;
    deque<int> a(n);
    for (int i = 0; i < n;i++)
        cin >> a[i];
    // sort(a.begin(), a.end());
    int minn = 0x3f3f3f3f;
    for (int i = 0; i < 83;i++)
    {
        int l = i;
        int tp = 0;
        int r = l + 17;
        for(auto it : a)
        {
            if(it < l)
            {
                tp += (i - it) * (i - it);
            }
            else if(it > r)
            {
                tp += (it - r) * (it - r);
            }
        }
        minn = min(minn, tp);
    }
    cout << minn;
}