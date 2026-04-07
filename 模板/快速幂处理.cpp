 #include <iostream>
using namespace std;
#define int long long
//输出一行一个字符串 a^b mod p=s，其中 a,b,p 分别为题目给定的值， s 为运算结果。
//输入2 10  9  输出2^10 mod 9=7
//幂取模运算
int solve1(int a,int b,int p)
{
	a = a % p;
	int res = 1;
	while (b != 0)
	{
		if (b & 1)
		{
			res = (res * a) % p;
		}
		a = (a * a) % p;
		b >>= 1;
	}
	return res;
}
//快速幂的乘法
int solve2(int a, int b)
{
	int res = 1;
	while (b != 0)
	{
		if (b & 1) res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
}
signed main()
{
	int a, b, p; cin >> a >> b >> p;
	int re = solve1(a, b, p);
	cout << a << "^" << b << " mod " << p << "=" << re << endl;
	int re2 = solve2(a, b);
	cout << re2;
}