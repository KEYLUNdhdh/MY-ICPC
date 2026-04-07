#include <stdio.h>

// 本题要求实现
long long SumUp(int n)
{
    long long m = (n * n) * (1ll + n * n) / 2ll;
    long long q = (1ll + n) * n / 2ll;
    return m + q;
}
int main() {
    int n;
    scanf("%d", &n);
    printf("%lld\n", SumUp(n));
    return 0;
}