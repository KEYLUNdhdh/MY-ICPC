#include <iostream>
#include <map>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	char var = 'A';
	map<char, int> m;
	for (int i = 0; i < 26; ++i)
	{
		m.insert(make_pair(var, 0));
		var++;
	}
	string temp;
	int max = 0;
	while (cin >> temp)
	{
		for (int i = 0; i < temp.size(); i++)
		{
			if (temp[i] >= 'A' && temp[i] <= 'Z')
			{
				m[temp[i]]++;
				if (m[temp[i]] > max) max = m[temp[i]];
			}
		}
	}
	max++;
	while (--max)
	{
		for (auto it = m.begin(); it != m.end(); it++)
		{
			if (it->second == max)
			{
				cout << "*";
				it->second--;
			}
			else
			{
				cout << " ";
			}
			cout << " ";
		}
		cout << "\n";
	}
	for (auto it = m.begin(); it != m.end(); it++)
	{
		cout << it->first << " ";
	}
	return 0;
}