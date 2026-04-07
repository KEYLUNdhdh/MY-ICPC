#include <bits/stdc++.h>
using namespace std;
int a[] = {2, 3,4, 5, 7,9, 11, 13,16, 17, 19, 23,25, 29, 31, 37, 41, 43, 47,49, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
int main()
{
    string ans;
    int cnt = 0;
    for (int i = 0; i < 20;i++)
    {
        cout << a[i] << endl;
        cout.flush();
        cin >> ans;
        if (ans == "yes")
        {
            cnt++;
        }
        if (cnt > 1)
        {
            cout << "composite";
            exit(0);
        }
    }
    if (cnt <= 1)
        cout << "prime";
    else
        cout << "composite";
}