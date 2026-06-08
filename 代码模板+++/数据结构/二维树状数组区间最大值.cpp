#include <bits/stdc++.h>
using namespace std;

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}

template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}
template<typename T>
struct FenwickMax 
{
    int n, m;
    vector<T> tr;

    FenwickMax(int n_ = 0, int m_ = 0) 
    {
        init(n_, m_);
    }

    void init(int n_ = 0, int m_ = 0) 
    {
        n = n_;
        m = m_;
        tr.assign((n + 1) * (m + 1), 0); 
    }

    inline int id(int x, int y) const 
    {
        return x * (m + 1) + y;
    }

    void update(int x, int y, T v) 
    {
        for (int i = x; i <= n; i += i & (-i)) 
        {
            for (int j = y; j <= m; j += j & (-j)) 
            {
                int pos = id(i, j);
                chmax(tr[pos], v);
            }
        }
    }

    T query(int x, int y) 
    {
        T ans{}; 
        for (int i = x; i > 0; i -= i & (-i)) 
        {
            for (int j = y; j > 0; j -= j & (-j)) 
            {
                int pos = id(i, j);
                chmax(ans, tr[pos]);
            }
        }
        return ans;
    }
};