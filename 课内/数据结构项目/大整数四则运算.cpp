#include <bits/stdc++.h>
using namespace std;
using i64 = long long;//为long long取别名，方便编写代码

// ==========================================
// 大整数类 (BigInt) 结构体封装
// 这是我打算法竞赛时已经封装好的板子
// ==========================================
struct BigInt
{
    // 采用逆序（小端序）存储大整数的每一位数字。
    // 例如：数字 123 存储为 [3, 2, 1]。
    // 在进行加法进位或乘法运算时，向高位扩展只需要在 vector 尾部 push_back 即可，极为高效。
    vector<int> vec;

    // 符号位：1 表示正数或 0，-1 表示负数
    int sign;

    // 构造函数：从 long long 整型初始化大整数
    BigInt(i64 x = 0)
    {
        //特判是正数还是负数
        if(x < 0)
            sign = -1, x = -x;
        else
            sign = 1;

        if(x == 0)
            vec.push_back(0);

        // 剥离每一位数字并存入数组
        while(x)
        {
            vec.push_back(x % 10);
            x /= 10;
        }
    }

    // 构造函数：从字符串初始化大整数
    BigInt(string s)
    {
        if(s.empty())
        {
            sign = 1;
            vec = {0};
            return;
        }

        // 处理负号
        if(s[0] == '-')
        {
            sign = -1;
            s = s.substr(1);
        }
        else
            sign = 1;
        
        // 逆序遍历字符串，存入 vector
        for (int i = s.size() - 1; i >= 0;i--)
        {
            vec.push_back(s[i] - '0');
        }
        trim();// 去除可能存在的前导零
    }

    // 核心维护函数：去除大整数高位多余的 0（即 vector 尾部的 0）
    // 防止出现 "000123" 这种非法表示
    void trim()
    {
        while(vec.size() > 1 && vec.back() == 0)
            vec.pop_back();

        // 防止出现 "-0" 的情况
        if(vec.size() == 1 && vec[0] == 0)
            sign = 1;
    }

    // 辅助函数：比较两个大整数的绝对值大小 (|a| < |b|)
    static bool abs_less(const BigInt& a,const BigInt &b)
    {
        if(a.vec.size() != b.vec.size())
            return a.vec.size() < b.vec.size();// 位数少则绝对值小
        
        // 位数相同时，从高位（vector尾部）向低位比较
        for (int i = a.vec.size() - 1; i >= 0;i--)
        {
            if(a.vec[i] != b.vec[i])
                return a.vec[i] < b.vec[i];
        }
        return false;
    }

    // 重载关系运算符：基于符号和绝对值进行严格比较
    bool operator<(const BigInt& b) const
    {
        if(sign != b.sign)
            return sign < b.sign;// 一正一负直接出结果
        
        if(sign == 1)
            return abs_less(*this, b);// 同为正，比较绝对值
        else
            return abs_less(b, *this);// 同为负，绝对值大的反而小
    }

    //剩余比较逻辑
    bool operator>(const BigInt &b) const { return b < *this; }
    bool operator<=(const BigInt &b) const { return !(*this > b); }
    bool operator>=(const BigInt &b) const { return !(*this < b); }
    bool operator==(const BigInt &b) const { return (sign == b.sign && vec == b.vec); }
    bool operator!=(const BigInt &b) const { return !(*this == b); }

    // 基础运算：无符号绝对值加法 (|a| + |b|)
    // 模拟列竖式计算，逐位向高位进位 (carry)
    static BigInt abs_add(const BigInt& a, const BigInt& b) 
    {
        BigInt res;
        res.vec.clear();

        int t = 0;// t 用于记录进位

        for (int i = 0; i < max(a.vec.size(), b.vec.size()) || t; i++) 
        {
            int cur = t + (i < a.vec.size() ? a.vec[i] : 0) + (i < b.vec.size() ? b.vec[i] : 0);
            res.vec.push_back(cur % 10);
            t = cur / 10;
        }
        return res;
    }

