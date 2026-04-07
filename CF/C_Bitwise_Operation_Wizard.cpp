#include <bits/stdc++.h>
using namespace std;
char x;
char query(int a,int b,int c,int d)
{
    cout << "? " << a << " " << b << " " << c << " " << d << endl;
    cout.flush();
    cin >> x;
    return x;
}
int main()
{
    int t;
    cin >> t;
    int n;
    vector<int> vec;
    while(t--)
    {
        cin >> n;
        int maxx = 0;
        for (int i = 0; i < n;i++)
        {
            if(query(maxx, maxx, i, i)  == '<')
            {
                maxx = i;
            }
        }
        int mx = 0;
        vec.push_back(0);
        for (int i = 1; i < n; i++)
        {
            if(query(mx,maxx,i,maxx) == '<')
            {
                mx = i;
                vec.clear();
                vec.push_back(mx);
            }
            else if(x == '=')
                vec.push_back(i);
        }
        int minn = vec[0];
        for (int i = 1; i < vec.size();i++)
        {
            if(query(minn,minn,vec[i],vec[i]) == '>')
            {
                minn = vec[i];
            }
        }
        cout << "! " << maxx << " " << minn << endl;
        cout.flush();
        vec.clear();
    }
}