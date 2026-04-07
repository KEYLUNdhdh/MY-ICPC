#include <bits/stdc++.h>
using namespace std;

#define int long long // 必须用long long，s和y都会爆int

const int MAXN = 200005;
int n, m, s;
int w[MAXN], v[MAXN];
int L[MAXN], R[MAXN];
int pre_cnt[MAXN], pre_sum[MAXN];
//i64 i64 dfkdsf
//i64 i128 i
int check(int W) 
{
    // 每次改变W，都要重新生成前缀和
    memset(pre_cnt, 0, sizeof(pre_cnt));
    memset(pre_sum, 0, sizeof(pre_sum));
    
    for (int i = 1; i <= n; i++) {
        if (w[i] >= W) {
            pre_cnt[i] = pre_cnt[i - 1] + 1;
            pre_sum[i] = pre_sum[i - 1] + v[i];
        } else {
            pre_cnt[i] = pre_cnt[i - 1];
            pre_sum[i] = pre_sum[i - 1];
        }
    }
    
    int Y = 0;
    for (int i = 1; i <= m; i++) {
        Y += (pre_cnt[R[i]] - pre_cnt[L[i] - 1]) * (pre_sum[R[i]] - pre_sum[L[i] - 1]);
    }
    return Y;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> s;
    int max_w = 0, min_w = 2e9;
    for (int i = 1; i <= n; i++) 
    {
        cin >> w[i] >> v[i];
        max_w = max(max_w, w[i]);
        min_w = min(min_w, w[i]);
    }
    for (int i = 1; i <= m; i++) 
    {
        cin >> L[i] >> R[i];
    }

    // 二分W，W范围在最小重量-1 到 最大重量+1 之间
    int l = min_w - 2, r = max_w + 2;
    int ans = 1e18; // 存储最小的 |s - y|

    while (l + 1 != r) 
    {
        int mid = l + (r - l) / 2;
        int Y = check(mid);
        
        ans = min(ans, abs(Y - s));
        
        // Y 随 W 增大而减小 (单调递减)
        if (Y > s) {
            l = mid; // Y太大了，需要增大W来减小Y
        } else {
            r = mid; // Y太小了，需要减小W来增大Y
        }
    }

    cout << ans << endl;

    return 0;
}