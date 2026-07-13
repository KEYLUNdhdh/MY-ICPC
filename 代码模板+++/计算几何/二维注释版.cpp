#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using ld = long double;

constexpr ld eps = 1e-12;
constexpr ld PI=3.1415926535897932384l;

// atan2(|a ^ b|, a * b)  直接获取两个向量的夹角，精度较高。
// 方便更改全局的数据类型
using point_t = ld;
// 点与向量
template<typename T> 
struct point
{
    T x, y;
    bool operator==(const point &a) const {return (abs(x - a.x) < eps && abs(y - a.y) < eps);}
    bool operator<(const point &a) const {if(abs(x - a.x) <= eps) return y < a.y - eps; return x < a.x - eps;}
    bool operator>(const point &a) const { return !(*this < a || *this == a); }
    point operator+(const point &a) const { return {x + a.x, y + a.y}; }
    point operator-(const point &a) const { return {x - a.x, y - a.y}; }
    point operator-() const { return {-x, -y}; }
    point operator*(const T k) const { return {k * x, k * y}; }
    point operator/(const T k) const { return {x / k, y / k}; }
    T operator*(const point &a) const { return x * a.x + y * a.y; }// 点积
    T operator^(const point &a) const { return x * a.y - y * a.x; }// 叉积，注意优先级

    // 当你调用 A.toleft(B) 时：
    // 返回 1：说明 B 在 A 的左侧。
    // 返回 -1：说明 B 在 A 的右侧。
    // 返回 0：说明两向量共线。
    int toleft(const point &a) const { const auto t = (*this) ^ a; return (t > eps) - (t < -eps);}// to-left 测试

    T len2() const { return (*this) * (*this); }// 向量长度的平方
    T dis2(const point &a) const { return (a - (*this)).len2(); }// 两点距离的平方

    // 涉及浮点数
    ld len() const { return sqrtl(len2()); }// 向量长度
    ld dis(const point &a) const { return sqrtl(dis2(a)); }// 两点距离
    ld ang(const point &a) const { return acosl(max(-1.0l, min(1.0l, ((*this) * a) / (len() * a.len())))); }// 向量夹角, 返回的是 cos 的值
    point rot(const ld rad) const { return {x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)}; }// 逆时针旋转（给定角度）
    point rot(const ld cosr, const ld sinr) const { return {x * cosr - y * sinr, x * sinr + y * cosr}; } // 逆时针旋转（给定角度的正弦与余弦）
};

using Point = point<point_t>;

// std::sort(pts.begin(), pts.end(), Polar::cmp);
namespace Polar
{
    // 获取点所在的宏观区域（象限/坐标轴划分）
    inline int quad(const Point &a)
    {
        if(a.y < -eps) return 1; // 下半平面
        if(a.y > eps) return 4;  // 上半平面 
        if(a.x < -eps) return 5; // X 轴负半轴
        if(a.x > eps)  return 3; // X 轴正半轴
        return 2;                // 原点
    }

     // 极角排序核心比较函数
    inline bool cmp(const Point &a, const Point &b)
    {
        int qa = quad(a), qb = quad(b);
        // 1. 如果不在同一个宏观区域，直接按区域优先级排序
        if(qa != qb)
            return qa < qb;
        // 2. 如果在同一个区域内，利用叉积判断精确的相对左右位置
        const auto t = a ^ b;

        // 3. 如果极角完全相同（共线），按到原点的距离升序排列
        // 利用了之前模板里的 len2() 函数，避免了直接相乘的歧义
        if (abs(t) <= eps) return a.len2() < b.len2() - eps; 
        else return t > eps;
    }
}

// 直线
template<typename T>
struct line
{
    point<T> p, v;// p 为直线上一点，v 为方向向量

    bool operator==(const line &a) const { return v.toleft(a.v) == 0 && v.toleft(p - a.p) == 0; }
    int toleft(const point<T> &a) const { return v.toleft(a - p); }// to-left 测试
    bool operator<(const line &a) const // 半平面交算法定义的排序
    {
        if(abs(v ^ a.v) <= eps && v * a.v >= -eps)
            return toleft(a.p) == -1;
        return Polar::cmp(v, a.v);
    }

