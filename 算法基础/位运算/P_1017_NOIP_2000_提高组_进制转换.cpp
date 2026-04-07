//10进制转成n进制的做法：
//对这个数不断除以n，将余数一一存储，最后倒序输出。
//负进制转换
//n = q * R + m//其中 n 是被除数，q 是商，R 是基数，m 是余数。
//问题所在：当 R < 0 且 n 为负数时，C++ 算出来的 m 可能是负数。例如：-15 \ -2，C++ 会给你：商 q = 7，余数 m = -1。但我们要的数码必须在 [0, 1] 之间，-1 显然不合法。
//解决方案：我们要强制让余数落在 [0, |R|-1] 之间。
//n = (q+1) * R + (m-R)//这个公式完美解决
#include <bits/stdc++.h>
using namespace std;
char c[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M'};
int main()
{
    int n, base;
    cin >> n >> base;
    int on = n;
    vector<char> ans;
    while(n != 0)
    {
        int temp = n % base;
        if(temp < 0)
        {
            int mr = n % base - base;
            ans.push_back(c[mr]);
            n = n / base + 1;
        }
        else
        {
            int m = n % base;
            ans.push_back(c[m]);
            n = n / base;
        }
    }
    cout << on << "=";
    for (auto it = ans.rbegin(); it != ans.rend();it++)
    {
        cout << *it;
    }
    cout << "(base" << base << ")";
}