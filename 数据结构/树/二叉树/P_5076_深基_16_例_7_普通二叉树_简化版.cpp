// #include <bits/stdc++.h>
// #define int long long
// using namespace std;
// const int INF = 2147483647;
// const int MAXN = 1e5 + 5;
// int tree[MAXN][2];
// int val[MAXN];
// int dat[MAXN];
// int sizee[MAXN];
// int cnt[MAXN];
// int tot, root;

// int New(int v)
// {
//     val[++tot] = v;
//     dat[tot] = rand();
//     cnt[tot] = 1;
//     sizee[tot] = 1;

//     return tot;
// }

// void pushup(int id)
// {
//     sizee[id] = sizee[tree[id][0]] + cnt[id] + sizee[tree[id][1]];
// }

// void build()
// {
//     root = New(-INF);
//     tree[root][1] = New(INF);
//     pushup(root);
// }

// void Rotate(int &id,int d)
// {
//     int temp = tree[id][d ^ 1];
//     tree[id][d ^ 1] = tree[temp][d];
//     tree[temp][d] = id;
//     id = temp;
//     pushup(tree[id][d]);
//     pushup(id);
// }
// void insert(int &id,int v)
// {
//     if(!id)
//     {
//         id = New(v);
//         return;
//     }
//     else
//     {
//         if(val[id] == v)
//         {
//             cnt[id]++;
//         }
//         else
//         {
//             int d = val[id] > v ? 0 : 1;
//             insert(tree[id][d], v);
//             if(dat[id] < dat[tree[id][d]])
//             {
//                 Rotate(id, d ^ 1);
//             }
//         }
//         pushup(id);
//     }
// }

// int get_rank(int id,int v)
// {
//     if(!id)
//     {
//         return 1;
//     }
//     if(val[id] == v)
//     {
//         return sizee[tree[id][0]] + 1;
//     }
//     else if(v < val[id])
//         return get_rank(tree[id][0],v);
//     else
//         return sizee[tree[id][0]] + cnt[id] + get_rank(tree[id][1], v);
// }
// int get_val(int id,int rk)
// {
//     if(!id)
//         return INF;
//     if(rk <= sizee[tree[id][0]])
//     {
//         return get_val(tree[id][0], rk);
//     }
//     else if(rk <= sizee[tree[id][0]] + cnt[id])
//     {
//         return val[id];
//     }
//     else
//     {
//         return get_val(tree[id][1], rk - sizee[tree[id][0]] - cnt[id]);
//     }
// }
// int get_pre(int v)
// {
//     int id = root, pre;
//     while(id)
//     {
//         if(val[id] < v)
//         {
//             pre = val[id];
//             id = tree[id][1];
//         }
//         else
//         {
//             id = tree[id][0];
//         }
//     }
//     return pre;
// }

// int get_next(int v)
// {
//     int id = root, next;
//     while(id)
//     {
//         if(val[id] > v)
//         {
//             next = val[id];
//             id = tree[id][0];
//         }
//         else
//         {
//             id = tree[id][1];
//         }
//     }
//     return next;
// }
// signed main()
// {
//     ios::sync_with_stdio(0);
//     cin.tie(0);
//     int q;
//     cin >> q;
//     build();
//     int op, x;
//     while(q--)
//     {
//         cin >> op >> x;
//         if(op == 1)
//         {
//             cout << get_rank(root, x) - 1 << "\n";
//         }
//         else if (op == 2)
//         {
//             cout << get_val(root, x + 1) << "\n";
//         }
//         else if(op == 3)
//         {
//             cout << get_pre(x) << "\n";
//         }
//         else if(op == 4)
//         {
//             cout << get_next(x) << "\n";
//         }
//         else
//         {
//             insert(root, x);
//         }
//     }
// }

#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> vec;
    int q;
    cin >> q;
    int op, x;
    while(q--)
    {
        cin >> op >> x;
        if(op == 1)
        {
            // 查询 x 的排名
            // lower_bound 返回第一个 >= x 的迭代器
            // 减去 v.begin() 就是前面有多少个数，+1 即为排名
            cout << (lower_bound(vec.begin(), vec.end(), x) - vec.begin()) + 1 << "\n";

        }
        else if(op == 2)
        {
            // 查询排名为 x 的数
            // 下标从0开始，所以是 x-1
            cout << vec[x - 1] << "\n";
        }
        else if(op == 3)
        {
            // 求 x 的前驱 (小于 x 且最大)
            // lower_bound 找第一个 >= x 的位置
            auto it = lower_bound(vec.begin(), vec.end(), x);
            if(it != vec.begin())
            {
                cout << *(--it) << "\n";
            }
            else
            {
                cout << -2147483647 << "\n";
            }
        }
        else if(op == 4)
        {
            // 求 x 的后继 (大于 x 且最小)
            // upper_bound 找第一个 > x 的位置
            auto it = upper_bound(vec.begin(), vec.end(), x);
            if(it != vec.end())
            {
                cout << *(it) << "\n";
            }
            else
            {
                cout << 2147483647 << "\n";
            }
        }
        else
        {
            //insert是插入到当前迭代器位置，迭代器原先指向的值后移
            auto it = lower_bound(vec.begin(), vec.end(), x);
            vec.insert(it, x);
        }
    }
}