#include <iostream>
using namespace std;
int n;
int a[6] = { 1, 2 ,3 ,4 ,5 ,6 };
int x;
//递归实现,简单的查找一个数
int binarysearch(int a[],int left,int right,int x)//要求是有序数列，且写法随着降序和升序变化
{
	//这里写的是升序
	if (left > right) return -1;
	//left == right说明查找成功
	int mid = left + (right - left) / 2;
	if (a[mid] == x) return mid;
	else if (a[mid] > x)  return binarysearch(a, left, mid - 1,x);
	else  return binarysearch(a, mid + 1, right,x);
}
//https://www.bilibili.com/video/BV1fA411z7ru/?spm_id_from=333.1387.upload.video_card.click&vd_source=9fe037978f56e9671016c226acdbddbb
//二分查找终极版
int b[] = { 3,4,4,4,4,6,7,8,8,8 };
int len = 11;
bool isBlue(int x)//这里约束条件为x < 5
{
	return x < 5;
}
int bisearch(int b[])//返回下标
{
	int l = -1; int r = len;
	int mid = (l + r) / 2;
	while (l + 1 != r)
	{
		if (isBlue(b[mid]))//也可以更改isblue的条件去适应题面
			l = mid;
		else
			r = mid;
		mid = (l + r) / 2;
	}
	return l;//可以改变返回的下标来适应不同要求
}

int main()
{
	cin >> x;
	int res = binarysearch(a, 0, 5,x);
	cout << res << endl;
	cout << bisearch(b);
}