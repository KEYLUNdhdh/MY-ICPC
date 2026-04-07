#include <iostream>
#include <string>
using namespace std;
#define int long long
int m, n;
void reverse2(string s1, string s2 = "0")
{
	 m = stoi(s1);
	 n = stoi(s2);

	int temp = 0;
	while (m != 0)
	{
		temp = temp * 10 + m % 10;
		m /= 10;
	}
	m = temp;
	temp = 0;
	while (n != 0)
	{
		temp = temp * 10 + n % 10;
		n /= 10;
	}
	n = temp;
}

signed main()
{
	string s;
	cin >> s;
	if (s.find('.') != -1)
	{
		string a = s.substr(0, s.find('.'));
		string b = s.substr(s.find('.') + 1, s.size() - 1 - s.find('.'));
		reverse2(a, b);
		cout << m << "." << n;
		return 0;
	}
	if (s.find('/') != -1)
	{
		string a = s.substr(0, s.find('/'));
		string b = s.substr(s.find('/') + 1, s.size() - 1 - s.find('/'));
		reverse2(a, b);
		cout << m << "/" << n;
		return 0;
	}
	if (s.find('%') != -1)
	{
		string a = s.substr(0, s.find('%'));
		reverse2(a);
		cout << m << "%";
		return 0;
	}
	reverse2(s);
	cout << m;
	return 0;
}