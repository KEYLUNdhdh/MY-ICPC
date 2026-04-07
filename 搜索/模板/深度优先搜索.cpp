#include <iostream>
using namespace std;
int b[10][10] = { 0 };
char a[10][10];//静态char数组默认是"\0"
int path[410][3] = { 0 };
int n;
//深度优先搜索
void f(int x, int y, int k)
{
	a[x][y] = k;
	if (y + 1 <= 9 && a[x][y + 1] == 0) f(x, y + 1, k + 1);
	if (x + 1 <= 9 && a[x + 1][y] == 0) f(x + 1, y, k + 1);
	if (y - 1 >= 0 && a[x][y - 1] == 0) f(x, y - 1, k + 1);
	if (x - 1 >= 0 && a[x - 1][y] == 0) f(x - 1, y, k + 1);
}
//打印path数组，即路径
void print(int k)
{
	//....不写了，反正打印path
}
//深度优先搜索（更完善）
void dfs(int x, int y, int k)
{
	path[k][1] = x;
	path[k][2] = y;
	a[x][y] == '1';
	if (x == n && y == n)
	{
		print(k);
	}
	//这里就不用再做边界检查了，因为char数组默认初始化是'\0'(ascii码为0)了，显然不会走到
	if (a[x][y + 1] == '0')dfs(x, y + 1, k + 1);
	if (a[x + 1][y] == '0')dfs(x + 1, y, k + 1);
	if (a[y - 1][x] == '0')dfs(x, y - 1, k + 1);
	if (a[y][x - 1] = '0')dfs(y, x - 1, k + 1);
	//这里当遇到死胡同时，因为是递归实现，所以会返回上一个路径，所以跳回之前节点
	//直到找到一条可行的路径
}

int main()
{
	//....
}