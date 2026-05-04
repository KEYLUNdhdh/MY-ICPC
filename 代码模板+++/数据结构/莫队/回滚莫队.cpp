#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct RollbackMo
{
    struct Query
    {
        int l, r, id;
    };

    int n, m, blockSize;
    vector<int> a;
    vector<Query> queries;  
    vector<int> ans;

    vector<int> firstpos, lastpos;
    int curans;

    RollbackMo(int n_, int m_, const vector<int> &a_, int maxval)
    {
        n = n_;
        m = m_;
        a = a_;
        blockSize = max(1, (int)(n / sqrt(m)));
        ans.assign(m, 0);

        firstpos.assign(maxval + 1, 0);
        lastpos.assign(maxval + 1, 0);
    }

    void addQuery(int l, int r, int id)
    {
        queries.push_back({l, r, id});
    }

    int bruteForce(int l, int r)
    {
        int res = 0;
        for (int i = l; i <= r;i++)
        {
            if(!firstpos[a[i]])
                firstpos[a[i]] = i;
            res = max(res, i - firstpos[a[i]]);
        }
        for (int i = l; i <= r;i++)
        {
            firstpos[a[i]] = 0;
        }
        return res;
    }

    vector<int> run()
    {
        sort(queries.begin(), queries.end(), [&](const Query &q1, const Query &q2)
        {
            int b1 = q1.l / blockSize;
            int b2 = q2.l / blockSize;
            if(b1 != b2)
                return b1 < b2;
            return q1.r < q2.r;
        });

        int lastblock = -1;
        int L = 1, R = 0;

        for(const auto &q : queries)
        {
            int curblock = q.l / blockSize;
            if(curblock != lastblock)
            {
                for (int i = R; i >= L;i--)
                {
                    firstpos[a[i]] = 0;
                    lastpos[a[i]] = 0;
                }

                L = (curblock + 1) * blockSize;
                R = L - 1;
                curans = 0;
                lastblock = curblock;
            }
            
            if(curblock == q.r / blockSize)
            {
                ans[q.id] = bruteForce(q.l, q.r);
                continue;
            }


            while(R < q.r)
            {
                R++;
                if(!firstpos[a[R]])
                    firstpos[a[R]] = R;
                lastpos[a[R]] = R;
                curans = max(curans, R - firstpos[a[R]]);
            }

            int tmpL = L;
            int tmpans = curans;

            while(tmpL > q.l)
            {
                tmpL--;
                int x = a[tmpL];
                if(!lastpos[x])
                    lastpos[x] = tmpL;
                tmpans = max(tmpans, lastpos[x] - tmpL);
            }

            ans[q.id] = tmpans;

            for (int i = q.l; i < L;i++)
            {
                int x = a[i];
                if(lastpos[x] == i)
                    lastpos[x] = 0;
            }
        }

        return ans;
    }
};