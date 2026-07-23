#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using ld = long double;
typedef pair<int, int> pii;
constexpr ld eps = 1e-12;
constexpr ld PI = 3.1415926535897932384l;

using point_t = ld;

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
    T operator*(const point &a) const { return x * a.x + y * a.y; }
    T operator^(const point &a) const { return x * a.y - y * a.x; }
    int toleft(const point &a) const { const auto t = (*this) ^ a; return (t > eps) - (t < -eps);}
    T len2() const { return (*this) * (*this); }
    T dis2(const point &a) const { return (a - (*this)).len2(); }

    ld len() const { return sqrtl(len2()); }
    ld dis(const point &a) const { return sqrtl(dis2(a)); }
    ld ang(const point &a) const { return acosl(max(-1.0l, min(1.0l, ((*this) * a) / (len() * a.len())))); }
    point rot(const ld rad) const { return {x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)}; }
    point rot(const ld cosr, const ld sinr) const { return {x * cosr - y * sinr, x * sinr + y * cosr}; }
};

using Point = point<point_t>;

// std::sort(pts.begin(), pts.end(), Polar::cmp);
namespace Polar
{
    inline int quad(const Point &a)
    {
        if(a.y < -eps) return 1;
        if(a.y > eps) return 4;
        if(a.x < -eps) return 5;
        if(a.x > eps)  return 3;
        return 2;
    }

    inline bool cmp(const Point &a, const Point &b)
    {
        int qa = quad(a), qb = quad(b);
        if(qa != qb)
            return qa < qb;
        const auto t = a ^ b;
        if (abs(t) <= eps) return a.len2() < b.len2() - eps; 
        else return t > eps;
    }
}

template<typename T>
struct line
{
    point<T> p, v;
    line(point<T> p = {0,0}, point<T> v = {0,0}) : p(p), v(v) {}
    
    bool operator==(const line &a) const { return v.toleft(a.v) == 0 && v.toleft(p - a.p) == 0; }
    int toleft(const point<T> &a) const { return v.toleft(a - p); }
    bool operator<(const line &a) const
    {
        if(abs(v ^ a.v) <= eps && v * a.v >= -eps)
            return toleft(a.p) == -1;
        return Polar::cmp(v, a.v);
    }

    // using ld
    point<T> inter(const line &a) const { return p + v * ((a.v ^ (p - a.p)) / (v ^ a.v)); }
    ld dis(const point<T> &a) const { return abs(v ^ (a - p)) / v.len(); }
    point<T> proj(const point<T> &a) const { return p + v * ((v * (a - p)) / (v * v)); }
};

using Line = line<point_t>;

template<typename T>
struct segment
{
    point<T> a, b;

    bool operator<(const segment &s) const { return make_pair(a, b) < make_pair(s.a, s.b); }

    int is_on(const point<T> &p) const
    {
        if(p == a || p == b)
            return -1;

        return (p - a).toleft(p - b) == 0 && (p - a) * (p - b) < -eps;
    }   

    int is_inter(const line<T> &l) const
    {
        if (l.toleft(a) == 0 || l.toleft(b) == 0)
            return -1;

        return l.toleft(a) != l.toleft(b);
    }

    int is_inter(const segment<T> &s) const
    {
        if(is_on(s.a) || is_on(s.b) || s.is_on(a) || s.is_on(b))
            return -1;
        const line<T> l{a, b - a}, ls{s.a, s.b - s.a};
        return l.toleft(s.a) * l.toleft(s.b) == -1 && ls.toleft(a) * ls.toleft(b) == -1;
    }

    ld dis(const point<T> &p) const
    {
        if((p - a) * (b - a) < -eps || (p - b) * (a - b) < -eps)
            return min(p.dis(a), p.dis(b));
        const line<T> l(a, b - a);
        return l.dis(p);
    }

    ld dis(const segment<T> &s) const
    {
        if(is_inter(s))
            return 0;

        return min({dis(s.a),dis(s.b),s.dis(a),s.dis(b)});
    }
};

