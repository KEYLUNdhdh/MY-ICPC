#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
/* ================== 斜率优化 / 凸包优化 (CHT) 模板 ================== */
template <typename F1, typename F2>
struct SlopeOpt {
    int head = 0, tail = -1;
    vector<int> q; // 单调队列存储候选决策点 j
    F1 X; // 外部传入的求 X 坐标的 lambda
    F2 Y; // 外部传入的求 Y 坐标的 lambda

    SlopeOpt(int max_nodes, F1 xFn, F2 yFn) : X(xFn), Y(yFn) {
        q.resize(max_nodes + 1);
    }

    // 核心函数 1：判断队尾三个点是否破坏了下凸包（叉乘判断）
    bool bad(int j1, int j2, int j3) {
        i128 y1 = Y(j1), y2 = Y(j2), y3 = Y(j3);
        i128 x1 = X(j1), x2 = X(j2), x3 = X(j3);
        // (y2 - y1) / (x2 - x1) >= (y3 - y2) / (x3 - x2) 
        // 转化为乘法，防止精度问题。注意 X(j) 必须是递增的
        return (y2 - y1) * (x3 - x2) >= (y3 - y2) * (x2 - x1);
    }

    // 核心函数 2：查询最优决策点
    int query(i128 k) {
        // 如果队头两个点的斜率 <= 当前需要的斜率 k，说明队头对当前及未来都不是最优，弹掉
        while (head < tail) {
            i128 y0 = Y(q[head]), y1 = Y(q[head + 1]);
            i128 x0 = X(q[head]), x1 = X(q[head + 1]);
            if (y1 - y0 <= k * (x1 - x0)) {
                head++;
            } else {
                break;
            }
        }
        return q[head];
    }

    // 核心函数 3：将新计算出的状态加入凸包
    void add(int i) {
        // 维护下凸壳：加入前，如果它跟队尾的元素构成的上凸，就一直弹掉队尾
        while (head < tail && bad(q[tail - 1], q[tail], i)) {
            tail--;
        }
        q[++tail] = i;
    }
};
/* =================================================================== */


void solve() {
    int n;
    i64 L;
    cin >> n >> L;
    
    vector<i64> c(n + 1), s(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        s[i] = s[i - 1] + c[i];
    }

    // A(i) 和 B(j) 宏定义化（或 Lambda），这里转成 i128 防止计算溢出
    auto A = [&](int i) -> i128 { return (i128)s[i] + i; };
    auto B = [&](int j) -> i128 { return (i128)s[j] + j + L + 1; };

    vector<i64> dp(n + 1, 0);

    // 1. 定义横坐标 X 和纵坐标 Y 的计算方式
    auto getX = [&](int j) -> i128 { 
        return B(j); 
    };
    auto getY = [&](int j) -> i128 { 
        return (i128)dp[j] + B(j) * B(j); 
    };

    // 2. 初始化封装好的斜率优化器
    SlopeOpt opt(n, getX, getY);
    
    // DP 初始化，先把状态 0 加进下凸壳
    opt.add(0);

    for (int i = 1; i <= n; i++) {
        // 3. O(1) 查询截距最小的最优决策点 j
        int j = opt.query(2 * A(i)); 
        
        // 4. 根据最优决策点 j 算出当前的 dp[i]
        i128 val = A(i) - B(j);
        dp[i] = dp[j] + (i64)(val * val); 

        // 5. 将当前点加入下凸壳供之后的 i 使用
        opt.add(i);
    }

    cout << dp[n] << "\n";
}

signed lyc_fan_club() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}