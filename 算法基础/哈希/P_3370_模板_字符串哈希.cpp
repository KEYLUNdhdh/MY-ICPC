// #include  <bits/stdc++.h>
// using namespace std;
// #define ull unsigned long long
// const int N = 1e4 + 5;
// ull base = 131;// 进制数，经验值，常用 131, 13331 等质数
// int n, ans = 1;// n是字符串个数，ans是结果（至少有1种）
// int prime = 233317;// 一个用来乱搞的加数，增加随机性
// ull mod = 212370440130137957ll;// 一个巨大的质数，作为模数
// //普通的字符串哈希实现过程
// ull hashe(string s)
// {
//     int len = s.length();
//     ull ans = 0;
//     for (int i = 0; i < len;i++)
//     {
//         ans = (ans * base + (ull)s[i]) % mod + prime;
//     }
//     return ans;
// }
// //以下是防止不同字符串得到的特征值冲突
// // // 假设 mod 是一个我们可以接受的数组大小，比如 1000000
// // bool check[1000000]; // 记录坑位是否被占
// // string parking_lot[1000000]; // 记录坑位里停的是谁

// // int insert(string s) {
// //     int h = hash(s); // 算出初始位置
// //     // 当这个位置有人，并且那个人不是我（真冲突了）
// //     while(check[h] && parking_lot[h] != s) {
// //         h = (h + 19260817) % 1000000; // 往后跳，记得取模防止越界
// //     }
// //     check[h] = true;
// //     parking_lot[h] = s;
// //     return h; // 返回最终安家的位置
// // }
// int main()
// {
//     int n;
//     cin >> n;
//     set<int> ss;
//     while(n--)
//     {
//         string tp;
//         cin >> tp;
//         int t = hashe(tp);
//         ss.insert(t);
//     }
//     cout << ss.size();
// }

// //所以，为了避免真正翻车我们使用多重哈希去计算同一个字符串，只有当两个字符串求出的所有哈希值一致，我们才判断他们相等

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

// 定义双哈希结构体
struct StringHash {
    ull h1, h2;
    // 重载 < 运算符，为了让 sort 知道怎么给两个结构体排序
    bool operator<(const StringHash &b) const {
        if (h1 != b.h1) return h1 < b.h1;
        return h2 < b.h2;
    }
    // 重载 != 运算符，为了方便判断
    bool operator!=(const StringHash &b) const {
        return h1 != b.h1 || h2 != b.h2;
    }
} a[10010];

ull base1 = 131, mod1 = 1e9 + 7;
ull base2 = 13331, mod2 = 1e9 + 9;
string s;
int n;

// 计算双哈希
StringHash compute(string s) {
    int len = s.length();
    ull ans1 = 0, ans2 = 0;
    for (int i = 0; i < len; i++) {
        ans1 = (ans1 * base1 + s[i]) % mod1;
        ans2 = (ans2 * base2 + s[i]) % mod2;
    }
    return {ans1, ans2};//返回两个值可以这么写
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        a[i] = compute(s);//可以直接给结构体赋值
    }

    // 1. 排序：让相同的哈希值挨在一起
    // 类似于把所有相同的字符串归拢到一起
    sort(a + 1, a + n + 1);

    // 2. 统计
    int ans = 1;
    for (int i = 1; i < n; i++) {
        // 直接比较结构体，如果 h1 或 h2 有一个不一样，就是新字符串
        if (a[i] != a[i + 1]) {
            ans++;
        }
    }
    
    printf("%d\n", ans);
    return 0;
}