using Segment = segment<point_t>;

template<typename T> 
struct polygon
{
    vector<point<T>> p;
    int nxt(const int i) const { return i == (int)p.size() - 1 ? 0 : i + 1; }
    int pre(const int i) const { return i == 0 ? (int)p.size() - 1 : i - 1; }

    T area() const
    {
        T sum = 0;
        for (int i = 0; i < p.size();i++)
            sum += p[i] ^ p[nxt(i)];
        return sum;
    }

    ld circ() const
    {
        ld sum = 0;
        for (int i = 0;i < p.size();i++)
            sum += p[i].dis(p[nxt(i)]);
        return sum;
    }

    pair<bool, int> winding(const point<T> &a) const
    {
        int cnt = 0;
        for (int i = 0; i < p.size();i++)
        {
            const point<T> u = p[i], v = p[nxt(i)];
            if(abs((a - u) ^ (a - v)) <= eps && (a - u) * (a - v) <= eps)
                return {true, 0};
            if(abs(u.y - v.y) <= eps)
                continue;
            const Line uv = {u, v - u};
            if(u.y < v.y - eps && uv.toleft(a) <= 0)
                continue;
            if(u.y > v.y + eps && uv.toleft(a) >= 0)
                continue;
            if(u.y < a.y - eps && v.y >= a.y - eps)
                cnt++;
            if(u.y >= a.y - eps && v.y < a.y - eps)
                cnt--;
        }
        return {false, cnt};
    }
};

using Polygon = polygon<point_t>;

template<typename T> 
struct convex : polygon<T>
{
    convex operator+(const convex &c) const
    {
        const vector<point<T>> &p = this->p;
        vector<Segment> e1(p.size()), e2(c.p.size()), edge(p.size() + c.p.size());
        vector<point<T>> res;
        res.reserve(p.size() + c.p.size());
        const auto cmp = [](const Segment &u, const Segment &v) -> bool
        {
            return Polar::cmp(u.b - u.a, v.b - v.a);
        };

        for (int i = 0; i < p.size();i++)
            e1[i] = {p[i], p[this->nxt(i)]};
        for (int i = 0; i < c.p.size();i++)
            e2[i] = {c.p[i], c.p[c.nxt(i)]};

        rotate(e1.begin(), min_element(e1.begin(), e1.end(), cmp), e1.end());
        rotate(e2.begin(), min_element(e2.begin(), e2.end(), cmp), e2.end());
        merge(e1.begin(), e1.end(), e2.begin(), e2.end(), edge.begin(), cmp);
        
        const auto check = [](const vector<point<T>> &res, const point<T> &u) -> bool
        {
            const auto back1 = res.back(), back2 = *prev(res.end(), 2);
            return (back1 - back2).toleft(u - back1) == 0 && (back1 - back2) * (u - back1) >= -eps;
        };

        auto u = e1[0].a + e2[0].a;
        for(const auto &v : edge)
        {
            while(res.size() > 1 && check(res, u))
                res.pop_back();
            res.push_back(u);
            u = u + v.b - v.a;
        }
        if(res.size() > 1 && check(res, res[0]))
            res.pop_back();
        return {res};
    }
    
    // guarantee that n > 2
    template<typename F>
    void rotcaliper(const F &func) const
    {
        const auto &p = this->p;
        const auto area = [](const point<T> &u, const point<T> &v, const point<T> &w) { return (w - u) ^ (w - v); };

        for (int i = 0, j = 1; i < p.size();i++)
        {
            const auto nxti = this->nxt(i);
            while(area(p[this->nxt(j)], p[i], p[nxti]) >= area(p[j], p[i], p[nxti]))
                j = this->nxt(j);
            func(p[i], p[nxti], p[j]);
        }
    } 

