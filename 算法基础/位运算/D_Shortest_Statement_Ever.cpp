// #include <bits/stdc++.h>
// #define int long long
// using namespace std;

// signed main()
// {
//     int t;
//     cin >> t;
//     while(t--)
//     {
//         int x, y;
//         cin >> x >> y;
//         int ox = x, oy = y;
//         int p1 = x;
//         int q1 = y ^ (x & y);
//         int cost1 = (x & y);
//         if((x & y) == 0)
//         {
//             cout << x << " " << y << "\n";
//             continue;
//         }
//         vector<int> a, b;
//         while(x != 0)
//         {
//             if(x & 1)
//             {
//                 a.push_back(1);
//             }
//             else
//                 a.push_back(0);
//             x >>= 1;
//         }
//         while(y != 0)
//         {
//             if(y & 1)
//             {
//                 b.push_back(1);
//             }
//             else
//                 b.push_back(0);
//             y >>= 1;
//         }
//         int gt = max(a.size(), b.size());
//         while(a.size() < gt)
//         {
//             a.push_back(0);
//         }
//         while(b.size() < gt)
//         {
//             b.push_back(0);
//         }
//         int hi = -1;
//         for (int i = 0; i < gt; i++)
//         {
//             if(a[i] == b[i] && a[i] == 1)
//             {
//                 hi = max(hi, i);
//             }
//         }
//         {
//             int p = ox;
//             int q = oy & (~ox);
//             int mask = (1ll << hi) - 1;
//             q |= (mask & (~p));
//             int cost = abs(p - ox) + abs(q - oy);
//             if(cost < cost1)
//             {
//                 cost1 = cost;
//                 p1 = p;
//                 q1 = q;
//             }
//         }
//         {
//             int q = oy;
//             int p = ox & (~oy);
//             int mask = (1ll << hi) - 1;
//             p |= (mask & (~q));
//             int cost = abs(p - ox) + abs(q - oy);
//             if(cost < cost1)
//             {
//                 cost1 = cost;
//                 p1 = p;
//                 q1 = q;
//             }
//         }
//         for (int i = hi + 1; i <= 30;i++)
//         {
//             int mask = ~((1ll << i) - 1);
//             if(!((ox >> i) & 1))
//             {
//                 int cp = (ox & mask) | (1ll << i);
//                 int cq = oy;
//                 if((oy >> i) & 1)
//                     cq = cq ^ (1ll << i);
//                 int cost = (abs(cp - ox) + abs(cq - oy));
//                 if(cost < cost1)
//                 {
//                     cost1 = cost;
//                     p1 = cp;
//                     q1 = cq;
//                 }
//             }

//             if(!((oy >> i) & 1))
//             {
//                 int cq = (oy & mask) | (1ll << i);
//                 int cp = ox;
//                 if((ox >> i) & 1)
//                 {
//                     cp = cp ^ (1ll << i);
//                 }
//                 int cost = abs(cp - ox) + abs(cq - oy);
//                 if(cost < cost1)
//                 {
//                     cost1 = cost;
//                     p1 = cp;
//                     q1 = cq;
//                 }
//             }
//         }
//         cout << p1 << " " << q1 << "\n";
//     }
// }

#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--)
    {
        int x, y;
        cin >> x >> y;

        int intersection = x & y;
        
        // 如果本来就没有冲突，直接输出
        if(intersection == 0)
        {
            cout << x << " " << y << "\n";
            continue;
        }

        int ox = x, oy = y;
        
        // 1. 找到最高冲突位 hi
        int hi = 63 - __builtin_clzll(intersection);

        int best_p = -1, best_q = -1;
        int min_cost = 2e18; // 初始化为无穷大

        // ==========================================
        // 策略 A: 向下取整 + 填充 (Downwards & Fill)
        // 解决最高位的冲突，牺牲其中一个数，但尽量用低位补救
        // ==========================================

        // A1: x 保持不变，y 做出牺牲
        {
            int p = x;
            // 1. y 必须去掉所有和 x 冲突的位 (包括 hi)
            int q = y & (~x); //等价于y ^ (x & y)
            // 2. 贪心填充：因为 y 失去了 hi 位，变小了。
            // 我们在 hi 位以下，把所有 p 没有占用的位，全部赋给 q，让 q 尽量大
            int mask = (1LL << hi) - 1; 
            q |= (mask & (~p));

            int cost = abs(p - ox) + abs(q - oy);
            if(cost < min_cost) {
                min_cost = cost;
                best_p = p;
                best_q = q;
            }
        }

        // A2: y 保持不变，x 做出牺牲 (对称操作)
        {
            int q = y;
            int p = x & (~y);
            int mask = (1LL << hi) - 1;
            p |= (mask & (~q));

            int cost = abs(p - ox) + abs(q - oy);
            if(cost < min_cost) {
                min_cost = cost;
                best_p = p;
                best_q = q;
            }
        }

        // ==========================================
        // 策略 B: 向上进位 (Upwards / Round Up)
        // 尝试把 x 或 y 进位到比 hi 更高的位置
        // ==========================================
        for (int i = hi + 1; i <= 30; i++)
        {
            int mask = ~((1LL << i) - 1); // 高位掩码

            // B1: 尝试让 x 进位
            if(!((ox >> i) & 1)) // 只有原 x 第 i 位是 0 才能进位
            {
                int p = (ox & mask) | (1LL << i); // 进位：高位保留，i变为1，低位清0
                
                // q 必须配合 p：如果 q 在第 i 位是 1，必须去掉
                // p 的低位全是 0，所以 q 的低位可以随便保留，不会冲突
                int q = oy;
                if((q >> i) & 1) q ^= (1LL << i);

                int cost = abs(p - ox) + abs(q - oy);
                if(cost < min_cost) {
                    min_cost = cost;
                    best_p = p;
                    best_q = q;
                }
            }

            // B2: 尝试让 y 进位
            if(!((oy >> i) & 1))
            {
                int q = (oy & mask) | (1LL << i);
                
                int p = ox;
                if((p >> i) & 1) p ^= (1LL << i);

                int cost = abs(p - ox) + abs(q - oy);
                if(cost < min_cost) {
                    min_cost = cost;
                    best_p = p;
                    best_q = q;
                }
            }
        }

        cout << best_p << " " << best_q << "\n";
    }
    return 0;
}