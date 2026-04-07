#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;//pair<int, int>表示一个数对，方便编写我们取别名为pii

//检查函数性
bool is_func(const unordered_set<int> &A, const unordered_set<int> &B, const vector<pii> &f)
{
    unordered_map<int, int> mapping;//我们利用哈希表去构建映射，mapping[u][v]表示u -> v
    for(const auto &[u, v] : f)
    {
        if(A.find(u) == A.end() || B.find(v) == B.end())//如果元素不存在，则不是函数
            return false;
        if(mapping.count(u) && mapping[u] != v)//如果一个u对应多个v，则不是函数
            return false;
        mapping[u] = v;//存入映射关系
    }
    return mapping.size() == A.size();
}
//检查f与g是否等价
bool is_equivalent(const vector<pii> &f, const vector<pii> &g)
{
    unordered_map<int, int> map_f, map_g;
    for(const auto &[u, v] : f)
        map_f[u] = v;
    for(const auto &[u, v] : g)
        map_g[u] = v;
    return map_f == map_g;//判断映射关系是否等价
}
//检查单射
bool is_injective(const vector<pii> &f)
{
    unordered_set<int> range_elements;
    for(const auto &[u, v] : f)
    {
        if(range_elements.count(v))//如果v已经存在，说明v有多个原像，则不是单射
            return false;
        range_elements.insert(v);//我们存入v
    }
    return true;//如果循环跑完没有return，则是单射
}
//检查满射
bool is_surjective(const unordered_set<int> &B, const vector<pii> &f)
{
    unordered_set<int> range_elements;
    for(const auto &[u, v] : f)
        range_elements.insert(v);//说明v有u这个原像，存入v
    return range_elements.size() == B.size();//检查每个y是否都有原像了
}
//检查双射
bool is_bijective(const unordered_set<int> &B, const vector<pii> &f)
{
    return is_injective(f) && is_surjective(B, f);//既单射又满射
}

void solve(int t)
{
    int n, m;
    cin >> n >> m;

    unordered_set<int> A, B;//unordered_set自带哈希去重机制，我们不用再去重
    //读入A中的元素
    for (int i = 0; i < n;i++)
    {
        int x;
        cin >> x;
        A.insert(x);
    }
    //读入B中的元素
    for (int i = 0; i < m;i++)
    {
        int x;
        cin >> x;
        B.insert(x);
    }
    //f中有k个映射关系
    int k;
    cin >> k;
    vector<pii> f(k);
    for (int i = 0; i < k;i++)
        cin >> f[i].first >> f[i].second;
    //g中有q个映射关系
    int q;
    cin >> q;
    vector<pii> g(q);
    for (int i = 0; i < q;i++)
        cin >> g[i].first >> g[i].second;

    cout << "--- Case #" << t << " ---" << "\n";
    bool is_function_f = is_func(A, B, f);//检查f是否为函数
    bool is_function_g = is_func(A, B, g);//检查f是否为函数
    cout << "f为合法函数: " << (is_function_f ? "Yes" : "No") << "\n";
    cout << "g为合法函数: " << (is_function_g ? "Yes" : "No") << "\n";

    if (is_function_f || is_function_g) 
    {
        cout << "单射: " << (is_injective(f) ? "Yes" : "No") << "\n";
        cout << "满射: " << (is_surjective(B, f) ? "Yes" : "No") << "\n";
        cout << "双射: " << (is_bijective(B, f) ? "Yes" : "No") << "\n";
        bool valid_g = is_func(A, B, g);
        if (valid_g)
            cout << "f与g等价: " << (is_equivalent(f, g) ? "Yes" : "No") << "\n";
    }

    cout << "\n";
}
signed main()
{
    //优化标准I/O速度
    ios::sync_with_stdio(0);
    cin.tie(0);
    //支持多测
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T;i++)
    {
        solve(i);
    }

    return 0;
}