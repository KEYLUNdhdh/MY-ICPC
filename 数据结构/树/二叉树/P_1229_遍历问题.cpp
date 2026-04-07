#include <bits/stdc++.h>
#define int long long
using namespace std;
//如果一个节点只有一个子节点（只有左孩子，或者只有右孩子），前序遍历都是根-子，后序遍历都是子-根。这种情况下，我们无法通过这两个序列判断这个孩子到底是在左边还是在右边。
//对于只有一个子的根节点，根和子必然是紧挨着的
signed main()
{
    string pre, ne;
    cin >> pre >> ne;
    int ans = 1;
    for (int i = 0; i < pre.size() - 1;i++)
    {
        char ch = pre[i];
        int pos = ne.find(ch);
        if(pre[i + 1] == ne[pos - 1])
            ans *= 2;
    }
    cout << ans;
}
