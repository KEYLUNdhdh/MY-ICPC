#include <bits/stdc++.h>
#define int long long
using namespace std;

// 手写 GCD 保证兼容性
int get_gcd(int a, int b) {
    return b == 0 ? a : get_gcd(b, a % b);
}

signed main() {
    string s;
    if (!(cin >> s)) return 0;
    s = s + "#";

    int i = 0, cnt = 0, f = 1;
    int resZ = 0, resM = 0; // 存储累加结果

    while (i < s.size()) {
        if (s[i] == '#') break;
        if (s[i] == '-') { f = -1; i++; }
        else if (s[i] == '+') { f = 1; i++; }
        else if (s[i] == '/') { i++; continue; }
        else if (isdigit(s[i])) {
            int num = 0;
            while (i < s.size() && isdigit(s[i])) {
                num = num * 10 + s[i] - '0';
                i++;
            }
            
            static int curZ; // 临时存当前分数分子
            if (cnt == 0) {
                curZ = f * num;
                cnt++;
            } else {
                int curM = num;
                cnt = 0;
                
                // --- 核心计算逻辑：边加边化简 ---
                if (resM == 0) { // 第一个分数
                    resZ = curZ;
                    resM = curM;
                } else {
                    // 公式：a/b + c/d = (ad + bc) / bd
                    int newZ = resZ * curM + curZ * resM;
                    int newM = resM * curM;
                    int common = get_gcd(abs(newZ), abs(newM));
                    resZ = newZ / common;
                    resM = newM / common;
                }
            }
        }
    }
    int gcc = gcd(resZ, resM);
    // 最后输出
    if (resZ % resM == 0) 
        cout << resZ / resM;
    else {
        // 确保分母为正
        if (resM < 0) { resZ = -resZ; resM = -resM; }
        cout << resZ  / gcc<< "/" << resM /gcc;
    }
    
    return 0;
}