    // 涉及浮点数
    // 保证 T 一定要是浮点数
    // using ld
    point<T> inter(const line &a) const { return p + v * ((a.v ^ (p - a.p)) / (v ^ a.v)); }// 直线交点
    ld dis(const point<T> &a) const { return abs(v ^ (a - p)) / v.len(); }// 点到直线距离
    point<T> proj(const point<T> &a) const { return p + v * ((v * (a - p)) / (v * v)); } // 点在直线上的投影
};

using Line = line<point_t>;

//线段
template<typename T>
struct segment
{
    point<T> a, b;

    bool operator<(const segment &s) const { return make_pair(a, b) < make_pair(s.a, s.b); }

    // 判定性函数建议在整数域使用

    // 判断点是否在线段上
    // -1 点在线段端点 | 0 点不在线段上 | 1 点严格在线段上
    int is_on(const point<T> &p) const
    {
        if(p == a || p == b)
            return -1;

        return (p - a).toleft(p - b) == 0 && (p - a) * (p - b) < -eps;
    }   

    // 判断线段直线是否相交
    // -1 直线经过线段端点 | 0 线段和直线不相交 | 1 线段和直线严格相交
    int is_inter(const line<T> &l) const
    {
        if (l.toleft(a) == 0 || l.toleft(b) == 0)
            return -1;

        return l.toleft(a) != l.toleft(b);
    }

    // 判断两线段是否相交
    // -1 在某一线段端点处相交 | 0 两线段不相交 | 1 两线段严格相交
    int is_inter(const segment<T> &s) const
    {
        if(is_on(s.a) || is_on(s.b) || s.is_on(a) || s.is_on(b))
            return -1;
        const line<T> l{a, b - a}, ls{s.a, s.b - s.a};
        return l.toleft(s.a) * l.toleft(s.b) == -1 && ls.toleft(a) * ls.toleft(b) == -1;
    }

    // 点到线段距离
    ld dis(const point<T> &p) const
    {
        if((p - a) * (b - a) < -eps || (p - b) * (a - b) < -eps)
            return min(p.dis(a), p.dis(b));
        const line<T> l(a, b - a);
        return l.dis(p);
    }

    // 两线段间距离
    ld dis(const segment<T> &s) const
    {
        if(is_inter(s))
            return 0;

        return min({dis(s.a),dis(s.b),s.dis(a),s.dis(b)});
    }
};

using Segment = segment<point_t>;

// 多边形
template<typename T> 
struct polygon
{
    vector<point<T>> p;// 以逆时针顺序存储
    int nxt(const int i) const { return i == (int)p.size() - 1 ? 0 : i + 1; }
    int pre(const int i) const { return i == 0 ? (int)p.size() - 1 : i - 1; }

    // 多边形面积的两倍
    // 可用于判断点的存储顺序是顺时针或逆时针
    T area() const
    {
        T sum = 0;
        for (int i = 0; i < p.size();i++)
            sum += p[i] ^ p[nxt(i)];
        return sum;
    }

    // 多边形的周长
    ld circ() const
    {
        ld sum = 0;
        for (int i = 0;i < p.size();i++)
            sum += p[i].dis(p[nxt(i)]);
        return sum;
    }

