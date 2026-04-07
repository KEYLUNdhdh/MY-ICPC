//离散化本质就是利用unique函数建立了一种映射关系。这题时间复杂度为O(NlogN)
#include <bits/stdc++.h>
using namespace std;
// 为什么是 2e5？
// 因为 n (约束数) 最大 1e5，每个约束涉及 2 个变量 (i, j)。
// 所以最多有 2 * 1e5 个不同的变量。
const int MAXN = 2e5 + 5;
int fa[MAXN];// 并查集数组，存储父节点
int discrete[MAXN];
struct Constraint{
    int u, v, e;// u:左变量, v:右变量, e:是否相等(1相等, 0不等)
};

inline int Find(int x)
{
    if(fa[x] == x)
        return x;
    else
        return fa[x] = Find(fa[x]);
}

void solve()
{
    int n;
    cin >> n;
    // queries 存储所有的操作，方便后面遍历两次
    vector<Constraint> queries(n);
    vector<int> nums;
    for (int i = 0; i < n;i++)
    {
        cin >> queries[i].u >> queries[i].v >> queries[i].e;
        // 把出现过的变量下标都扔进 nums 桶里
        nums.push_back(queries[i].u);
        nums.push_back(queries[i].v);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()),nums.end());
    auto get_id = [&](int x)
    {
        return lower_bound(nums.begin(), nums.end(), x) - nums.begin() + 1;
    };
    // m 是不同变量的总数（离散化后的大小）
    int m = nums.size();
    // 初始化并查集，只初始化用到的部分 (1 到 m)
    // 这一步非常重要，每组测试数据必须重置！
    for (int i = 1; i <= m;i++)
        fa[i] = i;
    // 第一次遍历：只处理相等条件 (e=1)
    for (int i = 0; i < n;i++)
    {
        if(queries[i].e == 1)
        {
            // 将原始下标 u, v 转换为离散化后的编号
            int rootU = Find(get_id(queries[i].u));
            int rootV = Find(get_id(queries[i].v));
            // 合并集合
            if(rootU != rootV)
            {
                fa[rootU] = rootV;
            }
        }
    }
    //判断是否冲突
    bool conflict = false;
    // 第二次遍历：检查不等条件 (e=0)
    for (int i = 0; i < n;i++)
    {
        if(queries[i].e == 0)
        {
            int rootU = Find(get_id(queries[i].u));
            int rootV = Find(get_id(queries[i].v));
            // 如果题目要求 u != v，但并查集发现它们已经在同一个集合里了
            // 说明产生了矛盾
            if(rootU == rootV)
            {
                conflict = true;
                break;
            }
        }
    }
    if(conflict)
    {
        cout << "NO\n";
    }
    else
        cout << "YES\n";
}

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        solve(  );
    }
}