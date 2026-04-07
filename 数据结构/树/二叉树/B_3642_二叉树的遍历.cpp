#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;

// 定义二叉树节点结构体
// 使用静态数组模拟，tree[i] 代表编号为 i 的节点
struct Node {
    int left;  // 左孩子编号
    int right; // 右孩子编号
} tree[MAXN];

int n;

// 1. 前序遍历：根 -> 左 -> 右
void pre_order(int id) {
    if (id == 0) return; // 递归终止条件：遇到空节点（0）
    
    cout << id << " ";   // 输出根
    pre_order(tree[id].left);  // 递归左
    pre_order(tree[id].right); // 递归右
}

// 2. 中序遍历：左 -> 根 -> 右
void in_order(int id) {
    if (id == 0) return;
    
    in_order(tree[id].left);   // 递归左
    cout << id << " ";         // 输出根
    in_order(tree[id].right);  // 递归右
}

// 3. 后序遍历：左 -> 右 -> 根
void post_order(int id) {
    if (id == 0) return;
    
    post_order(tree[id].left); // 递归左
    post_order(tree[id].right);// 递归右
    cout << id << " ";         // 输出根
}


int main() {
    // 必须优化 I/O，否则 10^6 数据量读取和输出会超时
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    // 建树过程
    // 题目说：之后 n 行，第 i 行表示结点 i 的左右子节点
    // 所以循环从 1 到 n，直接对应数组下标 i
    for (int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        tree[i].left = l;
        tree[i].right = r;
    }

    // 题目明确说明：根节点的编号为 1
    // 所以我们从 1 开始遍历

    // 输出前序
    pre_order(1);
    cout << "\n";

    // 输出中序
    in_order(1);
    cout << "\n";

    // 输出后序
    post_order(1);
    cout << "\n";

    return 0;
}