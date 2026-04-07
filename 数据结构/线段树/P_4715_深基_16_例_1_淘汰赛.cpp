//队列操作，最好写

// #include <bits/stdc++.h>
// using namespace std;
// struct g{
//     int val, id;
// };

// g cmp(g g1,g g2)
// {
//     if(g1.val > g2.val)
//         return g1;
//     else
//         return g2;
// }
// int main()
// {
//     ios::sync_with_stdio(0);
//     cin.tie(0);
//     int n;
//     cin >> n;
//     deque<g> d((int)pow(2,n));
//     for (int i = 0; i < pow(2,n);i++)
//     {
//         cin >> d[i].val;
//         d[i].id = i + 1;
//     }
//     while(d.size() != 2)
//     {
//         int cur = d.size() >> 1;
//         while(cur--)
//         {
//             d.push_back(cmp(d[0], d[1]));
//             d.pop_front();
//             d.pop_front();
//         }
//     }
//     if(d[0].val > d[1].val)
//     {
//         cout << d[1].id;
//     }
//     else
//     {
//         cout << d[0].id;
//     }
//     return 0;
// }
//下面是线段树/锦标赛树/赢者树做法
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,rl;
const int N = 1 << 7;
struct guo{
    int id, val;
};
guo tree[N];
guo a[N];
inline int ls(int x)
{
    return x << 1;
}
inline int rs(int x)
{
    return x << 1 | 1;
}

void build(int p,int l,int r)
{
    if(l == r)
    {
        // 1. 递归边界（叶子节点）
        // start == end 意味着区间长度为1，即具体的某一个国家
        tree[p].val = a[l].val;
        tree[p].id = a[l].id;
        return;
    }
    // 2. 递归构建子树
    int mid = l + r >> 1;
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);
    // 3. 核心逻辑（父节点存储胜者）
    // 当前节点（下一轮晋级者） = 左孩子和右孩子中能力值更大的那个
    tree[p] = tree[ls(p)].val > tree[rs(p)].val ? tree[ls(p)] : tree[rs(p)];
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= (1 << n);i++)
    {
        cin >> a[i].val;
        a[i].id = 1;
    }
    build(1, 1, 1 << n);
    if(tree[1].val == tree[2].val)
    {
        cout << tree[3].id;
    }
    else
    {
        cout << tree[2].id;
    }
}