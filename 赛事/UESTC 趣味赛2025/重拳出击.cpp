#include<iostream>
using namespace std;

int find(string s)
{
    int cnt = 0;
    int pos = s.find("nailong");
    int len = 7;
    while (pos != -1)
    {
        cnt++;
        s = s.substr(pos + 7);
        pos = s.find("nailong");
    }
    return cnt * 12;
}

int main()
{
    int maxt = 720;
    int t;
    cin >> t;
    string judge;
    while (t--)
    {
        cin >> judge;
       if (find(judge) < 720)
           cout << find(judge) << "\n";
           else
               cout << "Overflow!\n";
    }
    return 0;
}