    // guarantee that n > 2
    template<typename F>
    void rotcaliperRec(const F &func) const
    {
        const auto &p = this->p;
        const auto area = [](const point<T> &u, const point<T> &v, const point<T> &w) {return (w - u) ^ (w - v);};
        const auto dot = [](const point<T> &u, const point<T> &v, const point<T> &w) {return (w - v) * (u - v);};

        for (int i = 0, j = 1, l = 1, r = 1; i < p.size();i++)
        {
            const auto nxti = this->nxt(i);
            while(area(p[this->nxt(j)], p[i], p[nxti]) >= area(p[j], p[i], p[nxti]))
                j = this->nxt(j);

            while(dot(p[this->nxt(r)], p[i], p[nxti]) >= dot(p[r], p[i], p[nxti]))
                r = this->nxt(r);

            if(i == 0)
                l = r;

            while(dot(p[this->nxt(l)], p[i], p[nxti]) <= dot(p[l], p[i], p[nxti]))
                l = this->nxt(l);

            func(p[i], p[nxti], p[j], p[r], p[l]);
        }
    }

    int is_in(const point<T> &a) const
    {
        const auto &p = this->p;
        if(p.size() == 0)
            return 0;
        if(p.size() == 1)
            return a == p[0] ? -2 : 0;
        if(p.size() == 2)
        {
            if(a == p[0] || a == p[1])
                return -2;
            return segment<T>{p[0], p[1]}.is_on(a) == 1 ? -1 : 0;
        }
        if(a == p[0])
            return -2;
        if((p[1] - p[0]).toleft(a - p[0]) == -1 || (p.back() - p[0]).toleft(a - p[0]) == 1)
            return 0;

        const auto cmp = [&](const point<T> &u, const point<T> &v)
        {
            return (u - p[0]).toleft(v - p[0]) == 1;
        };

        const int i = lower_bound(p.begin() + 1, p.end(), a, cmp) - p.begin();

        if(i == p.size())
            return 0;
        if(a == p[i] || a == p[this->pre(i)])
            return -2;
        if(i == 1)
            return segment<T>{p[0], p[i]}.is_on(a) == 1 ? -1 : 0;
        if(i == p.size() - 1 && segment<T>{p[0], p[i]}.is_on(a) == 1)
            return -1;
        if(segment<T>{p[i - 1], p[i]}.is_on(a) == 1)
            return -1;
        return (p[i] - p[i - 1]).toleft(a - p[i - 1]) > 0;
    }
    
    int relation(const line<T> &l) const
    {
        const auto &p = this->p;
        const int n = p.size();

        if(n == 0)
            return 0;

        if(n <= 2)
        {
            int pos = 0, neg = 0, on = 0;
            for(auto &u : p)
            {
                const int s = l.toleft(u);
                pos |= s > 0;
                neg |= s < 0;
                on |= s == 0;
            }

            if(pos && neg)
                return 1;
            if(on)
                return -1;
            return 0;
        }

        const auto [i, j] = tangent(l);
        const int si = l.toleft(p[i]);
        const int sj = l.toleft(p[j]);

        if(si * sj < 0)
            return 1;
        if(si == 0 || sj == 0)
            return -1;
        return 0;
    }

