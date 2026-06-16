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
constexpr i64 MOD = 998244353, INF = 1e9;

struct Trie
{
    vector<array<int, 70>> ch;

    Trie()
    {
        newNode();
    }

    int newNode()
    {
        ch.push_back({0});
        return ch.size() - 1;
    }

    int getId(char c) const
    {
        if(c >= 'a' && c <= 'z')
            return c - 'a';
        else if(c >= 'A' && c <= 'Z')
            return c - 'A' + 26;
        else if(c >= '0' && c <= '9')
            return c - '0' + 52;
        return 69;

    }

    int insert(const string& s)
    {
        int p = 0;
        for(char c : s)
        {
            int u = getId(c);
            if(!ch[p][u]) ch[p][u] = newNode();
            p = ch[p][u];
        }
        return p;
    }
};

struct ACAuto : public Trie
{
    vector<int> fail;
    vector<int> cnt;      
    vector<int> bfsOrder; 

    ACAuto() : Trie() {}

    void build()
    {
        int n = ch.size();
        fail.assign(n, 0);
        cnt.assign(n, 0);

        queue<int> q;
        for (int i = 0; i < 70; i++)
        {
            if (ch[0][i])
            {
                q.push(ch[0][i]);
                bfsOrder.push_back(ch[0][i]); 
            }
        }

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int i = 0; i < 70; i++)
            {
                if (ch[u][i])
                {
                    fail[ch[u][i]] = ch[fail[u]][i];
                    q.push(ch[u][i]);
                    bfsOrder.push_back(ch[u][i]); 
                }
                else
                    ch[u][i] = ch[fail[u]][i];
            }
        }
    }

    void query(const string &t)
    {
        int u = 0;
        for (char c : t)
        {
            u = ch[u][getId(c)];
            cnt[u]++;
        }
    }

    void topoCount()
    {
        for (int i = bfsOrder.size() - 1; i >= 0; i--)
        {
            int u = bfsOrder[i];
            cnt[fail[u]] += cnt[u];
        }
    }
    
    int getCnt(int nodeId) const 
    {
        return cnt[nodeId];
    }
};

void solve(int n)
{
    ACAuto ac;
    vector<int> pos(n + 1, 0);
    vector<string> ss(n + 1, "");
    for (int i = 1; i <= n;i++)
    {
        cin >> ss[i];
        pos[i] = ac.insert(ss[i]);
    }

    string t;
    cin >> t;
    ac.build();
    ac.query(t);
    ac.topoCount();

    i64 maxx = 0;
    for (int i = 1; i <= n;i++)
        chmax(maxx, (i64)ac.getCnt(pos[i]));

    cout << maxx << "\n";
    for (int i = 1; i <= n;i++)
    {
        if(ac.getCnt(pos[i]) == maxx)
            cout << ss[i] << "\n";
    }
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T)
    {
        solve(T);
        cin >> T;
    }

    return 0;
}