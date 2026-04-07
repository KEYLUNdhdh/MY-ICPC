#include <string>
#include <iostream>
using namespace std;
int d[1000005] = {0};
int sum[1000005] = {0};
int main()
{
    string s;
    cin >> s;
    int cnt = 0;
    int index = 0;
    for (int i = 0; i < s.size() - 1;i++)
    {
        if(s[i] != s[i + 1])
        {
            d[index] = s[i] - '0';
            sum[index] = cnt + 1;
            cnt = 0;
            index++;
        }
        else
        {
            cnt++;
        }
    }
    d[index] = s[s.size() - 1] - '0';
    sum[index] = cnt + 1;
    index++;
    // for (int i = 0; i < index;i++)
    // {
    //     cout << d[i] << " ";
    // }
    // cout << "\n";
    // for (int i = 0; i < index;i++)
    // {
    //     cout << sum[i] << " ";
    // }
    // cout << "\n";
    if (index <= 1)
    {
        cout << 0;
        return 0;
    }
    int su = 0;
    for (int i = 1; i < index;i++)
    {
        if (d[i] == d[i - 1] + 1)
        {
            su += min(sum[i], sum[i - 1]);
        }
    }
    cout << su;
}