#include <iostream>
using namespace std;
int eter = 0;
int main()
{
	string s;
	string m;
	int cnt = 0;
	int pos = 0;
	cin >> s;
	while (cin >> m)
	{
		if (s.size() != m.size())
		{
			pos += m.size() + 1;
			continue;
		}
		int flag = 0;
		int swap = 'A' - 'a';
		for (int i = 0; i < s.size(); ++i)
		{
			if (s[i] != m[i] && s[i] - swap != m[i] && s[i] + swap != m[i])
				flag = 1;
		}
		if (flag)
		{
			pos += m.size() + 1;
			continue;
		}
		if (cnt == 0) eter = pos;
		cnt++;
	}
	if (cnt == 0)
	{
		cout << "-1";
		return 0;
	}
	cout << cnt << " " << eter;
}