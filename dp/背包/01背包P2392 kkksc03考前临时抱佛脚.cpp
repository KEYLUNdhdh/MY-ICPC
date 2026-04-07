// #include <bits/stdc++.h>
// using namespace std;

// int solve(int n)
// {
//     int a[25];
//     int sum = 0;
//     for (int i = 0; i < n;i++)
//     {
//         cin >> a[i];
//         sum += a[i];
//     }
//     int target = sum / 2;
//     vector<int> dp(target + 1, 0);
//     for (int i = 0; i < n;i++)
//     {
//         int t = a[i];
//         for (int j = target; j >= t;j--)
//         {
//             dp[j] = max(dp[j], dp[j - t] + t);
//         }
//     }
//     return sum - dp[target];
// }

// int main()
// {
//     int s[4];
//     for (int i = 0; i < 4;i++)
//         cin >> s[i];
//     int total = 0;
//     for (int i = 0; i < 4;i++)
//         total += solve(s[i]);
//     cout << total;
//     return 0;
// }

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// 处理单科目的最短时间
int solve_subject(int n) {
    vector<int> times(n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> times[i];
        sum += times[i];
    }

    int target = sum / 2;
    // dp[j] 表示在容量为 j 的情况下，能装下的最大时间
    // 初始化为 0，大小为 target + 1
    vector<int> dp(target + 1, 0);
    //这里压缩成一维了，逆向遍历用的就是上一轮i - 1的数据.
    // 0/1 背包核心流程
    for (int i = 0; i < n; i++) { // 遍历每一道题
        int t = times[i];
        for (int j = target; j >= t; j--) { // 逆序遍历背包容量
            // 状态转移：要么不选这题，要么选了这题并加上剩余容量的最优解
            dp[j] = max(dp[j], dp[j - t] + t);
        }
    }

    // 这一科的最短时间 = 总时间 - 那个分得少一点的大脑的时间
    return sum - dp[target];
}

int main() {
    int s[4];
    for (int i = 0; i < 4; i++) cin >> s[i];

    int total_time = 0;
    for (int i = 0; i < 4; i++) {
        total_time += solve_subject(s[i]);
    }

    cout << total_time << endl;
    return 0;
}