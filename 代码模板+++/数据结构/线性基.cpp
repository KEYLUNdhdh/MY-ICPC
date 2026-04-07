#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}

//i64
struct Basis
{
    vector<i64> a;
    vector<i64> t;
    bool zero = false;
    Basis()
    {
        a.resize(64, 0);
        t.resize(64, -1);
    }

    void add(i64 x, i64 y = 2e18)
    {
        for (int i = 63; i >= 0;i--)
        {
            if((x >> i) & 1)
            {
                if (y > t[i])
                {
                    swap(a[i], x);
                    swap(t[i], y);
                }
                x ^= a[i];
            }
        }
        if(x == 0)
            zero = true;
    }

    bool query(i64 x, i64 y = 0)
    {
        for (int i = 63; i >= 0;i--)
        {
            if(((x >> i) & 1) && t[i] >= y)
                x ^= a[i];
        }
        return x == 0;
    }
    //从高到低贪心尝试
    i64 getMax() 
    {
        i64 res = 0;
        for (int i = 63; i >= 0; i--) 
        {
            chmax(res, res ^ a[i]);
        }
        return res;
    }
    
    i64 getMin()
    {
        if(zero)
            return 0;
        for (int i = 0; i <= 63;i++)
        {
            if(a[i])
                return a[i];
        }
        return 0;
    }

    i64 getkth(i64 k)
    {
        if(zero)
        {
            if(k == 1)
                return 0;
            k--;
        }
        vector<i64> b = a;
        vector<i64> tmp;
        for (int i = 0; i <= 63;i++)
        {
            for (int j = i - 1; j >= 0;j--)
            {
                if((b[i] >> j) & 1)
                    b[i] ^= b[j];
                
            }
            if(b[i])
                tmp.push_back(b[i]);
        }
        i64 cnt = tmp.size();
        if(k >= (1ll << cnt))
            return -1;
        i64 res = 0;
        for (int i = 0; i < cnt;i++)
        {
            if((k >> i) & 1)
                res ^= tmp[i];
        }
        return res;
    }
};

//int 
struct Basis
{
    vector<int> a;
    vector<int> t;
    bool zero = false;
    Basis()
    {
        a.resize(32, 0);
        t.resize(32, -1);
    }

    void add(int x, int y = 1e9)
    {
        for (int i = 31; i >= 0;i--)
        {
            if((x >> i) & 1)
            {
                if (y > t[i])
                {
                    swap(a[i], x);
                    swap(t[i], y);
                }
                x ^= a[i];
            }
        }
        if(x == 0)
            zero = true;
    }

    bool query(int x, int y = 0)
    {
        for (int i = 31; i >= 0;i--)
        {
            if(((x >> i) & 1) && t[i] >= y)
                x ^= a[i];
        }
        return x == 0;
    }
    //从高到低贪心尝试
    int getMax() 
    {
        int res = 0;
        for (int i = 31; i >= 0; i--) 
        {
            chmax(res, res ^ a[i]);
        }
        return res;
    }
    int getMin()
    {
        if(zero)
            return 0;
        for (int i = 0; i <= 31;i++)
        {
            if(a[i])
                return a[i];
        }
        return 0;
    }

    int getkth(int k)
    {
        if(zero)
        {
            if(k == 1)
                return 0;
            k--;
        }
        vector<int> b = a;
        vector<int> tmp;
        for (int i = 0; i <= 31;i++)
        {
            for (int j = i - 1; j >= 0;j--)
            {
                if((b[i] >> j) & 1)
                    b[i] ^= b[j];
                
            }
            if(b[i])
                tmp.push_back(b[i]);
        }
        int cnt = tmp.size();
        if(k >= (1 << cnt))
            return -1;
        int res = 0;
        for (int i = 0; i < cnt;i++)
        {
            if((k >> i) & 1)
                res ^= tmp[i];
        }
        return res;
    }
};