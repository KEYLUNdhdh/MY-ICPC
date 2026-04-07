#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e5 + 5;
const int lim = 1e5 + 5;
int n, a, b;
struct cell{
    int s;
    // vector<int> sz;
} c[MAXN];
int cntaz[MAXN];
int cntsz[MAXN];
int isPrime[lim];
vector<int> primes;
vector<int> az;
int f = 0;
int minday = 2e18;
void ola()
{
    fill(isPrime + 1, isPrime + (int)1e5 + 1, 1);
    isPrime[1] = 0;
    for (int i = 2; i <= (int)1e5;i++)
    {
        if(isPrime[i])
            primes.push_back(i);
        for (auto p : primes)
        {
            if(i * p > (int)1e5)
                break;
            isPrime[i * p] = 0;
            if(i % p == 0)
                break;
        }
    }
}

void ela()
{
    //a
    int temp = a;
    for(auto i : primes)
    {
        if(i * i > temp )
            break;
        if(temp % i == 0)
        {
            az.push_back(i);
            while(temp % i == 0)
            {
                temp /= i;
                cntaz[i]++;
            }
            cntaz[i] *= b;
        }
    }
    if(temp != 1)
    {
        az.push_back(temp);
        cntaz[temp] = b;
    }
    // si;
    for (int i = 1; i <= n;i++)
    {
        int ts = c[i].s;
        if(ts == 1) continue;

        bool checkava = 1;
        int maxx = 0;
        for(int p : az)
        {
            int cnt = 0;
            if(ts % p != 0)
            {
                checkava = 0;
                break;
            }
            while(ts % p == 0)
            {
                cnt++;
                ts /= p;
            }
            int up = (cntaz[p] + cnt - 1) / cnt;
            maxx = max(maxx, up);
        }
        if(checkava)
        {
            minday = min(maxx, minday);
        }
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    cin >> a >> b;
    for (int i = 1; i <= n;i++)
    {
        int val;
        cin >> val;
        c[i].s = val;
    }
    ola();
    ela();
    if(minday == 2e18)
        cout << -1;
    else
        cout << minday;
}