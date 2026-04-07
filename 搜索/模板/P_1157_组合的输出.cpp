#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n, r;
vector<int> vec;
//index 已经选了几个 step 遍历到那个数 vec存储选了的数
void dfs(int index,int step)
{
    if (index == r)
    {
        for (auto& i : vec)
        {
            cout << setw(3) << i;
        }
        cout << "\n";
        return;
    }
    //如果step超限，经过上面的一个if说明index没到，直接不输出r直接eturn
    if (step > n)
    {
        return;
    }
    //选
    vec.push_back(step);
    //这里dfs传入的是形参，不影响实际的vec
    dfs(index + 1, step + 1);
    //不选
    vec.pop_back();
    dfs(index, step + 1);
}

int main()
{
    cin >> n >> r;
    vector<int> vec;
    dfs(0, 1);
}