    int relation(const segment<T> &s) const
    {
        const auto &p = this->p;
        const int n = p.size();

        if(n == 0)
            return 0;
        if(n == 1)
            return s.is_on(p[0]) ? -1 : 0;
        if(n == 2)
            return s.is_inter(segment<T>{p[0], p[1]}) ? -1 : 0;

        if(s.a == s.b)
            return is_in(s.a);

        const line<T> l{s.a, s.b - s.a};
        const int lineRelation = relation(l);
        if(lineRelation == 0)
            return 0;

        if(lineRelation == -1)
        {
            const auto [i, j] = tangent(l);
            const auto touch = [&](const int u) -> bool
            {
                if(l.toleft(p[u]) != 0)
                    return false;

                if(s.is_on(p[u]))
                    return true;

                const int prev = this->pre(u);
                const int nxt = this->nxt(u);

                if (l.toleft(p[prev]) == 0)
                {
                    const segment<T> edge{p[prev], p[u]};
                    if(s.is_inter(edge))
                        return true;
                }

                if (l.toleft(p[nxt]) == 0)
                {
                    const segment<T> edge{p[u], p[nxt]};
                    if(s.is_inter(edge))
                        return true;
                }
                return false;
            };
            return touch(i) || touch(j) ? -1 : 0;
        }

        auto [mx, mn] = tangent(l);
        if(l.toleft(p[mx]) < l.toleft(p[mn]))
            swap(mx, mn);

        const auto indexAt = [&](const int start, const int step, const int k)
        {
            int index = (start + 1ll * step * k) % n;
            if(index < 0)
                index += n;
            return index;
        };

        const auto findCrossingEdge = [&](const int step) -> pii
        {
            int len;
            if(step == 1)
                len = (mn - mx + n) % n;
            else
                len = (mx - mn + n) % n;

            int lo = 0;
            int hi = len;
            while(lo + 1 < hi)
            {
                int m = lo + hi >> 1;
                int id = indexAt(mx, step, m);

                if(l.toleft(p[id]) > 0)
                    lo = m;
                else
                    hi = m;
            }
            return pii{indexAt(mx, step, lo), indexAt(mx, step, hi)};
        };

        const auto [u1, v1] = findCrossingEdge(1);
        const auto [u2, v2] = findCrossingEdge(-1);

        const auto intersec = [&](const int u, const int v) -> ld
        {
            const point<T> edge = p[v] - p[u];
            const point<T> dir = s.b - s.a;
            const ld num = static_cast<ld>((p[u] - s.a) ^ edge);
            const ld den = static_cast<ld>(dir ^ edge);
            return num / den;
        };

        ld t1 = intersec(u1, v1);
        ld t2 = intersec(u2, v2);
        if(t1 > t2)
            swap(t1, t2);
        const ld left = max<ld>(0, t1);
        const ld right = min<ld>(1, t2);
        if(left < right - eps)
            return 1;
        if(left <= right + eps)
            return -1;
        return 0;
    }

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

    template<typename F>
    int extreme(const F &dir) const
    {
        const auto &p = this->p;
        const auto check = [&](const int i)
        {
            return dir(p[i]).toleft(p[this->nxt(i)] - p[i]) >= 0;
        };

        const auto dir0 = dir(p[0]);;
        const auto check0 = check(0);

        if(!check0 && check(p.size() - 1))
            return 0;

        const auto cmp = [&](const point<T> &v)
        {
            const int vi = &v - p.data();
            if(vi == 0)
                return 1;
            const auto checkv = check(vi);
            const auto t = dir0.toleft(v - p[0]);
            if(vi == 1 && checkv == check0 && t == 0)
                return 1;
            return checkv ^ (checkv == check0 && t <= 0);
        };
        return partition_point(p.begin(), p.end(), cmp) - p.begin();
    }

    // promise that a is not "on" or "inside" the convex
    pii tangent(const point<T> &a) const 
    {
        const int i = extreme([&](const point<T> &u){return u - a;});
        const int j = extreme([&](const point<T> &u){return a - u;});
        return {i, j};
    }

    pii tangent(const line<T> &a) const 
    {
        const int i = extreme([&](const auto &){return a.v;});
        const int j = extreme([&](const auto &){return -a.v;});
        return {i, j};
    }
};

using Convex = convex<point_t>;

Convex convexhull(vector<Point> p)
{
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());

    if(p.size() <= 2)
        return {p};

    vector<Point> st;
    const auto check = [](const vector<Point> &st, const Point &u)
    {
        const auto back1 = st.back(), back2 = *prev(st.end(), 2);
        return (back1 - back2).toleft(u - back1) <= 0;
    };

    for(const Point &u : p)
    {
        while(st.size() > 1 && check(st, u))
            st.pop_back();
        st.push_back(u);
    }

    int k = st.size();
    p.pop_back();
    reverse(p.begin(), p.end());

    for(const Point &u : p)
    {
        while(st.size() > k && check(st, u))
            st.pop_back();
        st.push_back(u);
    }

    st.pop_back();
    return {st};
}

