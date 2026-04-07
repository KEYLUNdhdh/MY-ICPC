#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>
using namespace std;

class stu
{
public:
	string name;
	int ch;
	int ma;
	int en;
	int zf;
	int id;
};
int main()
{
	ios::sync_with_stdio(0);
	vector<stu> overall;
	vector<pair<vector<stu>::iterator, vector<stu>::iterator>> res;
	overall.reserve(1000);
	int n; cin >> n;
	for (int i = 1; i <=n; ++i)
	{
		stu tp;
		cin >> tp.name >> tp.ch >> tp.ma >> tp.en;
		tp.zf = tp.ch + tp.ma + tp.en;
		tp.id = i;
		overall.push_back(tp);
	}
	for (auto i = overall.begin(); i != overall.end(); i++)
	{
		for (auto j = i + 1; j != overall.end(); ++j)
		{
			if (abs(j->ch - i->ch) <= 5 && abs(j->en - i->en) <= 5 &&
				abs(j->ma - i->ma) <= 5 && abs(j->zf - i->zf) <= 10)
			{
				res.push_back(make_pair(i, j));
			}
		}
	}
	for (auto it = res.begin(); it != res.end(); it++)
	{
		cout << it->first->name << " " << it->second->name << "\n";
	}
	return 0;
}