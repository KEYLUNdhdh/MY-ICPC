#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

template <typename F1, typename F2>
struct SlopeOpt
{
    int head = 0, tail = -1;
    vector<int> q; 
    F1 X; 
    F2 Y;

    SlopeOpt(int max_nodes, F1 xFn, F2 yFn) : X(xFn), Y(yFn) 
    {
        q.resize(max_nodes + 1);
    }

    bool bad(int j1, int j2, int j3) 
    {
        i128 y1 = Y(j1), y2 = Y(j2), y3 = Y(j3);
        i128 x1 = X(j1), x2 = X(j2), x3 = X(j3);
        return (y2 - y1) * (x3 - x2) >= (y3 - y2) * (x2 - x1);
    }

    int query(i128 k) 
    {
        while (head < tail) 
        {
            i128 y0 = Y(q[head]), y1 = Y(q[head + 1]);
            i128 x0 = X(q[head]), x1 = X(q[head + 1]);
            if (y1 - y0 <= k * (x1 - x0)) 
                head++;
            else 
                break;
        }
        return q[head];
    }

    void add(int i) 
    {
        while (head < tail && bad(q[tail - 1], q[tail], i))
            tail--;

        q[++tail] = i;
    }
};