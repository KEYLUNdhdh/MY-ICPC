#include <iostream>
using namespace std;

int main()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int sum = 0;
    sum += a + b + c + d;
    int aaa[4] = {a, b, c, d};
    int i = 1;
    int flag = 0;
    while (i < (1 << 4))
    {
        int tp = 0;
        for (int k = 0; k < 4;k++)
        {
            if(i & (1 << k))
            {
                tp += aaa[k];
            }
        }
        if (2 * tp == sum)
        {
            flag = 1;
            break;
        }
        i++;
    }
    if(flag)
        cout << "YES";
    else
        cout << "NO";
}