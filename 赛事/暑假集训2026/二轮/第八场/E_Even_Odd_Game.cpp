#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

typedef long long ll;
bool ST;
const int N = 100010;
int n;
ll x;
int jadd, oadd, jmul, omul;
set<int> jad, oad, jmu, omu;

int dp[300][300][305][2];
int now;

int dfs(int a, int b, int c,  int now)
{
    if (dp[a][b][c][now] != -1)
        return dp[a][b][c][now];
    int ne;
    if (a)// ji +
    {
        if (now & 1)
            ne = 0;
        else
            ne = 1;
        if (dfs(a - 1, b, c, ne) == 0)
            return dp[a][b][c][now] = 1;
    }
    if (b)// o +
    {
        ne = now;
        if (dfs(a, b - 1, c, ne) == 0)
            return dp[a][b][c][now] = 1;
    }
    if (c)
    {
        ne = 0;
        if (dfs(a, b, c - 1, ne) == 0)
            return dp[a][b][c][now] = 1;
    }
    return dp[a][b][c][now] = 0;
}

struct ty
{
    char op;
    int num;
};

ty find(int a, int b, int c, int now)
{
    int ne;
    if (a)
    {
        if (now & 1)
            ne = 0;
        else
            ne = 1;
        if (dfs(a - 1, b, c, ne) == 0)
            return {'+', *jad.begin()};
    }
    if (b)
    {
        ne = now;
        if (dfs(a, b - 1, c, ne) == 0)
        {
            if(!oad.empty())
                return {'+', *oad.begin()};
            else
                return {'*', *jmu.begin()};
        }
    }
    if (c)
    {
        ne = 0;
        if (dfs(a, b, c - 1, ne) == 0)
            return {'*', *omu.begin()};
    }
    return {'+', -1};
}

void deal(char op, int num)
{
    if (op == '+')
    {
        if (num & 1)
        {
            now ^= 1;
            jadd--;
            jad.erase(num);
        }
        else
        {
            now = now;
            oadd--;
            oad.erase(num);
        }
    }
    else if (op == '*')
    {
        if (num & 1)
        {
            jmul--;
            jmu.erase(num);
            if (now & 1)
                now = 1;
            else
                now = 0;
        }
        else
        {
            now = 0;
            omul--;
            omu.erase(num);
        }
    }
}

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        char op;
        ll x;
        cin >> op >> x;
        if (op == '+' && x % 2 == 0)
        {
            oad.insert(x);
        }
        else if (op == '+' && x % 2 == 1)
        {
            jad.insert(x);
        }
        else if (op == '*' && x % 2 == 0)
        {
            omu.insert(x);
        }
        else
        {
            jmu.insert(x);
        }
    }
    jadd = jad.size();
    oadd = oad.size();
    jmul = jmu.size();
    omul = omu.size();
    memset(dp, -1, sizeof dp);
    cin >> now;
    if (n & 1)
    {
        dp[0][0][0][1] = 0;
        dp[0][0][0][0] = 1;
    }
    else
    {
        dp[0][0][0][1] = 1;
        dp[0][0][0][0] = 0;
    }
    now %= 2;
    if (dfs(jadd, oadd + jmul, omul, now))
    {
        cout << "me" << endl;
    }
    else
    {
        cout << "you" << endl;
        ty tem;
        cin >> tem.op >> tem.num;
        deal(tem.op, tem.num);
    }
    while (jadd || oadd || jmul || omul)
    {
        ty tem = find(jadd, oadd + jmul, omul, now);
        deal(tem.op, tem.num);
        cout << tem.op << " " << tem.num << endl;
        cout.flush();
        if (jadd || oadd || jmul || omul)
        {
            cin >> tem.op >> tem.num;
            deal(tem.op, tem.num);
        }
        else
            break;
    }
    
}
bool ED;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}