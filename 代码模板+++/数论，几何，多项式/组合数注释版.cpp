#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
//constexpr
// 它表示这个构造函数可以在编译期执行。如果你定义一个常量 constexpr MLong<P> a;，编译器在编译程序的时候就已经把 a.x 初始化好了，不需要等到程序运行时再分配，这能提高性能。
template<class T>
constexpr T qpow(T a,i64 b)
{
    T res = 1;
    while(b)
    {
        if(b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
// 针对超大整数的乘法取模（防止 a*b 溢出 long long）
// 使用 long double 辅助计算
//根据数学恒等式 a*b = k*p + r（r = (a*b) % p，0 ≤ r < p），则 k = floor(a*b / p)，因此 r = a*b - k*p。
constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p; 
    res %= p;
    if (res < 0) res += p;
    return res;
}
// i64 P非类型模板参数
// 作用：将一个固定的常量“嵌入”模板中，让模板在编译期就确定这个值，无需在运行时传递。
// 要求：参数必须是编译时常量（如字面量、constexpr 变量、枚举值等），不能是运行时才能确定的变量（如用户输入的 int x）。
template<i64 P>
// MLong 与 MInt
// 自动取模结构体这两个结构体逻辑几乎一样。
// MInt 针对普通的 int（通常模数为 998244353），MLong 针对 long long。
// 核心成员变量：x: 实际存储的数值，保证始终在 [0, Mod-1] 之间。Mod: 静态变量，存储当前的模数。核心函数：norm(x): 标准化函数。如果 x 超出了模数范围，把它拉回来。这是保证代码安全的关键。
//在 C++ 的结构体或类中，加上 static 关键字意味着这些成员属于整个类，而不是属于某个具体的对象。这是得Mod是所有MLong通用的
struct MLong
{
    i64 x;
    // 列表初始化,x{}相当于x = 0;之后的{}就是空构造函数
    constexpr MLong() : x{} {}
    //这个才是我们初始化的地方
    constexpr MLong(i64 x) : x{norm(x % getMod())} {}
    //在 C++ 的结构体或类中，加上 static 关键字意味着这些成员属于整个类，而不是属于某个具体的对象。
    //简单来说，无论你创建了多少个 MLong 变量，它们都共享同一个模数。
    //代码中的模板参数 template<i64 P> 是编译期确定的。如果题目给定了固定模数（如 998244353），我们用 MLong<998244353>。但有些题目会动态输入一个模数 M。这时候 P 会被设为 0（即 MLong<0>）。当 P 为 0 时，getMod() 会去读取那个 static i64 Mod。因为它是静态的，你只需要通过 MLong<0>::setMod(M) 设置一次，后续所有的 MLong<0> 对象就都知道模数是多少了。
    static i64 Mod;
    constexpr static i64 getMod()
    {
        if(P > 0)
            return P;
        else
            return Mod;
    }
    constexpr static void setMod(i64 Mod_)
    {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const
    {
        if(x < 0)
            x += getMod();
        if(x >= getMod())
            x -= getMod();
        return x;
    }
    constexpr i64 val() const
    {
        return x;
    }
    //这是一个类型转换重载。它告诉编译器：“如果有人把 MLong 当作 i64 (即 long long) 来用，你可以按照这个规则把MLong 转换为 i64,且必须显式转换。”
    //explicit 的作用： 这个关键字非常重要。它表示这种转换必须是强制显式的。编译器不会在后台偷偷帮你转换，防止你写错代码。
    // i64 num = a;       // 错误！因为有 explicit，禁止隐式转换
    //i64 num = (i64)a;    // 正确！手动强制转换，触发 operator i64()
    explicit constexpr operator i64() const 
    {
        return x;
    }
    //在函数名后面的 const（如 val() const），是在告诉编译器：“这个函数很安全，它保证不会修改对象里的任何数据。”
    constexpr MLong operator-() const
    {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const
    {
        assert(x != 0);
        return qpow(*this, getMod() - 2);
    }
    //在 C++ 中，左值通常是有名字的变量，右值是临时产生的值。
    //&的意思是：“这个函数只能由左值（Lvalue）调用。”
    //正确用法
    // Z a(1), b(2);
    // a += b; // 正确！a 是个变量，可以被修改
    //错误用法
    //(a + b) += a;
    //如果没有这个 &，上面这行代码是可以通过编译的。但它毫无意义，因为 (a + b) 产生的是一个临时对象，你给一个马上就要消失的临时对象做加法，纯属浪费 CPU。 加上 & 后，编译器会直接拦截这种对临时对象的赋值操作，报错提示你。
    constexpr MLong &operator*=(MLong rhs) & 
    {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong &operator+=(MLong rhs) &
    {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong &operator-=(MLong rhs) & 
    {
        x = norm(x - rhs.x);
        return *this;
    }
    //为什么 operator/= 没有 friend？（它是成员函数）
    // operator/= 是一个赋值运算符。根据 C++ 的规定，赋值类运算符（如 =, +=, -=, /=）修改的是左侧的对象本身。
    // 逻辑上：它是属于某个具体对象的行为。当你写 a /= b 时，实际上是“告诉 a 把它自己除以 b”。
    // 语法上：成员函数会自动把左操作数绑定为 this 指针。对于 a /= b，a 必须是一个 MLong 类型的变量，这非常符合逻辑。
    constexpr MLong &operator/=(MLong rhs) &
    {
        return *this *= rhs.inv();
    }
    // 为什么 operator* 要加 friend？（它是全局友元函数）
    // operator* 是一个算术运算符，它不修改操作数，而是返回一个全新的值。
    // 核心原因：为了支持“对称性”和“隐式类型转换”。
    // 想象一下如果你不加 friend，把它写成成员函数：
    // MLong a = b * 2; 可以编译。因为 b 是 MLong，它有 operator* 成员，能把 2 转换成 MLong 再计算。
    // MLong a = 2 * b; 无法编译！ 因为左边的 2 是基本类型 int，它没有名为 operator* 的成员函数。
    //加上 friend（即声明为全局函数）后： 编译器会把 a * b 转化成 operator*(a, b)。此时，无论左边还是右边是 long long，编译器都能发现构造函数 MLong(i64 x) ，并自动把数字包装成 MLong 对象。
    //欸有人会问，这里不是涉及隐式转换了吗？我们上文不是有explicit吗
    // 别急，其实这是一种非常有经验的设计：
    // 入方向（数字 -> 对象）即构造函数MLong(i64 x)：不加 explicit。允许 a = 2，让对象“吸纳”数字。
    // 出方向（对象 -> 数字）：加上 explicit。防止你不小心把 MLong 当成普通数字传给某些危险函数（比如 printf 或数组下标），除非你显式地写 (i64)a。
    friend constexpr MLong operator*(MLong lhs, MLong rhs) 
    {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs) 
    {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs) 
    {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MLong operator/(MLong lhs, MLong rhs) 
    {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    // 在 C++ 中，输入流 >> (cin) 和输出流 << (cout) 本质上是函数调用。
    // 当我们写 cin >> a 时，编译器其实在找一个函数叫 operator>>(cin, a)。由于 cin 的官方代码里肯定没写过怎么处理你自定义的 MLong，所以我们必须在自己的代码里通过 friend 函数教编译器怎么做。  
    //为什么返回 is？ 为了支持链式输入。当你写 cin >> a >> b; 时，编译器先执行 (cin >> a)，返回 cin 后再执行 cin >> b。
    friend constexpr istream &operator>>(istream &is,MLong &a)
    {
        i64 v;
        is >> v;// 1. 先从流中读入一个普通的 long long (v)
        a = MLong(v);// 2. 利用构造函数把 v 包装成 MLong 类型（会自动取模）
        return is;// 3. 把流原样返回
    }
    //ostream &os：这是 cout 的引用。我们把它当作一个“传送带”，把数据丢进去。
    // const MLong &a：这是我们要打印的对象。用 const 是因为打印操作不应该修改它，用 & 是为了避免复印件产生的开销。
    // 内部原理：函数内部调用了 a.val() 拿到那个底层的 long long 数值，然后丢给 os。
    //可以简单理解为a.val()通过<<进入了cout这个函数里面，最后再return这个cout
    // 为什么要 return os？：这是为了支持链式调用。 当你写 cout << a << b; 时，cout << a 会执行完并返回 cout 自身，接着代码就变成了 cout << b;，这样就能一直传下去。
    friend constexpr ostream &operator<<(ostream &os,MLong &a)
    {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs,MLong rhs)
    {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!= (MLong lhs,MLong rhs)
    {
        return lhs.val() != rhs.val();
    }
};
//下面这行代码涉及 C++ 中两个比较高级的概念：模板特化（Template Specialization） 和 静态变量初始化。
// 简单来说，这行代码是在为 MLong<0> 这个特殊的版本设置默认的模数。
//1. 为什么模板括号是空的 template <>？
//这叫全特化（Full Specialization）。在你的代码开头，MLong 是这样定义的：
//template<i64 P> struct MLong { ... };
//编译器会把 MLong<998244353> 和 MLong<0> 看作两个完全不同的类。
//对于 MLong<998244353>，模数 $P$ 已经确定了。
//对于 MLong<0>，它代表“模数要在运行时动态指定”的版本。
//当你写 template <> 时，你是在告诉编译器：“我要给 MLong 模板中那个参数为 0ll 的特定版本写一点特殊的东西。” 因为参数 0ll 已经写在后面的 MLong<0ll> 里了，所以前面的 template 后面就不需要再写参数名，留空即可。
//在 C++ 中，类内部的 static 变量只是声明(之前的Mod)，它并不占用实际的内存。你必须在类外部找个地方正式地定义并初始化它，否则链接器会报错
//这行代码的意思是：“为 MLong<0ll> 这个类里的静态成员 Mod 分配内存，并把它初始化为 10^18 + 9。”
//3. 为什么只有 MLong<0ll> 需要这行代码？
//如果是 MLong<998244353>：在 getMod() 函数里，if (P > 0) 成立，直接返回了模板参数 998244353，根本用不到 static i64 Mod。如果是 MLong<0>：if (P > 0) 不成立，它会去读 Mod。如果不初始化它，程序就没法运行。
template <>
i64 MLong<0ll>::Mod = (i64)1e18 + 9;

template<int P>
struct MInt
{
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(x % getMod())} {}

    static int Mod;
    constexpr static int getMod()
    {
        if(P > 0)
            return P;
        else
            return Mod;
    }
    constexpr static void setMod(int Mod_)
    {
        Mod = Mod_;
    }
    constexpr int norm(int x) const 
    {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const 
    {
        return x;
    }
    explicit constexpr operator int() const 
    {
        return x;
    }
    constexpr MInt operator-() const 
    {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const 
    {
        assert(x != 0);
        return qpow(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & 
    {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & 
    {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & 
    {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & 
    {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) 
    {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) 
    {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) 
    {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) 
    {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) 
    {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) 
    {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) 
    {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) 
    {
        return lhs.val() != rhs.val();
    }
};

template<>
int MInt<0>::Mod = 998244353;
//这个 CInv 的写法其实是 C++14 引入的一个非常酷的特性，叫做 变量模板（Variable Template）。它能让编译器在编译程序的一瞬间就把逆元算出来。
//变量模板允许你定义一个带参数的变量。
// V：代表你想求逆元的那个数（比如 2）。
// P：代表模数。
// CInv<2, 998244353>：这就像一个“黑盒子”，你传进去 2 和模数，它直接给你结果。
//constexpr 的魔力：编译期预计算
// 这是最关键的地方。因为 MInt 的构造函数、inv() 函数、power() 函数全部都标记了 constexpr，这意味着它们都可以在编译期运行。
template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();
//写using Z = MInt<P>; 且 P = 998244353 时，编译器会生成一套专门为 998244353 服务的一套代码。这就好比你根据一个 42 号的鞋模子，直接注塑出了一双鞋，这双鞋的大小在出厂（编译）时就固定了。
constexpr int P = 998244353;
using Z = MInt<P>;


struct Comb
{
    int n;
    vector<Z> _fac;//存储阶乘（Factorial）
    vector<Z> _invfac;//存储阶乘的逆元（Inverse Factorial）
    vector<Z> _inv;//存储单个数字的逆元（Inverse）

    Comb() : n{0}, _fac{1}, _invfac{1},_inv{0} {}
    //“委托构造函数”（Delegating Constructor）。
    //在执行 Comb(int n) 之前，它会先去调用那个不带参数的构造函数 Comb()。先进行初始化操作
    //等到上面的“初始状态”设置好后，它才会执行大括号里的内容，即调用 init(n) 去真正分配内存并计算 1 到 n 的阶乘
    Comb(int n) : Comb()
    {
        init(n);
    }
    void init(int m)
    {
        //为什么要取 min？ 因为在模 P 的运算中，如果 i = P，那么 i == 0 (mod P)。零是没有逆元的。所以预处理最多只能做到 P-1。//而这应该也是m的上界
        m = min(m, Z::getMod() - 1);
        //如果请求的长度还没有当前已经处理好的长度长，就直接返回，避免重复劳动。
        if(m <= n)
            return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m;i++)
        {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();// 唯一一次快速幂先算出最大数 m 的逆元。然后倒着推
        for (int i = m; i > n;i--)
        {
            //1 / (i-1)! = 1 / i! * i
            _invfac[i - 1] = _invfac[i] * i;
            // 1 / i! * (i - 1)! = 1 / i
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    //if判断表明不需要一开始就知道题目最大的 N 是多少。如果你查询了超出当前预处理范围的数，它会自动扩容到原来的 2 倍，非常智能。
    //所以我们往往制药建立一个Comb实例然后去访问就行了
    Z fac(int m)
    {
        if(m > n)
            init(2 * m);
        return _fac[m];
    }
    Z invfac(int m)
    {
        if(m > n)
            init(2 * m);
        return _invfac[m];
    }
    Z inv(int m)
    {
        if(m > n)
            init(2 * m);
        return _inv[m];
    }
    Z binom(int n,int m)
    {
        if(n < m || m < 0)
            return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
};