    // 基础运算：无符号绝对值减法 (|a| - |b|)，前提保证 |a| >= |b|
    // 模拟列竖式计算，逐位借位 (borrow)
    static BigInt abs_sub(const BigInt& a, const BigInt& b) 
    {
        BigInt res = a;
        int t = 0;// t 用于记录借位

        for (int i = 0; i < b.vec.size() || t; i++) 
        {
            res.vec[i] -= t + (i < b.vec.size() ? b.vec[i] : 0);
            if (res.vec[i] < 0) 
            {
                res.vec[i] += 10;// 需要向高位借位
                t = 1;
            } 
            else 
                t = 0;
        }
        res.trim();// 减法极易产生前导零，必须清理
        return res;
    }

    // 重载加法：根据数学规则将其转化为绝对值加法或减法
    friend BigInt operator+(BigInt a, const BigInt& b) 
    {
        if (a.sign == b.sign) // 同号相加
        {
            BigInt res = abs_add(a, b);
            res.sign = a.sign;
            return res;
        }

        // 异号相加，转化为绝对值较大的减去绝对值较小的
        if (abs_less(a, b)) 
        {
            BigInt res = abs_sub(b, a);
            res.sign = b.sign;
            return res;
        } 
        else 
        {
            BigInt res = abs_sub(a, b);
            res.sign = a.sign;
            return res;
        }
    }

    // 重载减法：a - b 等价于 a + (-b)
    friend BigInt operator-(BigInt a, BigInt b) 
    {
        b.sign *= -1;// 翻转减数的符号
        return a + b;
    }

    // 重载乘法：O(N^2) 高精度乘法
    // a 的第 i 位乘以 b 的第 j 位，累加到结果的第 i+j 位
    friend BigInt operator*(const BigInt& a, const BigInt& b) 
    {
        if ((a.vec.size() == 1 && a.vec[0] == 0) || (b.vec.size() == 1 && b.vec[0] == 0))
            return BigInt(0);// 任何数乘0得0

        BigInt res;
        res.vec.assign(a.vec.size() + b.vec.size(), 0);// 乘积的最大位数不超过两者位数之和

        for (int i = 0; i < a.vec.size(); i++) 
        {
            for (int j = 0; j < b.vec.size(); j++) 
            {
                res.vec[i + j] += a.vec[i] * b.vec[j];// 对应位乘积累加
                res.vec[i + j + 1] += res.vec[i + j] / 10;// 处理进位
                res.vec[i + j] %= 10;// 当前位保留个值
            }
        }

        res.sign = a.sign * b.sign;// 同号得正，异号得负
        res.trim();

        return res;
    }

    // 重载一元负号操作符 (例如: a = -b)
    BigInt operator-() const 
    {
        BigInt res = *this;
        if (res != BigInt(0)) res.sign *= -1;
        return res;
    }

    // 复合赋值运算符
    BigInt& operator+=(const BigInt& b) { return *this = *this + b; }
    BigInt& operator-=(const BigInt& b) { return *this = *this - b; }
    BigInt& operator*=(const BigInt& b) { return *this = *this * b; }

    // 基础运算：无符号绝对值带余除法 (返回 商 和 余数)
    // 模拟竖式长除法：从高位到低位逐位拉下，尝试减去被除数
    static pair<BigInt, BigInt> abs_divmod(const BigInt& a, const BigInt& b) 
    {
        if (b == BigInt(0)) return {BigInt(0), BigInt(0)};// 除数不能为0（理论上应抛出异常）
        if (abs_less(a, b)) return {BigInt(0), a};// 被除数小于除数，商0余a

        BigInt q, r(0);
        q.vec.assign(a.vec.size(), 0);

        // 从被除数的高位开始模拟长除法
        for (int i = a.vec.size() - 1; i >= 0; i--) 
        {
            r = r * 10 + BigInt(a.vec[i]);// 将上一位的余数乘10，加上当前位
            int cnt = 0;

            // 通过循环减法求出当前位的商 (最多减9次)
            while (!abs_less(r, b)) 
            {
                r = abs_sub(r, b);
                cnt++;
            }
            q.vec[i] = cnt;// 记录当前位的商
        }

        //消除前导零
        q.trim();
        r.trim();
        return {q, r};
    }

