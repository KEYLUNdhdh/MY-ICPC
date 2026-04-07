#include <stdio.h>
// 本题要求
long long SumProducts(int n, int m)
{
    long long ans = 0;
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= m;j++)
        {
            ans += 1ll * i * j;
        }
    }
    return ans;
}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    printf("%lld\n", SumProducts(n, m));
    return 0;
}