    // 回转数
    // 返回值第一项表示点是否在多边形边上
    // 对于狭义多边形，回转数为 0 表示点在多边形外，否则点在多边形内
    // 向右（+x 轴）发射水平射线的思想
    pair<bool, int> winding(const point<T> &a) const
    {
        int cnt = 0;// cnt 记录回转数，向上穿透射线+1，向下穿透射线-1。
        for (int i = 0; i < p.size();i++)
        {
            const point<T> u = p[i], v = p[nxt(i)];
            // 1. 【特判：点在多边形边界上】
            // (a - u) ^ (a - v) <= eps 说明点 a 和 u, v 共线 (叉积为0)
            // (a - u) * (a - v) <= eps 说明点 a 在 u 和 v 的中间 (点积<=0)
            // 如果点恰好在边界上，直接返回 {true, 0}，提前结束。
            if(abs((a - u) ^ (a - v)) <= eps && (a - u) * (a - v) <= eps)
                return {true, 0};

            // 2. 【过滤水平边】
            // 水平向右发射射线，与水平边要么不相交，要么重合，对回转数没有贡献，直接忽略。
            if(abs(u.y - v.y) <= eps)
                continue;

            const Line uv = {u, v - u}; // 构建从 u 指向 v 的有向边

            // 3. 【核心剪枝一：向上边】
            // 如果边向上走 (u.y < v.y)，向右发射的射线想要碰到它，点 a 必须在边的 左侧。
            // uv.toleft(a) <= 0 意味着点 a 在这条有向边的 右侧 (或在延长线上)。
            // 既然点已经在右侧了，向右发射射线只会越走越远，永远碰不到，直接跳过！
            if(u.y < v.y - eps && uv.toleft(a) <= 0)
                continue;

            // 4. 【核心剪枝二：向下边】
            // 如果边向下走 (u.y > v.y)。注意！对于向下的向量，“左侧”其实是物理坐标系的“右侧”。
            // uv.toleft(a) >= 0 意味着点 a 位于向下向量的 左侧 (即物理空间的右侧)。
            // 同样，点已经在右侧，射线向右打必空，直接跳过！
            if(u.y > v.y + eps && uv.toleft(a) >= 0)
                continue;
            
            // 5. 【区间判定：向上穿透】
            // 走到这里，说明点 a 必定在边的“左侧”，射线 必定 会和所在的直线相交！
            // 接下来只要判断射线 a.y 是否落在 [u.y, v.y) 所在的 Y 轴区间内。
            // 注意这里的逻辑构成了左开右闭区间 (下端点, 上端点]，完美避免了射线刚好打在顶点时被重复计算 2 次的 Bug。
            if(u.y < a.y - eps && v.y >= a.y - eps)
                cnt++;

            // 6. 【区间判定：向下穿透】
            // 同理，边向下走时，判断射线是否落在 (v.y, u.y] 区间内。向下穿透，回转数 -1。
            if(u.y >= a.y - eps && v.y < a.y - eps)
                cnt--;
        }
        // 返回 {是否在边界上, 回转数}
        // 如果 cnt != 0，说明点在多边形内部；cnt == 0 则在外部。
        return {false, cnt};
    }
};

using Polygon = polygon<point_t>;

//凸多边形
template<typename T> 
struct convex : polygon<T>
{
    // 旋转卡壳
    // 遍历凸包的每一条边，并找到距离这条边最远的顶点。
    // func 为更新答案的函数，可以根据题目调整注入的函数 [&]
    template<typename F>
    void  rotcaliper(const F &func) const
    {
        const auto &p = this->p;
        // 计算面积
        // 三角形面积越大，意味着顶点 p[j] 到这条底边的垂直距离（高）越大。
        const auto area = [](const point<T> &u, const point<T> &v, const point<T> &w) { return (w - u) ^ (w - v); };

        // 双指针 i 和 j
        // 外层 for 循环变量 i 在遍历凸包的每一条边（由 p[i] 和 p[nxti] 组成）。
        // 内层 while 循环变量 j 代表当前正在寻找的“最远顶点”。
        for (int i = 0, j = 1; i < p.size();i++)
        {
            const auto nxti = this->nxt(i);
            while(area(p[this->nxt(j)], p[i], p[nxti]) >= area(p[j], p[i], p[nxti]))
                j = this->nxt(j);
            func(p[i], p[nxti], p[j]);
        }
    } 

