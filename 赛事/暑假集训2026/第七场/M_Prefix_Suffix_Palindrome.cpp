#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";       \
    cerr << "\n";           \
}
#define cutline { cerr << "----------------------\n"; }
using namespace std;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
using db = double;
typedef pair<int, int> pii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;

struct HashVal
{
    u64 h1, h2;
    bool operator<(const HashVal &b) const
    {
        if(h1 != b.h1)
            return h1 < b.h1;
        return h2 < b.h2;
    }

    bool operator==(const HashVal &b) const  
    {
        return h1 == b.h1 && h2 == b.h2;
    }

    bool operator!=(const HashVal &b) const
    {
        return h1 != b.h1 || h2 != b.h2;
    }
};

struct StringHash
{
    static const u64 B1 = 131, M1 = 1e9 + 7;
    static const u64 B2 = 13331, M2 = 1e9 + 9;

    int n;
    vector<u64> h1, h2;
    vector<u64> p1, p2;

    StringHash(const string &s)
    {
        n = s.length();
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        p1.assign(n + 1, 1);
        p2.assign(n + 1, 1);

        for (int i = 0; i < n;i++)
        {
            h1[i + 1] = (h1[i] * B1 + s[i]) % M1;
            h2[i + 1] = (h2[i] * B2 + s[i]) % M2;
            p1[i + 1] = (p1[i] * B1) % M1;
            p2[i + 1] = (p2[i] * B2) % M2;
        }
    }

    //0 - index
    HashVal get(int l, int r)
    {
        l++, r++;// offset
        u64 res1 = (h1[r] + M1 - h1[l - 1] * p1[r - l + 1] % M1) % M1;
        u64 res2 = (h2[r] + M2 - h2[l - 1] * p2[r - l + 1] % M2) % M2;
        return {res1, res2};
    }

    HashVal getAll()
    {
        return get(0, n - 1);
    }
};

void solve()
{
    string a;
    cin >> a;
    string b = a;
    reverse(b.begin(), b.end());

    int pos = -1;
    for (int i = 0; i < a.size();i++)
    {
        if(a[i] != b[i])
        {
            pos = i - 1;
            break;
        }
    }
    
    int nxtlen = a.size() - 2 * (pos + 1);

    string ka = a.substr(pos + 1, nxtlen), kb = b.substr(pos + 1, nxtlen);
    string revka = ka;
    reverse(revka.begin(), revka.end());
    string revkb = kb;
    reverse(revkb.begin(), revkb.end());
    StringHash ha(ka), hb(kb), rha(revka), rhb(revkb);

    int len = ka.size();
    int maxlen = 0;
    int f = 0;
    for (int i = 0; i < len;i++)
    {
        if(ha.get(0, i) == rha.get(len - i - 1, len - 1))
            maxlen = i + 1;
    }

    for (int i = maxlen; i < len;i++)
    {
        if(hb.get(0, i) == rhb.get(len - i - 1, len - 1))
        {
            maxlen = i + 1;
            f = 1;
        }
    }

    string mid;
    if(!f)
        mid = ka.substr(0, maxlen);
    else
        mid = kb.substr(0, maxlen);

    string ans = a.substr(0, pos + 1);
    string revans = ans;
    reverse(revans.begin(), revans.end());
    cout << ans << mid << revans << "\n";
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}