// guarantee using i64
// ********************
// the x and y have been multiplied by 3 inside the struct
// ********************
template<typename T>
struct dynamicHull
{
    struct Cmp
    {
        point<T> C;
        int quad(const point<T> &p) const
        {
            point<T> a = p - C;
            if(a.y < 0) return 1;
            if(a.y > 0) return 4;
            if(a.x < 0) return 5;
            if(a.x > 0) return 3;
            return 2;
        }

        bool operator()(const point<T> &a, const point<T> &b) const
        {
            int qa = quad(a), qb = quad(b);
            if(qa != qb)
                return qa < qb;

            T t = (a - C) ^ (b - C);
            if(t == 0)
                return (a - C).len2() < (b - C).len2();
            else
                return t > 0;
        }
    };
    set<point<T>, Cmp> s;

    dynamicHull() {}

    void init(point<T> p1, point<T> p2, point<T> p3)
    {
        p1 = p1 * 3, p2 = p2 * 3, p3 = p3 * 3;
        point<T> C = (p1 + p2 + p3) / 3;
        s = set<point<T>, Cmp>(Cmp{C});
        s.insert(p1);
        s.insert(p2);
        s.insert(p3);
    }

    auto nxt(typename set<point<T>, Cmp>::iterator it)
    {
        auto nx = next(it);
        return nx == s.end() ? s.begin() : nx;
    }

    auto pre(typename set<point<T>, Cmp>::iterator it)
    {
        return it == s.begin() ? prev(s.end()) : prev(it);
    }

    bool is_in(point<T> P)
    {
        if(s.size() < 3)
            return false;

        P = P * 3;
        auto it = s.lower_bound(P);
        auto R = (it == s.end() ? s.begin() : it);
        auto L = pre(R);
        return ((*R - *L) ^ (P - *L)) >= 0;
    }

    void add(point<T> P)
    {
        if(is_in(P))
            return;

        P = P * 3;
        auto it = s.insert(P).first;

        auto nx = nxt(it);
        while(s.size() > 3)
        {
            auto nnx = nxt(nx);
            if(((*nx - *it) ^ (*nnx - *nx)) <= 0)
            {
                s.erase(nx);
                nx = nnx;
            }
            else
                break;
        }

        auto pv = pre(it);
        while(s.size() > 3)
        {
            auto ppv = pre(pv);
            if(((*pv - *ppv) ^ (*it - *pv)) <= 0)
            {
                s.erase(pv);
                pv = ppv;
            }
            else
                break;
        }
    }
};

using DynamicHull = dynamicHull<i64>;

struct Circle
{
    Point c;
    ld r;
    bool operator==(const Circle &a) const { return c == a.c && abs(r - a.r) <= eps; }
    ld circ() const { return 2 * PI * r; }
    ld area() const { return PI * r * r; }

    int is_in(const Point &p) const 
    { 
        const ld d = p.dis(c);
        return abs(d - r) <= eps ? -1 : d < r - eps;
    }

    int relation(const Line &l) const
    {
        const ld d = l.dis(c);
        if(d > r + eps)
            return 0;
        if(abs(d - r) <= eps)
            return 1;
        return 2;
    }

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

    vector<Point> inter(const Line &l) const
    {
        const ld d = l.dis(c);
        const Point p = l.proj(c);
        const int t = relation(l);
        if(t == 0)
            return vector<Point>();
        if(t == 1)
            return vector<Point>{p};
        const ld k = sqrtl(max(0.0L, r * r - d * d)); 
        return vector<Point>{p - (l.v / l.v.len()) * k, p + (l.v / l.v.len()) * k};
    }

    vector<Point> inter(const Circle &a) const
    {
        const ld d = c.dis(a.c);
        const int t = relation(a);
        if(t == -1 || t == 0 || t == 4)
            return vector<Point>();
        Point e = a.c - c;
        e = e / e.len() * r;
        if(t == 1 || t == 3)
        {
            if(r * r + d * d - a.r * a.r >= -eps)
                return vector<Point>{c + e};
            return vector<Point>{c - e};
        }

        const ld costh = (r * r + d * d - a.r * a.r) / (2 * r * d);
        const ld sinth = sqrtl(max(0.0L, 1.0L - costh * costh)); 
        return vector<Point>{c + e.rot(costh, -sinth), c + e.rot(costh, sinth)};
    }

