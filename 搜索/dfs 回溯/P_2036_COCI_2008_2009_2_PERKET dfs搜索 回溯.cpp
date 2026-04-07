// #include <bits/stdc++.h>
// #define ll long long
// using namespace std;
// int mul[2000] = {0};
// int sum[2000] = {0};
// //用二进制表示选择
// int main()
// {
//     int n;
//     cin >> n;
//     int s[15] = {0};
//     int k[15] = {0};
//     for (int i = 0; i < n;i++)
//         cin >> s[i] >> k[i];
//     int u = 1 << n;
//     int  ans = 0x3f3f3f3f;
//     for (int i = 1; i < u;i++)
//     {
//         int ss = 1, kk = 0;
//         for (int j = 0; j < n;j++)
//         {
//             if (i & (1 << j))
//             {
//                 ss *= s[j];
//                 kk += k[j];
//             }
//         }
//         ans = min(ans, abs(ss - kk));
//     }
//     cout << ans;
// }

//方法二 dfs+ 回溯法
//ai说这个没有穷尽所有，且效率低下
// #include <bits/stdc++.h>
// #define ll long long
// using namespace std;
// int s[15] = {0};
// int k[15] = {0};
// int f[15] = {0};
// int n,ans = 0x3f3f3f3f,mul = 1,add = 0;
// void dfs(int p)
// {
//     if (p > n)
//         return;
//     else
//     {
//         for (int i = 0; i < n; i++)
//         {
//            if (!f[i])
//            {
//                 mul *= s[i];
//                 add += k[i];
//                 ans = min(ans, abs(mul - add));
//                 f[i] = 1;
//                 dfs(p + 1);
//                 f[i] = 0;
//                 mul /= s[i];
//                 add -= k[i];
//            }
//         }
//     }
// }
// int main()
// {
//     cin >> n;
//     for (int i = 0; i < n;i++)
//         cin >> s[i] >> k[i];
//     dfs(1);
//     cout << ans;
// }
//AI来一发
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits> // 用于 INT_MAX 或 LLONG_MAX

using namespace std;

// 使用 long long 来存储酸度乘积和最终结果，以防止溢出 (题目说明可能达到 10^9)
typedef long long ll; 

struct Ingredient {
    ll s; // 酸度
    ll b; // 苦度
};

// 全局变量来存储最小绝对差
ll min_diff = LLONG_MAX;

vector<Ingredient> ingredients;
int N;

/**
 * @brief 递归函数，用于生成所有可能的非空子集。
 * * @param index 当前正在考察的配料索引 (0 到 N-1)
 * @param current_s 当前已选配料的酸度乘积
 * @param current_b 当前已选配料的苦度总和
 * @param count 当前已选配料的数量
 */
void dfs(int index, ll current_s, ll current_b, int count) {
    
    // 1. 递归终止条件：所有食材都已考察完毕
    if (index == N) {
        // 必须选择至少一种配料
        if (count > 0) {
            ll diff = abs(current_s - current_b);
            min_diff = min(min_diff, diff);
        }
        return;
    }

    // 2. 递归展开 (两种选择):

    // --- 选择 1: 不使用当前食材 ingredients[index] ---
    dfs(index + 1, current_s, current_b, count);

    // --- 选择 2: 使用当前食材 ingredients[index] ---
    
    // 注意：酸度乘积和苦度求和
    ll new_s = current_s * ingredients[index].s;
    ll new_b = current_b + ingredients[index].b;
    
    dfs(index + 1, new_s, new_b, count + 1);
}
//每个dfs都有两个分支选和不选，更加清晰。

int main() {
    // 提升 I/O 效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N)) return 0;

    ingredients.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> ingredients[i].s >> ingredients[i].b;
    }

    // 初始调用：从索引 0 开始，初始酸度为 1 (乘法单位元)，苦度为 0，数量为 0。
    dfs(0, 1, 0, 0);

    cout << min_diff << "\n";

    return 0;
}
