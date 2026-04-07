#include <iostream>
#include <string>
using namespace  std;
int y, z;
char m;

void wayout()
{
	char temp;
	cin >> temp;
	if (temp >= 'a' && temp <= 'c')
	{
		m = temp;
		cin >> y >> z;
	}
	else
	{
		cin.unget();
		cin >>y >>z;
	}
	if (m == 'a')
	{
		string s = to_string(y) + "+" + to_string(z) +
			"=" + to_string(y + z);
		cout << s << "\n";
		cout << s.size();
	}
	if (m == 'b')
	{
		string s = to_string(y) + "-" + to_string(z) +
			"=" + to_string(y - z);
		cout << s << "\n";
		cout << s.size();
	}
	if (m == 'c')
	{
		string s = to_string(y) + "*" + to_string(z) +
			"=" + to_string(y * z);
		cout << s << "\n";
		cout << s.size() << "\n";
	}
}
int main()
{
	int t;
	cin >> t;
	while (t--) wayout();
}