    vector<Line> tangent(const Point &a) const
    {
        const int t = is_in(a);
        if(t == 1)
            return vector<Line>();
        if(t == -1)
        {
            const Point v = {-(a - c).y, (a - c).x};
            return vector<Line>{{a, v}};
        }
        Point e = a - c;
        e = e / e.len() * r;
        const ld costh = r / c.dis(a), sinth = sqrtl(1 - costh * costh);
        const Point t1 = c + e.rot(costh, -sinth), t2 = c + e.rot(costh, sinth);
        return vector<Line>{{a, t1 - a}, {a, t2 - a}};
    }

    tuple<int, Circle, Line> inverse(const Line &l) const 
    {
        const Circle nullC = {{0., 0.}, 0.};
        const Line nullL = {{0., 0.}, {0., 0.}};
        if(l.toleft(c) == 0)
            return {2, nullC, l};
        const Point v = l.toleft(c) == 1 ? Point{l.v.y, -l.v.x} : Point{-l.v.y, l.v.x};
        const ld d = r * r / l.dis(c);
        const Point p = c + v / v.len() * d;
        return {1, {(c + p) / 2, d / 2}, nullL};
    }

    tuple<int, Circle, Line> inverse(const Circle &a) const
    {
        const Circle nullC = {{0., 0.}, 0.};
        const Line nullL = {{0., 0.}, {0., 0.}};
        const Point v = a.c - c;
        if(a.is_in(c) == -1)
        {
            const ld d = r * r / (a.r + a.r);
            const Point p = c + v / v.len() * d;
            return {2, nullC, {p, {-v.y, v.x}}};
        }
        if(c == a.c)
            return {1, {c, r * r / a.r}, nullL};
        const ld d1 = r * r / (c.dis(a.c) - a.r), d2 = r * r / (c.dis(a.c) + a.r);
        const Point p = c + v / v.len() * d1, q = c + v / v.len() * d2;
        return {1, {(p + q) / 2, p.dis(q) / 2}, nullL};
    }
};

vector<Line> halfinter(vector<Line> l, const point_t lim = 1e9)
{
    const auto check = [](const Line &a, const Line &b, const Line &c) -> bool { return a.toleft(b.inter(c)) < 0; };

    // const auto check = [](const Line &a, const Line &b, const Line &c) -> bool
    // {
    //     const Point p = a.v * (b.v ^ c.v), q = b.p * (b.v ^ c.v) + b.v * (c.v ^ (b.p - c.p)) - a.p * (b.v ^ c.v);
    //     return p.toleft(q) < 0;
    // };

    l.push_back({{-lim, 0}, {0, -1}});
    l.push_back({{0, -lim}, {1, 0}});
    l.push_back({{lim, 0}, {0, 1}});
    l.push_back({{0, lim}, {-1, 0}});
    sort(l.begin(), l.end());
    deque<Line> q;
    for (int i = 0; i < l.size();i++)
    {
        if (i > 0 && l[i - 1].v.toleft(l[i].v) == 0 && l[i - 1].v * l[i].v > eps)
            continue;
        while(q.size() > 1 && check(l[i], q.back(), q[q.size() - 2]))
            q.pop_back();
        while(q.size() > 1 && check(l[i], q[0], q[1]))
            q.pop_front();
        if(!q.empty() && q.back().v.toleft(l[i].v) <= 0)
            return vector<Line>();
        q.push_back(l[i]);
    }
    while(q.size() > 1 && check(q[0], q.back(), q[q.size() - 2]))
        q.pop_back();
    while(q.size() > 1 && check(q.back(), q[0], q[1]))
        q.pop_front();
    return vector<Line>(q.begin(), q.end());
}
