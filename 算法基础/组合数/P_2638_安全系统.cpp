#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, a, b;
typedef vector<int> BigInt;
int comb[50][50];
BigInt tobig(int x)
{
    BigInt res;
    while(x)
    {
        res.push_back(x % 10);
        x /= 10;
    }
    return res;
}
BigInt add(const BigInt& A,BigInt B)
{
    BigInt C;
    int t = 0;
    for (int i = 0; i < A.size() || i < B.size();i++)
    {
        if(i < A.size())
        {
            t += A[i];
        }
        if(i < B.size())
        {
            t += B[i];
        }
        C.push_back(t % 10);
        t /= 10;
    }
    while(t)
    {
        C.push_back(t % 10);
        t /= 10;
    }
    return C;
}
void build()
{
    for (int i = 0; i < 50;i++)
    {
        comb[i][0] = 1;
        comb[i][i] = 1;
    }
    for (int i = 1; i < 50;i++)
    {
        for (int j = 1; j <= i; j++)
        {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
        }
    }
}
BigInt mul(const BigInt& A,BigInt B)
{
    if(A.size() == 1 && A[0] == 0 || B.size() == 1 && B[0] == 0)
        return {0};
    BigInt C(A.size() + B.size(), 0);
    for (int i = 0; i < A.size();i++)
    {
        for (int j = 0; j < B.size();j++)
        {
            C[i + j] += A[i] * B[j];
        }
    }
    //处理进位
    for (int i = 0; i < C.size() - 1;i++)
    {
        C[i + 1] += C[i] / 10;
        C[i] %= 10;
    }
    while(C.size() > 1 && C.back() == 0)
        C.pop_back();
    return C;
}
BigInt f(int n,int i, int j)
{
    BigInt g1 = tobig(comb[n + i - 1][n - 1]);
    BigInt g2 = tobig(comb[n + j - 1][n - 1]);
    return mul(g1, g2);
}
signed main()
{
    BigInt ans;
    cin >> n >> a >> b;
    build();
    for (int i = 0; i <= a;i++)
    {
        for (int j = 0; j <= b;j++)
        {
            ans = add(ans, f(n, i, j));
        }
    }
    for (int i = ans.size() - 1; i >= 0;i--)
        cout << ans[i];
}