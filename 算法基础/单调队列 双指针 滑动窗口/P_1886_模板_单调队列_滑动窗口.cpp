#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    deque<int> maxres, minres;
    deque<int> maxre, minre;
    vector<int> a(n);
    for (int i = 0; i < n;i++)
        cin >> a[i];
    for (int i = 0; i < n;i++)
    {
        while(!maxre.empty() && a[maxre.back()] <= a[i])
            maxre.pop_back();
        maxre.push_back(i);
        while(!minre.empty() && a[minre.back()] >= a[i])
            minre.pop_back();
        minre.push_back(i);
        
        while(i >= k && maxre.front() <= i - k)
            maxre.pop_front();
        while(i >= k && minre.front() <= i - k)
            minre.pop_front();
        if(i >= k - 1)
        {
            maxres.push_back(a[maxre.front()]);
            minres.push_back(a[minre.front()]);
        }
    }
    for(auto i : minres)
        cout << i << " ";
    cout << "\n";
    for(auto i : maxres)
        cout << i << " ";
    return 0;
}