#include <iostream>
#include <deque>
#include <algorithm>
#include <iomanip>
using namespace std;

double wayout(int m)
{
	deque<double> q;
	double temp;
	int fin = m;
	while (m--)
	{
		cin >> temp;
		q.push_back(temp);
	}
	sort(q.begin(), q.end());
	q.pop_back();
	q.pop_front();
	double sum = 0;
	for (auto it = q.begin(); it != q.end(); it++)
	{
		sum += *it;
	}
	double res = sum / (double)(fin - 2);
	return res;
}

int main()
{
	int n, m;
	double max = 0;
	cin >> n >> m;
	while (n--)
	{
		double cop = wayout(m);
		if (cop > max)
			max = cop;
	}
	cout << fixed << setprecision(2) << max;
}