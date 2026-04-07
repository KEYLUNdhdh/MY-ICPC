#include <bits/stdc++.h>
using namespace std;
// int n, q;
// const int N = 2e5 + 5;
// int a[N], b[N];
// int cnt[N];
// int d1[N];
// int d2[N];
// int main()
// {
//     ios::sync_with_stdio(0);
//     cin.tie(0);
//     int t;
//     cin >> t;
//     while(t--)
//     {
//         cin >> n >> q;
//         for (int i = 0; i <= n;i++)
//         {
//             cnt[i] = 0, d1[i] = 0, d2[i] = 0;
//         }
//         for (int i = 1; i <= n; i++)
//         {
//             cin >> a[i] >> b[i];
//         }
//         for (int i = 1; i <= n;i++)
//         {
//             if(a[i] == b[i])
//             {
//                 cnt[a[i]]++;
//             }
//             else
//             {
//                 cnt[a[i]]++;
//                 cnt[b[i]]++;
//             }
//             if(abs(a[i] - b[i]) == 1)
//                 d1[a[i] > b[i] ? b[i] : a[i]]++;
//             else if(abs(a[i] - b[i]) == 2)
//                 d2[a[i] > b[i] ? b[i] : a[i]]++;
//         }
//         int x;
//         while(q--)
//         {
//             cin >> x;
//             int ans = cnt[x - 1] + cnt[x]  + cnt[x + 1] - d1[x - 1] - d1[x] - d2[x - 1];
//             cout << n - ans << " ";
//         }
//         cout << "\n";
//     }
// }
//知识点 差分数组
// 差分数组（Difference Array） 的核心思想是：把“一段区间的修改”转化为“两个端点的修改”。
// 这就像开关水龙头一样，只要你在起点打开，水就会一直流下去，直到你在终点把它关掉。
//假设数组长度为 5，我们要让区间 [2, 4] 的数字都 +1。
// /修改差分数组：
//在 L=2 处 +1：diff[2] += 1
//在 R+1=5 处 -1：diff[5] -= 1
//还原真实数值（求前缀和）：最后，我们对 diff 数组求前缀和，就能得到每个位置实际的数值。
//nums[1] = diff[1] = 0
//nums[2] = diff[1] + diff[2] = 0 + 1 = 1 （影响开始了）
//nums[3] = nums[2] + diff[3] = 1 + 0 = 1 （影响持续中）
//nums[4] = nums[3] + diff[4] = 1 + 0 = 1 （影响持续中）
//nums[5] = nums[4] + diff[5] = 1 - 1 = 0 （影响结束了）
//结果：0, 1, 1, 1, 0。我们可以看到，区间 [2, 4] 成功全部加了 1，而我们只动了两个下标。
//模板
void solve_difference_array() {
    int n, q;
    cin >> n >> q;
    
    // 差分数组，大小要注意防止越界
    // 如果 n 是 200000，R+1 可能是 200001，所以要开大一点
    vector<int> diff(2e5 + 10, 0); 
    
    int range = 100; // 假设舒适范围是 [val-100, val+100]

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        
        // 计算两个区间 [L1, R1] 和 [L2, R2]
        int L1 = max(1, a - range); // 防止下标小于1
        int R1 = min(n, a + range); // 防止下标超过n
        
        int L2 = max(1, b - range);
        int R2 = min(n, b + range);

        // 判断是否有交集
        // 如果 区间1的右端 < 区间2的左端，或者反之，则无交集
        // 但为了方便判断，通常先让 L1 <= L2。
        if (L1 > L2) { swap(L1, L2); swap(R1, R2); }

        if (R1 >= L2 - 1) { 
            // 有交集（或者刚好连着），合并！
            // 为什么是 L2-1？因为 [1,2] 和 [3,4] 虽然不重叠，但可以合并成 [1,4] 连着加
            // 并集的左端是 L1，右端是 max(R1, R2)
            int final_L = L1;
            int final_R = max(R1, R2);
            
            diff[final_L] += 1;
            diff[final_R + 1] -= 1;
        } else {
            // 无交集，分别处理
            diff[L1] += 1;
            diff[R1 + 1] -= 1;
            
            diff[L2] += 1;
            diff[R2 + 1] -= 1;
        }
    }

    // 步骤三：求前缀和，还原 nums 数组
    vector<int> nums(2e5 + 10);
    int current_val = 0;
    for (int i = 1; i <= n; i++) {
        current_val += diff[i]; // 累加差分值
        nums[i] = current_val;  // 得到当前位置的实际值
    }

    // 回答询问
    while (q--) {
        int k;
        cin >> k;
        cout << n - nums[k] << " ";
    }
    cout << endl;
}
// #include <bits/stdc++.h>
// using namespace std;
// int n, q,a,b;
// map<int, int> mp;
// int main()
// {
//     int t;cin >> t;
//     while(t--)
//     {
//         cin >> n >> q;
//         vector<int> num(n + 5,0);
//         for (int i = 0; i < n;i++)
//         {
//             cin >> a >> b;
//             for (int i = -1; i <= 1;i++)
//             {
//                 mp[a + i] = 1;
//                 mp[b + i] = 1;
//             }
//             for(auto it : mp)
//             {
//                 num[it.first]++;
//             }
//             mp.clear();
//         }
//         int x;
//         for (int i = 0; i < q;i++)
//         {
//             cin >> x;
//             cout << n - num[x] << " ";
//         }
//         cout << "\n";
//     }
// }

