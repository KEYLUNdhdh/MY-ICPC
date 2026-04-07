#include <bits/stdc++.h>
#define int long long
#define ld long double
using namespace std;
int h, w;
int d[100][100];
int I[3][100][100];
int K[3][100][100];
int prefix[100][100];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> h >> w;
    for (int k = 0; k < 3;k++)
        for (int i = 1; i <= h;i++)
            for (int j = 1; j <= w;j++)
                cin >> I[k][i][j];

    for (int k = 0; k < 3;k++)
        for (int i = 1; i <= h;i++)
            for (int j = 1; j <= w;j++)
                cin >> K[k][i][j];

    for (int k = 0; k < 3;k++)
    {
        for (int i = 1; i <= h;i++)
        {
            for (int j = 1; j <= w;j++)
            {
                d[i][j] += (I[k][i][j] - K[k][i][j]) * (I[k][i][j] - K[k][i][j]);
            }
        }
    }
    ld m = 0;
    for (int i = 1; i <= h;i++)
    {
        for (int j = 1; j <= w;j++)
        {
            prefix[i][j] = d[i][j] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
        }
    }
    m = 1e18;
    int minh = (h + 1) / 2;
    int minw = (w + 1) / 2;
    for (int r1 = 1; r1 <= h;r1++)
        for (int c1 = 1; c1 <= w;c1++)
            for (int r2 = r1 + minh - 1; r2 <= h;r2++)
                for (int c2 = c1 + minw - 1; c2 <= w;c2++)
                {
                    ld cu = prefix[r2][c2] - prefix[r1 - 1][c2] - prefix[r2][c1 - 1] + prefix[r1 - 1][c1 - 1];
                    int H = r2 - r1 + 1;
                    int W = c2 - c1 + 1;
                    ld M = cu / (ld)(3 * H * W);
                    m = min(m, M);
                }
    ld ps = (ld)20 * log10((ld)255 / (ld)sqrt(m));
    cout << fixed << setprecision(8) << ps;
}