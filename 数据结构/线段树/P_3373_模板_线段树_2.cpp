#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 1e5 + 5;
ll n, q, MOD;// q是操作次数, MOD是模数
ll ans[MAXN << 2], a[MAXN];//建树一般ans开4n
ll add_tag[MAXN << 2], mul_tag[MAXN << 2];// 拆分为两个tag
//2. 懒标记的维护逻辑 (难点分析)这是这道题最容易错的地方。我们需要规定一个“运算优先级”。通常规定：先执行乘法标记，再执行加法标记。即：若一个节点的值为Val，它当前的标记为 mul 和 add，则其实际值为 Val * mul + add。
inline ll ls(ll p)
{
    return p << 1;
}
inline ll rs(ll p)
{
    return p << 1 | 1;
}
// push_up: 向上传参，记得取模
inline void push_up(ll p)
{
    ans[p] = (ans[ls(p)] + ans[rs(p)]) % MOD;
}
// build时，乘法标记必须初始化为 1
void build(ll p,ll l,ll r)
{
    add_tag[p] = 0;
    mul_tag[p] = 1;// 【关键】乘法默认为1

    if(l == r)
    {
        ans[p] = a[l] % MOD;
        return;
    }
    ll mid = l + r >> 1;
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);

    push_up(p);
}
// f: 核心难点，先乘后加
inline void f(ll p,ll l,ll r,ll add,ll mul)
{
    // 值 = 值 * 父乘 + 父加 * 长度
    ans[p] = (ans[p] * mul + add * (r - l + 1)) % MOD;
    // 乘法标记 = 原乘法标记 * 父乘
    mul_tag[p] = (mul_tag[p] * mul) % MOD;
    // 加法标记 = 原加法标记 * 父乘 + 父加
    add_tag[p] = (add_tag[p] * mul + add) % MOD;
}
//向下传递tag
inline void push_down(ll p,ll l,ll r)
{
    ll mid = l + r >> 1;
    f(ls(p), l, mid, add_tag[p], mul_tag[p]);
    f(rs(p), mid + 1, r, add_tag[p], mul_tag[p]);
    //处理完后初始化
    mul_tag[p] = 1;
    add_tag[p] = 0;
}
//数值变化：当前区间和ans显然要乘以k。
//乘法标记变化：原有的mul也要乘以k。
//加法标记变化：关键点！ 原有的add也要乘以k。原因：(Val * mul + add) * k = Val * (mul * k) + (add * k)。你看，加法标记也被放大了。
// 操作1: 区间乘法
inline void update_mul(ll nl,ll nr,ll l,ll r,ll p,ll k)
{
    if(nl <= l && nr >= r)
    {
        ans[p] = (ans[p] * k) % MOD;
        mul_tag[p] = (mul_tag[p] * k) % MOD;
        add_tag[p] = (add_tag[p] * k) % MOD;// 加法标记也要乘 k
        return;
    }
    //没return说明没有完全覆盖，要到子节点，所以往下传
    push_down(p, l, r);
    ll mid = l + r >> 1;
    if (nl <= mid)
        update_mul(nl, nr, l, mid, ls(p), k);
    if(nr >= mid + 1)
        update_mul(nl, nr, mid + 1, r, rs(p), k);
    //处理完子节点更新父节点
    push_up(p);
}
// 操作2: 区间加法
inline void update_add(ll nl,ll nr,ll l,ll r,ll p,ll k)
{
    if(nl <= l && nr >= r)
    {
        ans[p] = (ans[p] + k * (r - l + 1)) % MOD;
        add_tag[p] = (add_tag[p] + k) % MOD;//加法只用更新add，不用处理mul的tag
        return;
    }
    //后续处理同上
    push_down(p, l, r);
    ll mid = l + r >> 1;
    if(nl <= mid)
        update_add(nl, nr, l, mid, ls(p), k);
    if(nr >= mid + 1)
        update_add(nl, nr, mid + 1, r, rs(p), k);
    push_up(p);
}
//询问
ll query(ll q_x,ll q_y,ll l,ll r,ll p)
{
    ll res = 0;
    if(q_x <= l && q_y >= r)
        return ans[p];
    //没return要递归到子节点去了，所以想下更新
    push_down(p, l, r);
    ll mid = l + r >> 1;
    if(q_x <= mid)
        res = (res + query(q_x, q_y, l, mid, ls(p))) % MOD;
    if(q_y >= mid + 1)
        res = (res + query(q_x, q_y, mid + 1, r, rs(p))) % MOD;
    return res;
}

void scan()
{
    cin >> n >> q >> MOD;
    for (ll i = 1; i <= n;i++)
        cin >> a[i];
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    scan();
    ///别忘了建树
    build(1, 1, n);
    int op;
    ll x, y, k;
    while(cin >> op)
    {
        if(op == 1)
        {
            cin >> x >> y >> k;
            update_mul(x, y, 1, n, 1, k);
        }
        else if(op == 2)
        {
            cin >> x >> y >> k;
            update_add(x, y, 1, n, 1, k);
        }
        else if(op == 3)
        {
            cin >> x >> y;
            cout << query(x, y, 1, n, 1) << "\n";
        }
    }
    return 0;
}