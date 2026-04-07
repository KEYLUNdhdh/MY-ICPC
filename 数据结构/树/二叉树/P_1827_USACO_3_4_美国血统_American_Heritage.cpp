#include <bits/stdc++.h>
using namespace std;

// 递归函数：传入当前子树的中序和前序字符串
void solve(string in,string pre)
{
    // 递归边界：如果字符串为空，说明没有节点了，直接返回
    if(in.empty())
        return;
    
    // 1. 找到根节点
    // 前序遍历的第一个字符一定是根
    char root = pre[0];
    
    // 2. 在中序遍历中找到根节点的位置
    int index = in.find(root);

    // 根左边的是左子树的中序
    string lin = in.substr(0, index);

    // 根右边的是右子树的中序
    string rin = in.substr(index + 1);

    // 4. 切割前序字符串
    // 左子树的长度 = left_in.length()
    // 前序字符串要跳过第1个(因为是根)，然后截取跟左子树中序一样长的长度
    int len_left = lin.length();
    string lpre = pre.substr(1, len_left);
    string rpre = pre.substr(len_left + 1);

    // 5. 按照后序遍历规则输出：左 -> 右 -> 根
    solve(lin, lpre);// 递归处理左子树
    solve(rin, rpre);// 递归处理右子树
    // 这里的输出就是“后序”的体现
    cout << root;
}
int main()
{
    string iin, ipre;
    cin >> iin >> ipre;
    //递归处理
    solve(iin, ipre);

    return 0;
}