
// #include <bits/stdc++.h>
// using namespace std;
// int a[1000005] = {0};
// int main()
// {
//     ios::sync_with_stdio(0);
//     int n, k;
//     cin >> n >> k;
//     for (int i = 0; i < n;i++)
//         cin >> a[i];
//     vector<int> max_n;
//     vector<int> min_n;//存储最大最小值
//     deque<int> max_s;
//     deque<int> min_s;//滑动窗口，存储索引
//     for (int i = 0; i < n;i++)
//     {
//         while(!max_s.empty() && a[max_s.back()]  <= a[i])
//         {
//             max_s.pop_back();
//         }
//         max_s.push_back(i);
//         while(!min_s.empty() && a[min_s.back()] >= a[i])
//         {
//             min_s.pop_back();
//         }
//         min_s.push_back(i);
//         if(i >= k && max_s.front() <= i - k)
//         {
//             max_s.pop_front();
//         }
//         if (i >= k && min_s.front() <= i - k)
//         {
//             min_s.pop_front();
//         }
//         if (i >= k - 1)
//         {
//             max_n.push_back(a[max_s.front()]);
//             min_n.push_back(a[min_s.front()]);
//         }
//     }
    // for (const auto &i : min_n)
    // {
    //     cout << i << " ";
    // }
    // cout << "\n";
    // for (const auto& i : max_n)
    // {
    //     cout << i << " ";
    // }
    // return 0;
// }
//滑动窗口//deque先进去的在front 后进去的在back
//AI给的代码
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

/**
 * @brief 使用单调双端队列（Monotonic Deque）在 O(n) 时间内解决滑动窗口问题。
 * * 两个 Deque：
 * 1. max_deque：维护当前窗口内元素的索引，且对应值单调递减（用于求最大值）。
 * 2. min_deque：维护当前窗口内元素的索引，且对应值单调递增（用于求最小值）。
 * * 队列中存储的是数组元素的索引（下标），而不是值本身。
 */
void solve_sliding_window(int n, int k, const vector<int>& a) {
    // 存储结果
    vector<int> min_results;
    vector<int> max_results;

    // 单调双端队列：存储元素的索引
    deque<int> max_deque; // 队头最大，单调递减
    deque<int> min_deque; // 队头最小，单调递增

    // 遍历整个数组
    for (int i = 0; i < n; ++i) {
        // --- 1. 维护最大值单调队列 (Monotonic Decreasing Deque) ---
        // 规则：新元素 a[i] 准备入队，移除队尾所有比 a[i] 小的元素的索引。
        // 因为这些被移除的元素既不如 a[i] 大，又比 a[i] 先离开窗口，所以永远不可能成为最大值。
        //这里如果选择移除队头是错误的，因为此时队头索引指向是整个滑动窗口里最大的数，整个队列索引所指的数呈现降序排序。从back删除才能保证删除所有的数，下面的min处理同理
        while (!max_deque.empty() && a[max_deque.back()] <= a[i]) {
            max_deque.pop_back();
        }
        // 新元素入队
        max_deque.push_back(i);

        // --- 2. 维护最小值单调队列 (Monotonic Increasing Deque) ---
        // 规则：新元素 a[i] 准备入队，移除队尾所有比 a[i] 大的元素的索引。
        // 因为这些被移除的元素既不如 a[i] 小，又比 a[i] 先离开窗口，所以永远不可能成为最小值。
        while (!min_deque.empty() && a[min_deque.back()] >= a[i]) {
            min_deque.pop_back();
        }
        // 新元素入队
        min_deque.push_back(i);

        // --- 3. 检查队头过期（处理窗口滑动） ---
        // 如果队头索引小于等于当前窗口的最左端索引 i - k，说明它已不在当前窗口内，需要移除。
        //在i >= k时此时窗口已经开始移动了，所以需要判断
        if (i >= k && max_deque.front() <= i - k) {
            max_deque.pop_front();
        }
        if (i >= k && min_deque.front() <= i - k) {
            min_deque.pop_front();
        }

        // --- 4. 记录结果 ---
        // 当窗口形成时 (i >= k - 1)，队头即为当前窗口的最大/最小值。
        if (i >= k - 1) {
            min_results.push_back(a[min_deque.front()]);
            max_results.push_back(a[max_deque.front()]);
        }
    }

    // --- 输出结果 ---
    for (const auto &i : min_results)
    {
        cout << i << " ";
    }
    cout << "\n";
    for (const auto& i : max_results)
    {
        cout << i << " ";
    }
}

int main() {
    // 提升 I/O 效率
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    // 读取数组长度 n 和窗口大小 k
    if (!(cin >> n >> k)) return 0;

    vector<int> a(n);
    // 读取数组元素
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // 运行 O(n) 算法
    solve_sliding_window(n, k, a);

    return 0;
}