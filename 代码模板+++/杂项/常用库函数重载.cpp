#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
template<class T>
T ceilDiv(T n, T m) {
    if (n >= 0) {
        return (n + m - 1) / m;
    //-
    } else {
        return n / m;
    }
}
template<class T>
T floorDiv(T n, T m) {
    if (n >= 0) {
        return n / m;
    //-
    } else {
        return (n - m + 1) / m;
    }
}

template<class T>
void chmax(T &a, T b) {
    if (a < b) {
        a = b;
    }
}

i128 gcd(i128 a, i128 b) {
    return b ? gcd(b, a % b) : a;
}
