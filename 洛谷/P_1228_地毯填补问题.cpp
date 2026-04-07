#include <bits/stdc++.h>
using namespace std;

void solve(int x,int y,int len,int px,int py)
{   
    if(len == 1)
        return;
    int half = len / 2;
    int midx = x + half;
    int midy = y +  half;

    if (px < midx && py < midy)
    {
        cout << midx << " " << midy << " " << 1 << "\n";
        solve(x, y, half, px, py);
        solve(x, midy, half, midx - 1, midy);
        solve(midx, y, half, midx, midy - 1);
        solve(midx, midy, half, midx, midy);
    }
    else if(px < midx && py >= midy)
    {
        cout << midx << " " << midy - 1 << " " << 2 << "\n";
        solve(x, y, half, midx - 1, midy - 1);
        solve(x, midy, half, px, py);
        solve(midx, y, half, midx, midy - 1);
        solve(midx, midy, half, midx, midy);
    }
    else if (px >= midx && py < midy)
    {
        cout << midx - 1 << " " << midy  << " "<< 3 << "\n";
        solve(x, y, half, midx - 1, midy - 1);
        solve(x, midy, half, midx - 1, midy);
        solve(midx, y, half, px, py);
        solve(midx, midy, half, midx, midy);

    }
    else
    {
        cout << midx - 1 << " " << midy - 1 << " " << 4 << "\n";
        solve(x, y, half, midx - 1, midy - 1);
        solve(x, midy, half, midx - 1, midy);
        solve(midx, y, half, midx, midy - 1);
        solve(midx, midy, half, px, py);
    }
    return;
}

int main()
{
    int k, x, y;
    cin >> k >> x >> y;
    solve(1, 1, 1 << k, x, y);

    return 0;
}