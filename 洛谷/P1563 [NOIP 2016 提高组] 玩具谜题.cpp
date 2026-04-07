#include <iostream>
#include <string>
using namespace std;
int face[100000] = { 0 };
string name[100000] = {" "};
//face 0 圈内 1 圈外
//映射到数组name 0圈内 右边 就+ 左边 就 - --- -- --1圈外 左边 + 右边 -
int main()
{
	int n, m; cin >> n >> m;
	for (int i = 0; i < n; ++i)
	{
		cin >> face[i] >> name[i];
	}
	int i = 0;
	int temp;
	while (m--)
	{
		int dir, step; cin >> dir >> step;
		if (face[i] == 0)//圈内
		{
			if (dir == 0)//左边
			{
				temp = i - step;
				if (temp < 0) temp += n;
				i = temp;
			}
			if (dir == 1)//右边
			{
				temp = i + step;
				if (temp >= n) temp -= n;
				i = temp;
			}
		}
		else//圈外
		{
			if (dir == 0)//左边
			{
				temp = i + step;
				if (temp >= n) temp -= n;
				i = temp;
			}
			if (dir == 1)//右边
			{
				temp = i - step;
				if (temp < 0) temp += n;
				i = temp;
			}
		}
	}
	cout << name[i];
	return 0;
}