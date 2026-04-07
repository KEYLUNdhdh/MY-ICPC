#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;
int a[500005] = { 0 };
//由于测试用例数量较多（约 200000 个），若对每个数单独计算真约数和会导致效率过低，推荐使用埃拉托斯特尼筛法（Euler 筛的变种） 预处理所有 1~500000 的数的真约数和，具体步骤如下：
//
//初始化一个大小为 500001 的数组sum_div，用于存储每个数的真约数和，初始值均为 0；
//遍历从 2 到 500000 的每个数i，将i的所有倍数（从2i开始，步长为i）的sum_div值加上i（因为i是这些倍数的约数，且严格小于倍数）；
//预处理完成后，对于每个测试用例的数n，直接输出sum_div[n]即可（1 的sum_div值保持为 0，符合定义）。

void wayout(int n)
{
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; i * j <= n; j++)
		{
			a[i * j] += i;
		}
	}
}

signed main()
{
	int t; cin >> t;
	vector<int> vt;
	for (int i = 0; i < t; ++i)
	{
		int temp; cin >> temp;
		vt.push_back(temp);
	}
	vector<int> tp = vt;
	sort(vt.begin(), vt.end(), [](int i, int j) {return i > j; });
	int max = *(vt.begin());
	wayout(max);
	
	for (auto it = tp.begin(); it != tp.end(); it++)
	{
		cout << a[*it] -*it<< "\n";
	}
	return 0;
}