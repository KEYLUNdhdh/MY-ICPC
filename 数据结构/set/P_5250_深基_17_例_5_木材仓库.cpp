#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    set<int> st;
    int m,op,len;
    cin >> m;
    while(m--)
    {
        cin >> op >> len;
        if(op == 1)
        {
            // set 的 insert 自带判重和排序，复杂度 O(log N)
            //set 里面的 insert(x) 函数其实是有返回值的，会返回一个这样的奇怪的东西：pair<set<int>::iterator,bool>。其中的bool返回的就是是否插入成功，迭代器就是插入的地点
            if(!st.insert(len).second)
                cout << "Already Exist\n";
        }
        else
        {
            if(st.empty())
            {
                cout << "Empty\n";
                continue;
            }
            auto it = lower_bound(st.begin(),st.end(),len);
            if(it == st.end())
            {
                it--;
                cout << *it << "\n";
                // lower_bound 在 set 中是 O(log N)
                st.erase(it);
            }
            else if(it == st.begin())
            {
                cout << *it << "\n";
                st.erase(it);
            }
            else
            {
                auto ne = it--;
                if(len - *it > *ne - len)
                {
                    cout << *ne << "\n";
                    st.erase(ne);
                }
                else
                {
                    cout << *it << "\n";
                    st.erase(it);
                }
            }
        }
    }
}