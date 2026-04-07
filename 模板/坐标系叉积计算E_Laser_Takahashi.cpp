#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct point{
    int x, y;
};
// 叉积计算：x1*y2 - x2*y1
// 结果 > 0 表示 a 在 b 的顺时针方向（相对原点）
// 结果 < 0 表示 a 在 b 的逆时针方向
// 结果 = 0 表示共线
ll cross(const point &a,const point &b)
{
    return (ll)a.x * b.y - (ll)a.y * b.x;
}
//叉积只能处理夹角小于 180 度的情况。所以必须先粗略地按上半、下半平面分开。
//叉积排序：在同半平面内，利用叉积性质排序。这个 cmp 函数实现了按逆时针（角度从小到大）排序。
//第一部分 (ah = 0)：
//上半平面 + 正 X 轴范围：y > 0 或者 (y = 0 且 x > 0)。
//对应角度：[0, 180)。这部分的点被强制排在前面。
//第二部分 (ah = 1)：
//下半平面 + 负 X 轴范围：y < 0 或者 (y = 0 且 x < 0)。对应角度：[180, 360)。这部分的点被强制排在后面。
bool cmp(const point &a,const point &b)
{
    // 判断点属于上半平面还是下半平面
    // 这里的逻辑将平面分为两部分：
    // ah = 0: 上半平面 (y>0) 或 正x轴 (y=0, x>0) -> 角度范围 [0, 180)
    // ah = 1: 下半平面 (y<0) 或 负x轴 (y=0, x<0) -> 角度范围 [180, 360)
    int ah = (a.y < 0 || (a.y == 0 && a.x < 0));
    int bh = (b.y < 0 || (b.y == 0 && b.x < 0));
    // 如果不在同一个半平面，下半平面的角度一定大于上半平面
    if(ah != bh)
        return ah < bh;
    // 如果在同一个半平面，利用叉积判断相对顺序
    // cross > 0 代表 a 的角度小于 b (逆时针方向 a 在 b 前面)
    return cross(a, b) > 0;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n, q;
    cin >> n >> q;
    vector<point> pt(n);
    for (int i = 0; i < n;i++)
    {
        cin >> pt[i].x >> pt[i].y;
    }
    // ord 数组存储的是怪物的下标 (0 ~ n-1)
    vector<int> ord(n);
    for (int i = 0; i < n;i++)
        ord[i] = i;// 初始化 ord 为 0, 1, 2...
    // 使用 cmp 对下标进行排序
    sort(ord.begin(), ord.end(), [&](int i, int j)
         { return cmp(pt[i], pt[j]); });
    // 【关键】题目要求顺时针旋转，而 cmp 是逆时针排序。
    // 所以 reverse 一下，变成了顺时针顺序（角度从大到小）。
    reverse(ord.begin(), ord.end());
    // rev[i] 表示：原始编号为 i 的怪物，在排序后的数组中排第几名
    vector<int> rev(n);
    for (int i = 0; i < n;i++)
    {
        rev[ord[i]] = i;
    }
    // l[i]: 排序后第 i 个怪物所在的“同角组”的【起始下标】
    // r[i]: 排序后第 i 个怪物所在的“同角组”的【结束下标的下一个位置】(左闭右开区间)
    vector<int> l(n), r(n);
    // 预处理 l 数组
    l[0] = 0;
    for (int i = 1; i < n;i++)
    {
        // cmp 返回 true 说明 pt[ord[i]] 和 pt[ord[i-1]] 角度不同
        // 如果角度不同，l[i] 就是 i 自己；否则继承前一个的 l[i-1]
        l[i] = (cmp(pt[ord[i]], pt[ord[i - 1]]) ? i : l[i - 1]);
    }
    // 预处理 r 数组
    r[n - 1] = n;
    for (int i = n - 2; i >= 0;i--)
    {
        // 同理，如果和后一个角度不同，r[i] 就是 i+1；否则继承后一个
        r[i] = (cmp(pt[ord[i + 1]], pt[ord[i]]) ? i + 1 : r[i + 1]);
    }
    while(q--)
    {
        int a, b;
        cin >> a >> b;
        --a, --b;// 转为 0-based 索引

        // 1. 找到怪物 a 和 b 在顺时针序列中的位置
        // 2. 将位置修正为它们所在“同角组”的边界
        // a 变成所在组的起点，b 变成所在组的终点(开区间)
        a = l[rev[a]];
        b = r[rev[b]];
        if(a < b)
        {
            // 情况1：顺时针没有跨越数组边界 (没有经过 0 度线)
            // 直接相减
            cout << b - a << "\n";
        }
        else
            // 情况2：跨越了边界
            // 总数 n - (中间未被覆盖的部分 a - b)
            // 或者理解为：后半段(n-a) + 前半段(b)
            cout << n - (a - b) << "\n";
    }
}