    // 旋转卡壳求最小矩形覆盖
    template<typename F>
    void rotcaliperRec(const F &func) const
    {
        const auto &p = this->p;
        // 辅助闭包：计算叉积 (用于求高度/面积)
        const auto area = [](const point<T> &u, const point<T> &v, const point<T> &w) {return (w - u) ^ (w - v);};
        // 辅助闭包：计算点积 (用于求在底边上的投影长度极值)
        const auto dot = [](const point<T> &u, const point<T> &v, const point<T> &w) {return (w - v) * (u - v);};

        // 维护 3 个极值点指针：j(最高), r(最右), l(最左)
        for (int i = 0, j = 1, l = 1, r = 1; i < p.size();i++)
        {
            const auto nxti = this->nxt(i);
            // 1. 卡最高点 (Top) - 叉积最大化
            while(area(p[this->nxt(j)], p[i], p[nxti]) >= area(p[j], p[i], p[nxti]))
                j = this->nxt(j);

            // 2. 卡最右点 (Right) - 底边正方向点积最大化
            while(dot(p[this->nxt(r)], p[i], p[nxti]) >= dot(p[r], p[i], p[nxti]))
                r = this->nxt(r);

            // 第一轮找最左点时，必须从最右点开始逆时针找，防止死循环
            if(i == 0)
                l = r;

            // 3. 卡最左点 (Left) - 点积最小化 (即负方向投影最大化)
            while(dot(p[this->nxt(l)], p[i], p[nxti]) <= dot(p[l], p[i], p[nxti]))
                l = this->nxt(l);

            // 把底边 (i, nxti) 和三个卡壳极值点全部丢给外层闭包处理
            func(p[i], p[nxti], p[j], p[r], p[l]);
        }
    }

    // 判断点是否在凸多边形内
    // 复杂度 O(logn)
    // -1 点在多边形边上 | 0 点在多边形外 | 1 点在多边形内
    int is_in(const point<T> &a) const
    {
        const auto &p = this->p;
        if(p.size() == 1) // 只有一个点
            return a == p[0] ? -1 : 0;
        if(p.size() == 2) // 只有两个点（一条线段）
            return segment<T>{p[0], p[1]}.is_on(a) ? -1 : 0;
        if(a == p[0]) // 点恰好和基准点（通常是左下角点）重合
            return -1;

        // 如果目标点 a 跑到了最右侧光线 p[0]->p[1] 的右边，或者跑到了最左侧光线 p[0]->p.back() 的左边，那它绝对不可能在多边形内部，直接返回 0。
        if((p[1] - p[0]).toleft(a - p[0]) == -1 || (p.back() - p[0]).toleft(a - p[0]) == 1)
            return 0;

        // 比较函数：判断向量 v 是否在向量 u 的严格左侧
        const auto cmp = [&](const point<T> &u, const point<T> &v)
        {
            return (u - p[0]).toleft(v - p[0]) == 1;
        };

        // 二分查找
        // 凸多边形的顶点是逆时针排列的，它们的极角在单调递增
        // 这里的lower_bound 传参顺序永远是 cmp(数组里的元素, 目标值)。（传入的就是点 a）
        // lower_bound 的官方定义是：寻找第一个使得 cmp(element, value) 返回 false 的元素
        // 当 lower_bound 拿着某个顶点 u 和点 a 问 cmp 时，cmp 会回答：
        // 返回 true：点 a 在射线 p[0] -> u 的严格左侧（极角比 u 大）。
        // 返回 false：点 a 在射线 p[0] -> u 的右侧或共线上（极角小于等于 u）。
        const int i = lower_bound(p.begin() + 1, p.end(), a, cmp) - p.begin();

        // 1. 如果锁定的边界是第一条边，判断是否落在这条边上
        if(i == 1)
            return segment<T>{p[0], p[i]}.is_on(a) ? -1 : 0;
        // 2. 如果锁定的边界是最后一条边，且刚好落在这条边上
        if(i == p.size() - 1 && segment<T>{p[0], p[i]}.is_on(a))
            return -1;
        // 3. 判断是否落在多边形外围的那条“封口边”上
        if(segment<T>{p[i - 1], p[i]}.is_on(a))
            return -1;

        // 4. 终极判断：在三角形内部吗？
        return (p[i] - p[i - 1]).toleft(a - p[i - 1]) > 0;
    }

