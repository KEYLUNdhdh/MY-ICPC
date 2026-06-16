#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
// 获取高精度时间戳作为动态随机种子，确保每次运行的哈希映射规则都不同
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
const u64 SEED = rnd();

struct HashMap
{
    // MOD 取一个质数，通常是最大插入元素数量的 1.5 ~ 2 倍。
    // 本题 n = 5e6，8388617 是一个非常合适的质数（2^23 附近）
    static const int MOD = 8388617;
    // MAX_NODE 是最大不同元素的个数，等于 n
    static const int MAXNODE = 5e6 + 5;

    int head[MOD];
    int nxt[MAXNODE];
    u64 keys[MAXNODE];
    u64 vals[MAXNODE];
    int tot;// 节点计数器

    // SplitMix64 强哈希算法（专门应对恶意构造的碰撞数据）
    inline int hashFunc(u64 x)
    {
        x += SEED;// 加上动态随机种子，破解出题人的预谋
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return (x ^ (x >> 31)) % MOD;
    }

    // 重载 [] 运算符，用法和 unordered_map 完全一样
    inline u64 &operator[](const u64 k)
    {
        int h = hashFunc(k);
        // 遍历该哈希值对应的链表
        for (int i = head[h]; i; i = nxt[i])
            if(keys[i] == k)
                return vals[i];// 找到了，直接返回值的引用

        // 如果没找到，开辟一个新节点并插入到链表头部
        // 链式前向星，头插法
        ++tot;
        keys[tot] = k;
        vals[tot] = 0;// 题目要求初始 f(x) = 0
        nxt[tot] = head[h];
        head[h] = tot;
        return vals[tot];
    }

    // 应对多组测试数据的清空函数
    inline void clear()
    {
        // 注意：千万不要用 memset 清空整个 head，对于 8e6 的数组，
        // 每次 memset 会带来巨大开销，容易 TLE。
        // 最优解是只清空用过的 head 位置：
        for (int i = 1; i <= tot;i++)
            head[hashFunc(keys[i])] = 0;

        tot = 0;// 重置节点计数器
    }
} f; // ⚠️强力建议：将哈希表实例化为全局变量，避免爆栈，且全局数组会自动初始化为 0
