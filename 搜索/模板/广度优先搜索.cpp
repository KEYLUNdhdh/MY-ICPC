#include <iostream>
using namespace std;
//找出迷宫的最短路径
int a[110][110] = { 0 };//表示迷宫
int p[10010][4] = { 0 };//按每个格子被赋的值存储坐标和每个格子的父格子
int n, m;//迷宫为n * m
int head = 1;//队头
int tail = 1;//队尾
int dx[5] = {0,0,1,0,-1};
int dy[5] = {0,1,0,-1,0};
int tx, ty;
int k = 1;//为迷宫每个格子赋值
//当head大于tail时探索结束

void print()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}
void print2(int tail)//递归打印最短路径，此时tail指向迷宫终点
{
	if (tail != 0)
	{
		print2(p[tail][3]);
	}
	if (tail == 0) return;
	cout << p[tail][1] << "," << p[tail][2];
	if (tail!= k) cout << " --> ";
}
int main()
{
	cin >> n >> m;
	a[1][1] = 1;//为第一个格子赋值
	p[1][1] = 1;//坐标
	p[1][2] = 1;//坐标
	p[1][3] = 0;//没有父格子，初始化为0
	while (head <= tail)
	{
		for (int i = 1; i <= 4; i++)
		{
			tx = p[head][1] + dx[i];
			ty = p[head][2] + dy[i];
			if (tx >= 1 && tx <= n && ty >= 1 && ty <= n && a[tx][ty] == 0)
			{
				tail++;
				p[tail][1] = tx;
				p[tail][2] = ty;
				p[tail][3] = head;
				a[tx][ty] = k + 1;
				k++;
				if (tx == n && ty == m)
				{
					print2(tail);
				}
			}
		}
		head++;//四个可能方向找完后head移动到下一个坐标继续找
	}
	//print();
}