    // 凸多边形的直径的平方
    T diamemter2() const
    {
        const auto &p = this->p;
        if(p.size() == 1)
            return 0;
        if(p.size() == 2)
            return p[0].dis2(p[1]);
        T ans = 0;
        auto func = [&](const point<T> &u, const point<T> &v, const point<T> &w)
        {
            ans = max({ans, w.dis2(u), w.dis2(v)});
        };
        rotcaliper(func);
        return ans;
    }
};

using Convex = convex<point_t>;

// 点集的凸包
// Andrew 算法，复杂度 O(nlogn)
Convex convexhull(vector<Point> p)
{
    // 1. 先进行排序和去重
     // 1. 排序：利用 point<T> 中重载的 operator< (先按 x，再按 y)
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());

    // 2. 在去重之后，再特判点数 <= 2 的情况！
    // （这不仅包含了 n=1, 2 的情况，也包含了 n=0 的空集情况，非常安全）
    if(p.size() <= 2)
        return {p};

    vector<Point> st;
    // 检查是否非左转（右转或共线：toleft <= 0）
    const auto check = [](const vector<Point> &st, const Point &u)
    {
        const auto back1 = st.back(), back2 = *prev(st.end(), 2);
        return (back1 - back2).toleft(u - back1) <= 0;
    };

    // 2. 求下凸壳
    for(const Point &u : p)
    {
        // 只要最新加入的点使得栈顶两个点所在的直线没有向左拐，就弹栈
        while(st.size() > 1 && check(st, u))
            st.pop_back();
        st.push_back(u);
    }

    int k = st.size();// 1. 记录下凸链的节点数量
    p.pop_back();// 2. 删掉排序后数组中最后一个点（它是最右侧的点，既属于下凸链也属于上凸链）
    reverse(p.begin(), p.end());// 3. 将剩余点集逆序

    // 3. 求上凸壳
    for(const Point &u : p)
    {
         // 注意这里的边界条件是 st.size() > k，防止把下凸壳的点弹掉
        while(st.size() > k && check(st, u))
            st.pop_back();
        st.push_back(u);
    }

    st.pop_back();// 终点（即下凸壳的起点）会被上凸壳再加入一次，需要弹出
    return {st};
}

// 圆
struct Circle
{
    Point c;
    ld r;
    bool operator==(const Circle &a) const { return c == a.c && abs(r - a.r) <= eps; }
    ld circ() const { return 2 * PI * r; } // 周长
    ld area() const { return PI * r * r; } // 面积

    // 点与圆的关系
    // -1 圆上 | 0 圆外 | 1 圆内
    int is_in(const Point &p) const 
    { 
        const ld d = p.dis(c);
        return abs(d - r) <= eps ? -1 : d < r - eps;
    }

    // 直线与圆关系
    // 0 相离 | 1 相切 | 2 相交
    int relation(const Line &l) const
    {
        const ld d = l.dis(c);
        if(d > r + eps)
            return 0;
        if(abs(d - r) <= eps)
            return 1;
        return 2;
    }

    // 圆与圆关系
    // -1 相同 | 0 相离 | 1 外切 | 2 相交 | 3 内切 | 4 内含
    int relation(const Circle &a) const
    {
        if(*this == a)
            return -1;
        const ld d = c.dis(a.c);
        if(d > r + a.r + eps)
            return 0;
        if(abs(d - r - a.r) <= eps)
            return 1;
        if(abs(d - abs(r - a.r)) <= eps)
            return 3;
        if(d < abs(r - a.r) - eps)
            return 4;
        return 2;
    }

    // 直线与圆的交点
    vector<Point> inter(const Line &l) const
    {
        const ld d = l.dis(c);
        const Point p = l.proj(c);
        const int t = relation(l);
        if(t == 0) // 相离
            return vector<Point>();
        if(t == 1) // 相切
            return vector<Point>{p};
        const ld k = sqrtl(max(0.0L, r * r - d * d)); // 求出单位向量应该倍增的模长
        return vector<Point>{p - (l.v / l.v.len()) * k, p + (l.v / l.v.len()) * k}; // 沿着单位向量走 k 大小的距离
    }

