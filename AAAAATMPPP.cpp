#include<iostream>
#include<vector>
using namespace std;

const int N = 300010;
vector<int>edge[N];
int n,m;
int ans[N];

void dfs(int u) {
    for (int v : edge[u]) {
        if (ans[v] != -1)continue;
        ans[v] = ans[u] + 1;
        dfs(v);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)edge[i].clear();
    for (int i = 1; i <= n; ++i) {
        ans[i] = -1;
    }
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    ans[1] = 0;
    dfs(1);
    for (int i = 1; i <= n; ++i)cout << ans[i] << " ";
    puts("");
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}