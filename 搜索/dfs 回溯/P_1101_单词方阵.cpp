#include <bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int N = 105;
int n;
char c[N][N] = {'\0'};
int ava[N][N] = {0};
int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
string check = "yizhong";
vector<pii> vec;
void search(int i,int j)
{
    vec.clear();
    for (int k = 0; k < 8;k++)
    {
        vec.push_back(make_pair(i, j));
        int nx, ny, cnt = 0;
        for (int p = 1; p <= 6;p++)
        {
            nx = i + dx[k] * p;
            ny = j + dy[k] * p;
            if (nx >= 0 &&nx < n &&ny >= 0 &&ny < n &&c[nx][ny] == check[p])
            {
                vec.push_back(make_pair(nx, ny));
            }
            else
            {
                break;
            }
        }
        if(vec.size() == 7)
        {
            for(auto it : vec)
            {
                ava[it.first][it.second]++;
            }
        }
        vec.clear();
    }
}
int main()
{
    
    cin >> n;
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < n;j++)
        {
            cin >> c[i][j];
        }
    }
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < n;j++)
        {
            if(c[i][j] == 'y')
            {
                search(i, j);
            }
        }
    }
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < n;j++)
        {
            if(!ava[i][j])
                cout << "*";
            else
                cout << c[i][j];
        }
        cout << "\n";
    }

}