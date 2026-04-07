//Treap 是一种非常优雅的数据结构，它结合了 二叉搜索树 (BST) 的性质和 堆 (Heap) 的性质：
//BST 性质：对于任意节点，左子树所有节点的值 <= 当前节点值 <= 右子树所有节点的值。这决定了它的内容。
//Heap 性质：每个节点被赋予一个随机的优先级 (dat)，父节点的优先级必须小于（或大于，看具体实现）子节点的优先级。
//这决定了它的形态。因为优先级是随机的，Treap 能够概率性地保证树的高度在 O(log N)，从而避免普通 BST 退化成链表。
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int x = 0;
    int f = 1;
    char ch = getchar();
    while(ch <'0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return f * x;
}
const int maxn = 1e6 + 5;
const int INF = 1e9;
int na;
int ch[maxn][2];// 存储树的结构。ch[i][0] 是节点 i 的左孩子，ch[i][1] 是右孩子
int val[maxn];// 存储节点实际的数值 (输入数据中的 x)
int dat[maxn];// 存储随机生成的优先级 (维护平衡的关键)
//让树具有堆性质，保证查找时间复杂度近似O(logN)而不是退化成O(N)
int sizee[maxn];// 存储以当前节点为根的子树大小 (用于查询排名)
int cnt[maxn];// 存储当前数值出现的次数 (处理“可重集合”的需求)
int tot;// 内存池计数器，表示当前用到了第几个节点
int root;// 根节点的编号

// 新建节点函数
int New(int v)
{
    val[++tot] = v;// 分配新编号，赋值
    dat[tot] = rand();// 核心：随机生成优先级！
    sizee[tot] = 1;// 新节点本身大小为 1
    cnt[tot] = 1;// 初始副本数为 1//实际是统计这个数出现几次
    return tot;// 返回新节点的编号
}
//更新大小
void pushup(int id)
{
    // 当前子树大小 = 左子树大小 + 右子树大小 + 当前节点本身的副本数
    sizee[id] = sizee[ch[id][0]] + sizee[ch[id][1]] + cnt[id];
}
void build()
{
    // 插入 -INF 和 INF 作为哨兵节点
    //哨兵节点：最左边放一个负无穷，最右边放一个正无穷。防止在查询前驱/后继或删除时越界访问空指针，简化边界判断。
    //因为多了这两个虚构的点，最后查询排名时需要进行 -1 之类的修正。
    root = New(-INF);
    ch[root][1] = New(INF);
    // 更新根节点大小
    pushup(root);
}
// d=0 代表左旋（通常为了提升右子树），d=1 代表右旋（通常为了提升左子树）
// 注意：代码里的 d 和通常的定义可能相反，我们看逻辑
void Rotate(int &id,int d)
{
    int temp = ch[id][d ^ 1];// temp 是我们要把其“提上来”的子节点
    ch[id][d ^ 1] = ch[temp][d];// 把 temp 的内侧子树挂到 id 的下面
    ch[temp][d] = id;// 把 id 变成 temp 的子节点（temp 篡位成功，变成了父节点）
    id = temp;// 更新当前指针指向新的父节点 temp
    // 先更新原来的父节点(现在的子节点)，再更新新的父节点
    pushup(ch[id][d]);
    pushup(id);
}

