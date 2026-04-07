#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype>
using namespace std;

int main()
{
	vector<int> st;
	string a[] = { "zero","one","two","three","four","five","six","seven","eight","nine","ten","eleven"
	,"twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen","twenty",
	"a","both","another","first","second","third" };
	int d[] = { 0,1,4,9,16,25,36,49,64,81,0,21,44,69,96,25,56,89,24,61,0,1,2,1,1,4,9 };
	string temp;
	int tp;
	while (cin >> temp)
	{
		temp[0] = tolower(temp[0]);
		if (temp[temp.size() - 1] == '.')
		{
			temp = temp.substr(0, temp.size() - 1);
		}
		tp = -1;
		for (int i = 0; i < 27; ++i)
		{
			if (temp == a[i])
			{
				tp = i;
				break;
			}
		}
		if (tp != -1)
		st.push_back(d[tp]);
	}
	sort(st.begin(), st.end());
	int total = 0;
	for (int i = 0; i < st.size(); i++)
	{
		total = total * 100 + st[i];
	}
	cout << total;

}