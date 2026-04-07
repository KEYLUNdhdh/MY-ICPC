#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef vector<int> BigInt;
typedef struct Minister
{
    int a, b;
}Minister;
BigInt multiply(const BigInt& A,int b)
{
    BigInt C;
    int t = 0;
    for (int i = 0; i < A.size() || t;i++)
    {
        if (i < A.size())
            t += A[i] *b;
        C.push_back(t % 10);
        t /= 10;
    }
    while(C.size() > 1 && C.back() == 0)
        C.pop_back();
    return C;
}
BigInt divide(const BigInt& A,int b)
{
    BigInt C;
    int r = 0;
    for (int i = A.size() - 1; i >= 0;i--)
    {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r %= b;
    }
    reverse(C.begin(), C.end());//转回低位在前
    while(C.size() > 1 && C.back() == 0)
        C.pop_back();
    return C;
}
bool IsGreaterBigInt(const BigInt& A,const BigInt & B)//比较BigInt大小
{
    if (A.size() != B.size())
        return A.size() > B.size();
    else
    {
        for (int i = A.size() - 1; i >= 0;i--)
        {
            if (A[i] != B[i])
                return A[i] > B[i];
        }
        return false;
    }
}
bool cmp(Minister m1,Minister m2)
{
    return m1.a * m1.b < m2.a * m2.b;
}
signed main()
{
    ios::sync_with_stdio(0);
    int n;
    cin >> n;
    int ka, kb;
    cin >> ka >> kb;
    vector<Minister> m(n);
    for (int i = 0; i < n;i++)
        cin >> m[i].a >> m[i].b;
    sort(m.begin(),m.end(), cmp);
    BigInt cur;
    while(ka)
    {
        cur.push_back(ka % 10);
        ka /= 10;
    }
    BigInt max = {0};
    for (int i = 0; i < n;i++)
    {
        BigInt now = divide(cur, m[i].b);
        if(IsGreaterBigInt(now,max))
            max = now;
        cur = multiply(cur, m[i].a);
    }
    for (int i = max.size() - 1; i >= 0;i--)
    {
        cout << max[i];
    }
    return 0;
}