#include <stdio.h>
#include <stdlib.h>

// 本题要求实现
long long GCD(long long x, long long y)
{
    if(x < y)
    {
        long long tp = x;
        x = y;
        y = tp;
    }
    return (y == 0 ? x : GCD(y, x % y));
}
int main() {
    long long x, y;
    scanf("%lld %lld", &x, &y);
    printf("%lld\n", GCD(x, y));
    return 0;
}