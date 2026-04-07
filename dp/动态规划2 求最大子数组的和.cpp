#include <iostream>
using namespace std;
//求最大子数组的和
//https://www.bilibili.com/video/BV1bGHNzKEys/?spm_id_from=333.1387.upload.video_card.click&vd_source=9fe037978f56e9671016c226acdbddbb
int a[100010] = { 0 };
int dp[100010] = { 0 };
int n;

int main()
{
	int n; cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	dp[1] = a[1];//初始化
	int g_m = dp[1];//global_max存储全局最大子数组的和

	for (int i = 2; i <= n; i++)
	{
		dp[i] = max(dp[i - 1] + a[i], a[i]);
		g_m = max(dp[i], g_m);
	}
	cout << g_m;
}