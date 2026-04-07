#include <bits/stdc++.h>
using namespace std;
void solve(string in,string post)
{
    if(in.empty() || post.empty())
        return;
    char root = post.back();
    int pos = in.find(root);

    string lin = in.substr(0, pos);
    string rin = in.substr(pos + 1);

    int len = lin.length();
    string lpost = post.substr(0,len);
    string rpost = post.substr(len);
    rpost.pop_back();
    cout << root;
    solve(lin, lpost);
    solve(rin, rpost);
}
int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    solve(s1, s2);

    return 0;
}