    // 重载除法与取模：包装符号判断逻辑
    friend pair<BigInt, BigInt> divmod(BigInt a, BigInt b) 
    {
        int res_q_sign = a.sign * b.sign;// 商的符号：同号得正，异号得负
        int res_r_sign = a.sign; // 余数的符号：通常与被除数一致

        pair<BigInt, BigInt> res = abs_divmod(a, b);
        
        res.first.sign = res_q_sign;
        res.second.sign = res_r_sign;
        
        //消除前导零
        res.first.trim();  
        res.second.trim();
        return res;
    }

    // 复合赋值运算符    
    BigInt operator/(const BigInt& b) const { return divmod(*this, b).first; }
    BigInt operator%(const BigInt& b) const { return divmod(*this, b).second; }
    BigInt& operator/=(const BigInt& b) { return *this = *this / b; }
    BigInt& operator%=(const BigInt& b) { return *this = *this % b; }

    // 允许大整数直接与普通 int 相乘 (辅助重载)
    BigInt operator*(int b_int) const 
    {
        if (b_int == 0) return BigInt(0);
        BigInt b_big(b_int);
        return (*this) * b_big;
    }

    // 重载输出流：因为底层是逆序存储，输出时必须从后往前遍历
    friend ostream& operator<<(ostream& os, const BigInt& a) 
    {
        if (a.sign == -1) os << '-';
        for (int i = a.vec.size() - 1; i >= 0; i--) os << a.vec[i];
        return os;
    }

    // 重载输入流：读取字符串并利用构造函数转换
    friend istream& operator>>(istream& is, BigInt& a) 
    {
        string s;
        if (!(is >> s)) return is;
        a = BigInt(s);
        return is;
    }
};

// ==========================================
// 表达式求值逻辑 (结合双栈算法)
// 针对题意进行编写
// ==========================================

// 获取运算符优先级
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0; // 括号或未知符号
}

// 弹出一个运算符和两个操作数进行一次计算
void computeTop(stack<BigInt>& nums, stack<char>& ops) {
    if (nums.size() < 2 || ops.empty()) return; // 防御性判断
    
    BigInt b = nums.top(); nums.pop();
    BigInt a = nums.top(); nums.pop();
    char op = ops.top(); ops.pop();
    
    if (op == '+') nums.push(a + b);
    else if (op == '-') nums.push(a - b);
    else if (op == '*') nums.push(a * b);
    else if (op == '/') nums.push(a / b);
}

// 解析并计算完整的表达式字符串
BigInt evaluateExpression(const string& s) {
    stack<BigInt> nums;
    stack<char> ops;
    int n = s.length();
    
    // is_unary 标记当前读取的 '-' 是否是一元符号（负号）
    // 如果出现在表达式开头，或者紧跟在 '(' 甚至其他操作符后面，那就是负数
    bool is_unary = true; 

    for (int i = 0; i < n; i++) {
        if (isspace(s[i])) continue;

        if (s[i] == '(') {
            ops.push(s[i]);
            is_unary = true; // 括号后面出现的第一个减号是负号
        } 
        else if (s[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                computeTop(nums, ops);
            }
            if (!ops.empty()) ops.pop(); // 弹出 '('
            is_unary = false; // 右括号后面接的肯定是操作符，不是数字的负号
        } 
        // 遇到数字，或者遇到了负号（且判断为一元运算符）
        else if (isdigit(s[i]) || (s[i] == '-' && is_unary)) {
            string val = "";
            if (s[i] == '-') {
                val += '-';
                i++;
            }
            while (i < n && isdigit(s[i])) {
                val += s[i];
                i++;
            }
            i--; // 因为for循环还会i++，这里退回一步
            nums.push(BigInt(val));
            is_unary = false; // 数字读取完毕，接下来期望遇到操作符
        } 
        else { 
            // 遇到二元操作符: + - * /
            while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(s[i])) {
                computeTop(nums, ops);
            }
            ops.push(s[i]);
            is_unary = true; // 操作符之后，可以合法接负号（比如 3 * -5）
        }
    }

    // 扫描完成后，清空栈中剩余的运算
    while (!ops.empty()) {
        computeTop(nums, ops);
    }

    return nums.empty() ? BigInt(0) : nums.top();
}

int main() {
    cout << "请输入大整数四则运算算式 (支持加减乘除及括号):" << endl;
    string expression;
    if (getline(cin, expression)) {
        BigInt result = evaluateExpression(expression);
        cout << "计算结果: " << result << endl;
    }
    return 0;
}