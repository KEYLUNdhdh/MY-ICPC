//我们考虑异或的两个小小的性质：

//k 个相同的数的异或和，当 k 为奇数时，结果是这个数本身，否则结果是 0。
//任何数与 0 的异或值是它本身。
//然后注意到题目。题目需要求 n 个数中出现奇数次的那个数，且保证这个数存在且只有一个。于是我们根据上面两个性质得出，答案就是这 n 个数的异或和。
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int num = 0;
    char ch;
    ch = getchar();
    while(ch < '0' || ch > '9')
    {
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        num = num * 10 + ch - '0';
        ch = getchar();
    }
    return num;
}
int main()
{
    int n;
    cin >> n;
    int ans = 0,tp;
    while(n--)
    {
        tp = read();
        ans ^= tp;
    }
    cout << ans;
}