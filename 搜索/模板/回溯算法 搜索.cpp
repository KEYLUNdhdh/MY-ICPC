#include <iostream>
using namespace std;
int path[400][3] = { 0 };
int dx[5] = { 0,0,1,0,-1 };
int dy[5] = { 0,1,0,-1,0 };//这里dx，dy直接记录方向，方便书写
bool mark[6][6];//静态默认为false，用于回溯法，创建迷宫
int n = 0;
int cnt = 0;//记录路径条数

void print(int k)
{
	//显示第几条路径
	cnt++;
	cout << cnt << " :";
	//打印path路径
	for (int i = 1; i < k; i++)
	{
		cout << path[i][1] << "," << path[i][2] << "-->";
	}
	cout << path[k][1] << "," << path[k][2] << endl;
}
//回溯算法，深度优先搜索进阶,即找出所有可能的路径
void dfs(int x, int y, int k)//k为path数组中的行
{
	//同上
	path[k][1] = x;
	path[k][2] = y;
	if (x == n && y == n)
	{
		print(k);
		return;//这里return代表一个路径找到了，此时函数结束并返回上一个节点
	}
	//这里用i尝试四个方向
	for (int i = 1; i <= 4; i++)
	{
		int tx = x + dx[i];
		int ty = y + dy[i];
		if (mark[tx][ty] == false && tx >= 1 && tx <= n && ty >= 1 && ty <= n)
		{
			mark[tx][ty] = true;//标记为走过了
			dfs(tx, ty, k + 1);//当这个函数结束了说明一个路径找完了
			//下面开始找另一个路线，并作初始化处理
			mark[tx][ty] = false;//跳回去，并标记为未走过
			path[k + 1][1] = 0;
			path[k + 1][2] = 0;//均为初始化

		}
	}
}
int main()
{
	mark[1][1] = true; //还要设置mark[1][1] = true;
	cin >> n;//迷宫大小
	dfs(1, 1, 1);//开始搜索
}