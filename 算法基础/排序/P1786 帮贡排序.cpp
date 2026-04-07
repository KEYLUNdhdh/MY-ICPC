#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define bz "BangZhu"
#define fbz "FuBangZhu"
#define hf "HuFa"
#define zl "ZhangLao"
#define tz "TangZhu"
#define jy "JingYing"
#define bzo "BangZhong"
using namespace std;

class person
{
public:
	string name;
	string o_pos;
	int pos_level;
	int gong;
	int level;
	int cin_id;
};
bool cop1(person p, person q)
{
	if (p.gong > q.gong)
	{
		return true;
	}
	else if (p.gong == q.gong && p.cin_id < q.cin_id)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool cop2(person p, person q)
{
	if (p.pos_level < q.pos_level) return true;
	else if (p.pos_level == q.pos_level && p.level > q.level) return true;
	else if (p.pos_level == q.pos_level && p.level == q.level && p.cin_id < q.cin_id) return true;
	else return false;
}
int main()
{
	ios::sync_with_stdio(0);
	vector<person> still;
	vector<person> dp;
	int n; cin >> n;
	for (int i = 1; i <= n; i++)
	{
		person temp;
		cin >> temp.name >> temp.o_pos >> temp.gong >> temp.level;
		temp.cin_id = i;
		if (temp.o_pos == bz) temp.pos_level = 1;
		if (temp.o_pos == fbz) temp.pos_level = 2;
		if (temp.o_pos == hf) temp.pos_level = 3;
		if (temp.o_pos == zl) temp.pos_level = 4;
		if (temp.o_pos == tz) temp.pos_level = 5;
		if (temp.o_pos == jy) temp.pos_level = 6;
		if (temp.o_pos == bzo) temp.pos_level = 7;
		if (temp.o_pos == bz || temp.o_pos == fbz) still.push_back(temp);
		else dp.push_back(temp);
	}
	sort(dp.begin(), dp.end(), cop1);
	for (int i = 0; i < n - 3; ++i)
	{
		if (i == 0 || i == 1)
		{
			dp[i].o_pos = hf;
			dp[i].pos_level = 3;
		}
		 else if (i >= 2 && i <= 5)
		{
			dp[i].o_pos = zl;
			dp[i].pos_level = 4;
		}
		 else if (i >= 6 && i <= 12)
		{
			dp[i].o_pos = tz;
			dp[i].pos_level = 5;
		}
		 else if (i >= 13 && i <= 37)
		{
			dp[i].o_pos = jy;
			dp[i].pos_level = 6;
		}
		else
		{
			dp[i].o_pos = bzo;
			dp[i].pos_level = 7;
		}
	}
	for (auto i = still.begin(); i != still.end(); i++)
	{
		dp.push_back(*i);
	}
	sort(dp.begin(), dp.end(), cop2);
	for (auto it = dp.begin(); it != dp.end(); it++)
	{
		cout << it->name << " " << it->o_pos << " " << it->level << "\n";
	}
	return 0;
}