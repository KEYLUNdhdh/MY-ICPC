#include <iostream>
using namespace std;
//dp一般都是倒推或者从小到大
//金字塔形查找最大可能的和
//https://www.bilibili.com/video/BV1aTJmzQELD/?spm_id_from=333.1387.upload.video_card.click&vd_source=9fe037978f56e9671016c226acdbddbb
int t[110][110] = { 0 };//存储金字塔
int dp[110][110] = { 0 };//存储每个节点对应的子金字塔的最大可能的和
int n;;
void d()
{
	//初始化dp数组（利用金字塔最底部的数据）
	for (int i = 1; i <= n; i++)
	{
		dp[n][i] = t[n][i];
	}
	//倒着循环，逐级往上dp
	for (int i = n - 1; i >= 1; i--)
	{
		for (int j = 1; j <= i; j++)
		{
			dp[i][j] = t[i][j] + max(dp[i + 1][j], dp[i + 1][j + 1]);
		}
	}
}
int main()
{
	//读入
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			cin >> t[i][j];
		}
	}
	d();
	cout << dp[1][1];
}