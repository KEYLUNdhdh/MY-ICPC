#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
long long M;
if (!(cin >> N >> M)) return 0;

vector<long long> A(N);
for (int i = 0; i < N; ++i) {
    cin >> A[i];
}

// cnt[k][r] 表示：有多少个 A_i 满足 (A_i * 10^k) % M == r
// k 的范围是 1 到 10 (因为 A_i <= 10^9)
// 使用 map 来存储余数的计数，key 是余数，value 是次数
vector<map<long long, int>> cnt(11);

for (int i = 0; i < N; ++i) {
    long long current_val = A[i] % M;
    for (int k = 1; k <= 10; ++k) {
        current_val = (current_val * 10) % M;
        cnt[k][current_val]++;
    }
}

long long ans = 0;

for (int i = 0; i < N; ++i) {
    long long val = A[i];
    
    // 计算位数
    // 也可以用 to_string(val).length()，但数学计算更快一点
    int len = 0;
    long long temp = val;
    while (temp > 0) {
        temp /= 10;
        len++;
    }
    // 特殊情况：如果 val 是 0（虽然题目说正整数），位数为 1
    if (val == 0) len = 1;

    // 公式： (A_i * 10^len + A_j) % M == 0
    // => (A_i * 10^len) % M == (-A_j) % M
    // => (A_i * 10^len) % M == (M - (A_j % M)) % M
    
    long long rem_j = val % M;
    long long target = (M - rem_j) % M;

    // 在对应的位数 k=len 的 map 中查找需要的余数 target
    if (cnt[len].count(target)) {
        ans += cnt[len][target];
    }
}

cout << ans << endl;

return 0;

}