void insert(int& id,int v)
{
    if(!id)//0值说明当前节点有空位，直接插入
    {
        id = New(v);// 找到空位，直接新建
        return;
    }
    if(val[id] == v)// 如果值相等，直接增加计数器（不增加新节点）
    {
        cnt[id]++;
    }
    else
    {
        int d = v < val[id] ? 0 : 1;// d=0 表示要去左边，d=1 表示要去右边
        insert(ch[id][d], v);// 递归插入
        // 插入后回溯检查：如果子节点的优先级 > 当前节点优先级，违反了堆性质
        // 需要旋转！让优先级高的节点在上面，同时不会破坏BST性质
        // 如果 d=0 (在左边插入)，且左孩子优先级高，我们需要右旋 (Rotate(..., 1))
        // 所以这里写 Rotate(id, d ^ 1) 是非常精妙的对应
        if(dat[id] < dat[ch[id][d]])
        {
            Rotate(id, d ^ 1);//将d这个子节点对应的子树提上来
        }
    }
    pushup(id);//更新当前节点大小
}
//删除操作
void Remove(int &id,int v)
{
    if(!id)//没找到
        return;
    if(v == val[id])//找到了目标节点
    {
        if(cnt[id] > 1)//有多个副本直接--就行
        {
            cnt[id]--, pushup(id);//别忘了更新大小
            return;
        }
        //到这里没return说明又该节点且只有一个副本，要真正删除
        if(ch[id][0] || ch[id][1])//如果不是叶子节点(还有儿子)
        {
            // 我们需要把当前节点“旋转”到树的底部（变成叶子）再删除
            // 为了保持堆性质，我们要把优先级较大的那个儿子提上来
            //这里比较优先级是儿子之间比较
            if(!ch[id][1] || dat[ch[id][0]] > dat[ch[id][1]])
            {
                //如果左节点优先级大于右节点或者右节点没东西，就把左节点提上来
                Rotate(id, 1);
                Remove(ch[id][1], v);
            }
            else
            {
                //反之就提右节点
                Rotate(id, 0);
                Remove(ch[id][0], v);
            }
            pushup(id);//更新大小
        }
        else
        {
            id = 0;// 是叶子节点，直接删除（指针置空）
        }
        return;
    }
    // 没找到，继续按 BST 性质递归找
    v < val[id] ? Remove(ch[id][0], v) : Remove(ch[id][1], v);
    pushup(id);//别忘了更新大小
}
// 查询 v 的排名（比 v 小的数的个数 + 1）
//类似二分查找
int get_rank(int id,int v)
{
    if(!id)//如果节点不存在
        return 1;
    if(v == val[id])// 找到了：排名 = 左子树大小 + 1
        return sizee[ch[id][0]] + 1;
    else if(v < val[id])// 在左边，递归查左边(直接查找)
        return get_rank(ch[id][0], v);
    else// 在右边：排名 = 左子树所有人 + 当前节点所有人 + 右边查出来的排名
        return sizee[ch[id][0]] + cnt[id] + get_rank(ch[id][1], v);
}
// 查找排名为 rank 的数的值
int get_val(int id,int rank)
{
    if(!id)//没找到
        return INF;
    if(rank <= sizee[ch[id][0]])// 排名很小，肯定在左子树
        return get_val(ch[id][0], rank);
    else if (rank <= sizee[ch[id][0]] + cnt[id])// 排名刚好落在当前节点区间内
        return val[id];
    else// 排名很大，在右子树。注意：去右边查的时候，排名要减去左边和中间已经占用的人数
        return get_val(ch[id][1], rank - sizee[ch[id][0]] - cnt[id]);
}
// 找前驱：小于 v 且最大的数。复杂度概率上为O(log n)
int get_pre(int v)
{
    int id = root, pre;// pre 记录当前找到的最优解
    while(id)//不断查找直到找到id不存在的情况
    {
        // 如果当前值 < v，它是一个候选的前驱。
        // 但我们要找“最大”的，所以往右子树走（右边更大），看看有没有更好的。
        if(val[id] < v)
        {
            pre = val[id];
            id = ch[id][1];
        }
        // 如果当前值 >= v，它没资格做前驱，必须往左走找更小的。
        else
            id = ch[id][0];
    }
    return pre;
}
// 找后继：大于 v 且最小的数
int get_next(int v)
{
    int id = root, next;
    while(id)
    {
        // 如果当前值 > v，它是候选后继。
        // 要找“最小”的，所以往左子树走。
        if(val[id] > v)
        {
            next = val[id], id = ch[id][0];    
        }
        // 如果当前值 <= v，没资格做后继，往右走找更大的。
        else
            id = ch[id][1];
    }
    return next;
}

int main()
{
    ios::sync_with_stdio(0);
    build();// 必须先 build，初始化哨兵节点
    na = read();
    for (int i = 1; i <= na;i++)
    {
        int cmd = read(),x = read();
        if (cmd == 1)
            insert(root, x);
        else if(cmd == 2)
            Remove(root, x);
        // 注意：get_rank 算上了 -INF 这个哨兵，所以结果偏大了 1，需要减掉
        else if(cmd == 3)
            cout << get_rank(root, x) - 1 << "\n";
        // 注意：我们要查第 x 名，但因为有 -INF 占了第 1 名，所以实际要查 x+1 名
        else if(cmd == 4)
            cout << get_val(root, x + 1) << "\n";
        else if(cmd == 5)
            cout << get_pre(x) << "\n";
        else if(cmd == 6)
            cout << get_next(x) << "\n";
    }
    return 0;
}