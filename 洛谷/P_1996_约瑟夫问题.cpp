#include <bits/stdc++.h>
using namespace std;
typedef struct node{
    int val, r, l;
} node;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<node> vec(n);
    int cnt = m - 1;
    for (int i = 0; i < n;i ++)
    {
        if(i == 0)
        {
            vec[i].val = i + 1;
            vec[i].l = n - 1;
            vec[i].r = 1;
        }
        else if(i == n - 1)
        {
            vec[i].val = i + 1;
            vec[i].l = i - 1;
            vec[i].r = 0;
        }
        else
        {
            vec[i].val = i + 1;
            vec[i].l = i - 1;
            vec[i].r = i + 1;
        }
    }
    int pos = 0;
    int tp = m;
    int count = 0;
    while(1)
    {
        if(count == n)
        {
            break;
        }
        cnt--;
        pos = vec[pos].r;
        
        if(cnt == 0)
        {
            cout << vec[pos].val << " ";
            cnt = m;
            vec[vec[pos].l].r = vec[pos].r;
            vec[vec[pos].r].l = vec[pos].l;
            count++;
        }
    }
}