    // 圆与圆交点
    vector<Point> inter(const Circle &a) const
    {
        const ld d = c.dis(a.c);
        const int t = relation(a);
        if(t == -1 || t == 0 || t == 4) //相同，相离，内含
            return vector<Point>();

        // 构造指着另一个圆的圆心的，长度为 r 的向量。
        Point e = a.c - c;
        e = e / e.len() * r;
        if(t == 1 || t == 3) // 外切或者内切
        {
            // 余弦定理的分子部分
            // 当两圆外切，或者当前圆包含另一个圆（内切且 r > a.r）时，夹角为 0, 余弦大于 0
            if(r * r + d * d - a.r * a.r >= -eps)
                return vector<Point>{c + e};

            // 当前圆被另一个圆包含（内切且 r < a.r）时，交点 P 在向量 e 的反方向上, 夹角为 180， 余弦小于 0
            return vector<Point>{c - e};
        }

        // 余弦定理求旋转角度
        const ld costh = (r * r + d * d - a.r * a.r) / (2 * r * d);
        const ld sinth = sqrtl(max(0.0L, 1.0L - costh * costh)); 
        return vector<Point>{c + e.rot(costh, -sinth), c + e.rot(costh, sinth)};
    }
};

// 半平面交
// 排序增量法，复杂度 O(nlogn)
// 输入与返回值都是用直线表示的半平面集合
vector<Line> halfinter(vector<Line> l, const point_t lim = 1e9)
{
    // 判断直线 b 和 c 的交点，是否在直线 a 的右侧（外部）。
    const auto check = [](const Line &a, const Line &b, const Line &c) -> bool { return a.toleft(b.inter(c)) < 0; };

    // 无精度误差的方法，但注意取值范围会扩大到三次方
    // 所以会有溢出的风险
    // const auto check = [](const Line &a, const Line &b, const Line &c) -> bool
    // {
    //     const Point p = a.v * (b.v ^ c.v), q = b.p * (b.v ^ c.v) + b.v * (c.v ^ (b.p - c.p)) - a.p * (b.v ^ c.v);
    //     return p.toleft(q) < 0;
    // };

    // 在无穷远处（10^9）人为加上四个半平面，框出一个极大的正方形（逆时针包围）。
    // 保证所有半平面交的结果必定是一个封闭的凸多边形
    l.push_back({{-lim, 0}, {0, -1}});
    l.push_back({{0, -lim}, {1, 0}});
    l.push_back({{lim, 0}, {0, 1}});
    l.push_back({{0, lim}, {-1, 0}});

    // 所有直线按极角（与 x 轴的夹角）从小到大排序
    sort(l.begin(), l.end());
    deque<Line> q;

    for (int i = 0; i < l.size();i++)
    {
        // 1. 去重：如果两条线平行且同向，只保留最靠内侧的第一条
        if (i > 0 && l[i - 1].v.toleft(l[i].v) == 0 && l[i - 1].v * l[i].v > eps)
            continue;
        // 2. 队尾淘汰：新线切掉了队尾的角，队尾出局
        while(q.size() > 1 && check(l[i], q.back(), q[q.size() - 2]))
            q.pop_back();
        // 3. 队首淘汰：新线切掉了队首的角（因为极角是绕一圈的），队首出局
        while(q.size() > 1 && check(l[i], q[0], q[1]))
            q.pop_front();
        // 4. 空集特判：如果新线和队尾线方向夹角 >= 180度，且没被上面的 while 淘汰，
        // 说明它们构成了平行的反向半平面，或者背道而驰，此时半平面交必定为空集！
        if(!q.empty() && q.back().v.toleft(l[i].v) <= 0)
            return vector<Line>();
        // 5. 新线入队
        q.push_back(l[i]);
    }
    // 最后加入的几条线，可能会和最开始加入的第一条线（q[0]）发生切角冲突。
    while(q.size() > 1 && check(q[0], q.back(), q[q.size() - 2]))
        q.pop_back();
    while(q.size() > 1 && check(q.back(), q[0], q[1]))
        q.pop_front();
    return vector<Line>(q.begin(), q.end());
}


