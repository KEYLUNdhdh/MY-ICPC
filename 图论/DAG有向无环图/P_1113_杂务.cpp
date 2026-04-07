//DAG（有向无环图）上的动态规划 问题，或者说是求 关键路径（Critical Path）。
//杂务 k 的准备工作只可能在杂务 1 至 k-1 中。
//这意味着输入本身就是 拓扑序 的，我们甚至不需要建图或进行复杂的排序，直接线性处理即可。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e4 + 5;
int f[MAXN];// f[i] 表示完成第 i 项任务所需要的最短总时间（即它的结束时间）
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    int ans = 0;
    for (int i = 1; i <= n;i++)
    {
        int id, len, tp;
        cin >> id >> len;

        int pre = 0;
        while(cin >> tp && tp != 0)
        {
            // 当前任务必须等所有前置任务中结束最晚的那个完成
            pre = max(pre, f[tp]);
        }
        f[id] = len + pre;
        ans = max(f[id], ans);
    }
    cout << ans;
}