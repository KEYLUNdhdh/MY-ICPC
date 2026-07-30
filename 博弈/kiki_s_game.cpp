#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        if ((n & 1) && (m & 1))
            cout << "What a pity!\n";
        else
            cout << "Wonderful!\n";
    }

    return 0;
}