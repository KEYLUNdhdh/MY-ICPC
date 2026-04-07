#include <bits/stdc++.h>
using namespace std;
using db = double;
struct Gauss
{
    static constexpr db EPS = 1e-8;
    //a n * (n + 1)
    static int solve(vector<vector<db>> &a,vector<db> &res)
    {
        int n = a.size();
        int r = 0;
        for (int i = 0; i < n;i++)
        {
            int maxrow = r;
            for (int j = r + 1; j < n;j++)
            {
                if(abs(a[j][i]) > abs(a[maxrow][i]))
                    maxrow = j;
            }
            if(abs(a[maxrow][i]) < EPS)
                continue;

            swap(a[r], a[maxrow]);
            db pivot = a[r][i];
            for (int j = i; j <= n;j++)
                a[r][j] /= pivot;
            for (int j = 0; j < n;j++)
            {
                if(r != j)
                {
                    db factor = a[j][i];
                    for (int k = i; k <= n;k++)
                        a[j][k] -= factor * a[r][k];
                }
            }
            r++;
        }
        if(r < n)
        {
            for (int i = r; i < n;i++)
            {
                if(abs(a[i][n]) > EPS)
                    return -1;
            }
            return 0;
        }
        res.resize(n);
        for (int i = 0; i < n;i++)
            res[i] = a[i][n];
        return 1;
    }
};
