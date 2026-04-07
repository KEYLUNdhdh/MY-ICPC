#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
using namespace std;
#define m_size 15
int a[m_size] = { 1,8,3,4,2,5,7,6,9,10,12,11,14,13,15 };
vector<int> a_m = { 1,8,3,4,2,5,7,6,9,10,12,11,14,13,15 };
int temp[m_size] = { 0 };
//https://www.bilibili.com/video/BV18mXaY1EcS?spm_id_from=333.788.videopod.sections&vd_source=9fe037978f56e9671016c226acdbddbb&p=4
//所有演示的排序均为降序类型
void swap(int& a, int& b)
{

	int c = a;
	a = b;
	b = c;
}
void BuBlesort(int a[])//冒泡排序，相邻交换。
{
	for (int i = 0; i < m_size - 1; ++i)
		for (int j = 0; j < m_size - 1 - i; ++j)
		{
			if (a[j] < a[j + 1]) swap(a[j], a[j + 1]);
		}
}
void insert(int a[])//插入排序,切割成有序和无序的两个数组，无序的第一个和有序的最后一个
//比较，利用temp介导，逐步向前比较有序数组的值，最终找到对应位置
//稳定 // 降序
{
	//外层循环，遍历无序序列
	for (int i = 1; i < m_size; i++)
	{
		//拿出无序序列的第一个元素
		int temp = a[i];
		//设置内层循环的起始值 = 有序序列最后一个元素的位置
		int j = i - 1;
		while (j >= 0 && a[j] < temp)//a[j] 和 temp 的比较决定是升序还是降序
		{
			//有序数列数据后移
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = temp;
	}
}
void Selectsort(int a[])//选择排序,遍历，找到最大值的索引，与第一个值交换，完成降序排列
//
{
	int posmax = 0;
	for (int i = 0; i < m_size - 1; i++)
	{
		for (int j = i + 1; j < m_size; j++)
		{
			if (a[posmax] < a[j])
			{
				posmax = j;
			}
		}
		swap(a[i], a[posmax]);
	}
}
void Shellsort(int a[])//希尔排序，选择排序的进阶版本，更高效
//不稳定 // 降序
{
	for (int gap = m_size / 2; gap > 0; gap /= 2)
	{
		//外层循环，遍历无序序列
		for (int i = gap; i < m_size; i++)
		{
			int temp = a[i];//拿出无序序列第一个元素
			int j = i - gap;//拿出有序序列最后一个元素
			while (j >= 0 && a[j] < temp)
			{
				a[j + gap] = a[j];
				j -= gap;
			}
			a[j + gap] = temp;//填坑
		}
	}
}//实际上对每个要排序的子列只操作了一次插入排序

void quicksort(int a[], int left, int right)//快速排序//我去经典递归环节
{
	if (left >= right) return;
	int pivot = a[(left + right) / 2];//取出基准值
	int begin = left; int end = right;
	//和基准数进行比较
	while (begin <= end)
	{
		//头部元素和基准元素比较
		while (a[begin] > pivot && begin <= end)//条件不满足指针会停止
		{
			begin++;
		}
		while (a[end] < pivot && begin <= end)//条件不满足指针会停止
		{
			end--;
		}
		if (begin <= end)
		{
			swap(a[begin], a[end]);
			begin++;
			end--;
		}
	}
	quicksort(a, left, end);//左侧序列
	quicksort(a, begin, right);//右侧序列
}
//void quicksort(vector<int> a) 其实快速排序也支持封装好一个函数直接调用
void mergesort(int a[], int left, int right, int temp[])//归并排序//如果是其他数据结构要以引用的方式传入
{
	if (left >= right) return;
	//从中间位置对数组进行拆分
	int mid = left + (right - left) / 2;//防止整数越界 
	//与快速排序不同，先拆分再排序
	mergesort(a, left, mid, temp);
	mergesort(a, mid + 1, right, temp);
	//对两个（有序）子序列合并//***做双指针遍历***
	int i = left, j = mid + 1;
	int index = 0;//从头开始向temp写数据
	while (i <= mid && j <= right)//保证i,j不会越界
	{
		//做降序比较
		if (a[i] >= a[j])//多一个等号可以保证排序是稳定的
		{
			temp[index++] = a[i++];//同时更新index ，i或j做双指针遍历
		}
		else
		{
			temp[index++] = a[j++];
		}
	}
	//循环做完有一个分支数据被拿完了,开始排除
	while (i <= mid)//如果已经是mid就不做循环
	{
		temp[index++] = a[i++];
	}
	while (j <= right)//如果已经是right就不做循环
	{
		temp[index++] = a[j++];
	}
	//做值覆盖
	for (int k = 0; k < index; ++k)
	{
		a[left + k] = temp[k];//做一个映射，映射到a的对应位置
	}
}
//void mergesort(vector<int>& a)//做一个重载,不过不适用int a[]类型，得其他支持empty（）的容器
//{
//	if (a.empty())
//	{
//		return;
//	}
//	vector<int> temp;
//	mergesort(vector<int> a, 0, a.size() - 1, temp);
//}

//堆排序其实就是构建最大或最小堆，将数组中一个最大或最小的值移动到整个树的根节点
//之后让根节点的值与最后一个叶子节点的值交换，相当于末端此时变为有序了
//之后就是不断重复这个过程,对前面无序的树进行排序,直到整个树有序
void headadjust(vector<int>& a, int len, int parent)//parent是调整的树根节点的位置//堆排序//基于完全二叉树实现
//只调整根节点和它左右孩子的位置//len是子树的长度
{
	int maxIndex = parent;//根节点的位置
	int left = parent * 2 + 1;//左孩子的位置
	int right = parent * 2 + 2;//右孩子的位置
	//根节点和左孩子进行比较,找到左右孩子中更小的那个
	if (a[left] < a[maxIndex] && left < len)//防止越界
	{
		maxIndex = left;
	}
	//根节点和右孩子进行比较,找到左右孩子中更小的那个
	if (a[right] < a[maxIndex] && right < len)
	{
		maxIndex = right;
	}
	//判断根节点的值是不是最大的
	if (maxIndex != parent)
	{
		swap(a[parent], a[maxIndex]);//做值交换
		headadjust(a, len, maxIndex);//进一步调整子树的子树，保证满足最大堆或者最小堆条件
	}
}
void headsort(vector<int>& a)
{
	if (a.empty())
	{
		return;//如果是空数组直接返回
	}
	//如果不是空的，从最后一个非叶子节点开始进行调整
	//按照最大或最小堆的属性进行调整,一直往前到根节点
	for (int i = a.size() / 2 - 1; i >= 0; i--)//i的初始化其实就是求最后一个非叶子节点的公式
	{
		headadjust(a, a.size(), i);//完成对调整函数的调用
	}
	//当for循环走完了，我们就会得到一个最大或最小堆
	//交换根节点和最后一个叶子节点的值
	for (int i = a.size() - 1; i >= 1; i--)//i从最后一个子叶开始，然后不用取到根节点
	{
		swap(a[0], a[i]);//交换完就不是最大堆或最小堆了
		//继续进行调整，去掉i当前对应的叶子节点
		headadjust(a, i, 0);//继续进行调整，len这里要逐渐变小，并且parent是那个
		//大树对应的根节点，所以parent为0
	}
}
//基数排序//基于桶排序实现的
void radixsort(vector<int>& a)
{
	int max = *max_element(a.begin(), a.end());//借用迭代器返回最大值,但返回的是迭代器，所以需要解引用
	//计算位数
	int len = 0;
	while (max > 0)
	{
		max /= 10;
		len++;
	}
	//2.计算位数可以转换位string直接调用size进行处理
	//准备同对象，10个桶，代表0 到 9 这10个数字
	vector<vector<int>> bucket(10);
	//遍历数字位
	int mod = 10; int dev = 1;
	for (int i = 0; i < len; ++i, mod *= 10, dev *= 10)
	{
		//分桶
		for (int j = 0; j < a.size(); j++)
		{
			int num = a[j] % mod / dev;//取出数不同位数上的数字
			bucket[num].push_back(a[j]);
		}
		//内层for循环跑完了一遍数组
		//数据收集,做降序处理
		int index = 0;
		//这是升序处理
		//for (const auto& item : bucket)
		//{
		//	for (const auto& it : item)
		//	{
		//		//写回a这个vector容器
		//		a[index++] = it;
		//	}
		//}
		//下为倒序处理
		for (auto item = bucket.rbegin(); item != bucket.rend(); item++)//反常++，迭代器实际向前移动
		{
			for (const auto& it : *item)
			{
				a[index++] = it;
			}
		}
		//桶内还是正序处理
		//重置桶里的数据
		bucket.assign(10, vector<int>());//分配十个vector数组
	}
}
//传统计数排序
//https://www.bilibili.com/video/BV1KU4y1M7VY/?spm_id_from=333.337.search-card.all.click&vd_source=9fe037978f56e9671016c226acdbddbb
void countingsort(vector<int>& a)
{
	if (a.empty()) return;
	//取出最大最小值
	int min = *min_element(a.begin(), a.end());
	int max = *max_element(a.begin(), a.end());
	int range = max - min + 1;//这里可能会占用过大内存
	//初始化计数数组
	vector<int> count(range, 0);
	for (int num : a)
	{
		count[num - min]++;//偏移量为min，为了更好映射
	}
	//计算前缀和，便于确定各个数的位置//这个是升序处理
	/*for (int i = 1; i < range; i++)
	{
		count[i] += count[i - 1];
	}*/
	//下面是计算前缀和的降序处理，从右至左计算前缀和
	for (int i = range - 2; i >= 0; i--)
	{
		count[i] += count[i + 1];
	}
	//反向遍历数组，保证稳定性，并填充结果
	vector<int> res(a.size());
	for (int i = a.size() - 1; i >= 0; i--)
	{
		int num = a[i];//获取具体数字
		int index = count[num - min] - 1;//考虑偏移量，获得该数字再排序后数组的索引
		res[index] = num;//索引赋值
		count[num - min]--;//排了一次就减掉，避免重复赋值
	}
	a = res;
}
void print(int a[])
{
	for (int i = 0; i < m_size; ++i)
	{
		cout << a[i] << " ";
	}
	cout << "\n";
}
void print(vector<int>& a)
{
	for (int i = 0; i < a.size(); ++i)
	{
		cout << a[i] << " ";
	}
	cout << "\n";
}

int main()
{
	//Bublesort(a);
	//Selectsort(a);
	//insert(a);
	//Shellsort(a);
	//quicksort(a,0,size -1);
	//mergesort(a, 0, size - 1, temp);
	//radixsort(a_m);
	countingsort(a_m);
	print(a_m);
	/*print(a);*/
}