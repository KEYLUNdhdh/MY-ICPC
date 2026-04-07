#include <bits/stdc++.h>
using namespace std;
struct node{
    char val;
    char l, r;
} tree[200];
void pre(char id)
{
    cout << id;
    if (tree[id].l != '*')
        pre(tree[id].l);
    if(tree[id].r != '*')
        pre(tree[id].r);

    return;
}
int main()
{
    int n;
    cin >> n;
    char ini;
    for (int i = 1; i <= n;i++)
    {

        char tp;
        cin >> tp;
        if(i == 1)
        {
            ini = tp;
        }
        cin >> tree[tp].l >> tree[tp].r;
    }
    pre(ini);
}