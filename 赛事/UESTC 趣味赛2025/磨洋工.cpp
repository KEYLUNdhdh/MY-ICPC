#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int a[N] = {0};
signed main()
{
    ios::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    if(a[1] == 1){
        cout << 1;
        return 0;
    }
    int cnt = 0;
    cnt += (a[1] - 2) * n;
    cnt++;
    a[1] = 1;
    int pos = n;
    int lastpos = 1;
    while(1)
    {
        while(a[pos] == 1)
            pos--;
        if(pos <= 0)
        {
            cnt += n;
            break;
        }
        cnt += (pos - lastpos + n) % n;
        cnt += (a[pos] - 2) * n;
        a[pos] = 1;
        lastpos = pos;
    }
    cout << cnt;
}