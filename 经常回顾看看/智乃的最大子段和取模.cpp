//与最大子段和原题相同，都是将其拆分成两个前缀和的差，既找到sum(r)-sum(l-1)的最大值，接下来分两种情况讨论
//sum(r)-sum(l-1) > 0 说明取模不会产生影响，直接当成原题做。
//sum(r)-sum(l-1) < 0 则可能由于取模运算导致它变成一个非常大的数字。
//对于第二种情况，注意到 sum(x)在过程中取余，它的取值范围是[0,mod)，所以做差之后只可能在(-mod,0]这个区间，故对于这种情况，需要且仅需要补充一个mod，在计算max的过程中补上一个+mod即可。
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
//先对每个前缀和取模再去计算
//set维护前面出现的数值
void solve()
{
    int n;
    i64 p;
    cin >> n >> p;
    vector<i64> a(n + 1, 0);
    vector<i64> pre(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        pre[i] = (a[i] + pre[i - 1]) % p;
    }
    set<pll> st;
    st.insert({0,0});
    i64 maxx = -1;
    int l = -1, r = -1;
    //对每个i，记录以i结尾的最大值
    for (i64 i = 1; i <= n;i++)
    {
        i64 prefix = pre[i];
        auto it = st.begin();
        i64 val = (prefix - it->first + p) % p;
        if(val > maxx)
        {
            maxx = val;
            l = it->second;
            r = i - 1;
        }
        it = st.upper_bound({prefix, n + 1});
        if(it != st.end())
        {
            val = (prefix - it->first + p) % p;
            if(val > maxx)
            {
                maxx = val;
                l = it->second;
                r = i - 1;
            }
        }
        st.insert({prefix, i});
    }
    cout << l << " " << r << " " << maxx;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}