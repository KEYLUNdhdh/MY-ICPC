#include <iostream>
#include <vector>
using namespace std;
//介绍nth_element:用于将容器中第 n 小的元素放置到指定位置，并确保该位置左侧所有元素均小于等于它，
// 右侧所有元素均大于等于它（但左右两侧元素不一定完全有序）。
#include <algorithm>  // 必须包含的头文件

// 基础版：按升序划分，找第 k 小元素（k = pos - first）
//nth_element(开始迭代器, 目标位置迭代器, 结束迭代器);
//例如,对于vector《int》容器v
// 执行nth_element(v.begin(), v.begin() + 2, v.end());
//可以保证v[2]上的数字一定是第3小的数,左边元素一定比他小，右边元素一定比它大，但不是有序的

// 进阶版：自定义比较规则（如降序划分，找第 k 大元素）
//nth_element(开始迭代器, 目标位置迭代器, 结束迭代器, 比较函数);//这里就可以自定义比较函数了

//本题可以使用分治算法。分治，顾名思义就是“分而治之”，也就是把一个大问题分解成规模更小但本质相同的问题，再用同样的方法解决，再把小问题的解合并，就是大问题的解。
//这一题，我们可以随便选择一个数，并将数组分为三部分：比它小的数，这个数本身，和比它大的数。然后再判断第 k 小的数位于哪个部分，再在这个部分中继续用同样的方法查找，直到得出答案为止。平均时间复杂度可以达到 O(n)。
//注意最小的数是第 0 小，所以分治之前 k 要加一。且数据范围比较大，需要快速读入输出。
//快速选择算法,用手打

int quickselect(vector<int>& a,int left,int right,int k)
{
	if (left >= right) return a[left];
	//选择基准值，这里选择最右侧的元素
	int pivot = a[right];
	int i = left;
	for (int j = left; j < right; ++j)//这里小于基准值的都在左边，大于的都在右边，但不是有序的
	{
		if (a[j] < pivot)
		{
			swap(a[i], a[j]);
			i++;
		}
	}
	swap(a[i], a[right]);//双指针遍历，将基准值放到正确位置。即基准值为第p大，就放到p - 1索引上
	//下面判断想要找的第k大的位置是不是此时swap后i索引的位置（即pivot）
	if (k == i) return a[i];
	//如果不是，就进行递归操作.
	if (k > i) return quickselect(a, i + 1, right, k);
	else return quickselect(a, left, i - 1, k);
}

int main()
{
	ios::sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector<int> a(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	cout << quickselect(a, 0, n - 1, k);
	return 0;
}