#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
int isPrime[MAXN];
int prime[MAXN];
int cnt = 0;
void ola(int n)
{
    memset(isPrime, 1, sizeof isPrime);
    isPrime[1] = 0;
    for (int i = 2; i <= n;i++)
    {
        if(isPrime[i])
            prime[cnt++] = i;
        for (int j = 0; j < cnt && prime[j] * i <= n;j++)
        {
            isPrime[i * prime[j]] = 0;
            if(i % prime[j] == 0)
                break;
        }
    }
}
int fa[MAXN];

inline int Find(int x)
{
    if(fa[x] == x)
        return x;
    else
        return fa[x] = Find(fa[x]);
}

inline void unite(int x,int y)
{
    int fx = Find(x);
    int fy = Find(y);
    if(fx != fy)
    {
        fa[fx] = fy;
    }
}
int main()
{
    int a, b, p;
    cin >> a >> b >> p;
    ola(b);
    int index = 0;
    for (int i = a; i <= b;i++)
        fa[i] = i;
    while (prime[index] < p)
        index++;
    vector<int> vec;
    for (int i = index; i < cnt &&prime[i] <= b;i++)
    {
        vec.push_back(prime[i]);
    }
    for(auto i : vec)
    {
        int ch = a / i;
        while(ch * i < a)
            ch++;
        int pre = ch * i;
        ch++;
        while(ch * i <= b)
        {
            if(Find(pre) != Find(ch * i))
            {
                unite(pre, ch * i);
            }
            ch++;
        }
    }
    set<int> st;
    for (int i = a; i <= b;i++)
    {
        st.insert(Find(i));
    }
    cout << st.size();
}