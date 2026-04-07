//离散化本质就是利用unique函数建立了一种映射关系。这题时间复杂度为O(NlogN)
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 5e4 + 5;
int a[MAXN];
int n;
void solve()
{
    int vis[MAXN] ={0};
    cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n;i++)
        cin >> vec[i];
    // nums 用于离散化，存储所有出现过的原始下标
    vector<int> nums = vec;
    // 1. 排序：将下标从小到大排列
    // 假设 nums 原本是 [10, 1, 10, 100]
    // sort 后变成: [1, 10, 10, 100]
    sort(nums.begin(), nums.end());
    // 2. 去重：unique 会把重复元素移到末尾，并返回“新数组”的尾部迭代器
    // unique 后逻辑上变成: [1, 10, 100, (垃圾数据)]
    // erase 会把后面的垃圾数据删掉
    // 最终 nums 变成: [1, 10, 100]
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    // 定义一个 lambda 函数，用于查询原始值 x 对应的“新编号”
    auto getid = [&](int x)
    {
        // lower_bound 在有序数组中通过二分查找找到第一个 >= x 的位置
        // 减去 nums.begin() 得到下标 (0, 1, 2...)
        // +1 是为了让下标从 1 开始，方便并查集处理 (1, 2, 3...)
        return lower_bound(nums.begin(), nums.end(), x) - nums.begin() + 1;
    };
    int id;
    for (int i = 0; i < n;i++)
    {
        id = getid(vec[i]);
        if(!vis[id])
        {
            vis[id] = 1;
            cout << vec[i] << " ";
        }
    }
    cout << "\n";
    return;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--)
        solve();
}