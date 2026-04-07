#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 定义坐标结构体
struct Point {
    int x, y;
};

// 预处理 0-9 的坐标
// 1:(0,0), 2:(0,1), 3:(0,2)
// 4:(1,0), 5:(1,1), 6:(1,2)
// 7:(2,0), 8:(2,1), 9:(2,2)
// 0:(3,1)
Point getPos(char c) {
    if (c == '0') return {3, 1};
    int digit = c - '1';
    return {digit / 3, digit % 3};
}

// 检查坐标是否是有效的按键
bool isValid(int x, int y) {
    if (x >= 0 && x <= 2 && y >= 0 && y <= 2) return true; // 1-9
    if (x == 3 && y == 1) return true; // 0
    return false;
}

int main() {
    int n;
    string s;
    if (!(cin >> n >> s)) return 0;

    // 原始字符串第一个字符的坐标
    Point startPos = getPos(s[0]);

    // 枚举所有可能的“新起点”字符 '0' 到 '9'
    for (char c = '0'; c <= '9'; c++) {
        // 如果新起点和原起点一样，跳过（我们要找的是“另一个”号码）
        if (c == s[0]) continue;

        Point newStartPos = getPos(c);
        
        // 计算偏移量 (dx, dy)
        int dx = newStartPos.x - startPos.x;
        int dy = newStartPos.y - startPos.y;

        // 检查原字符串中的每一个字符，在加上偏移量后是否仍然有效
        bool possible = true;
        for (char digit : s) {
            Point p = getPos(digit);
            int nx = p.x + dx;
            int ny = p.y + dy;
            
            if (!isValid(nx, ny)) {
                possible = false;
                break; // 只要有一个字符出界，这个新起点 c 就不行
            }
        }

        // 如果对于起点 c，所有字符变换后都有效，说明找到了另一个号码
        if (possible) {
            cout << "NO" << endl;
            return 0;
        }
    }

    // 如果枚举完所有可能都没有找到合法的替换，则说明是唯一的
    cout << "YES" << endl;

    return 0;
}