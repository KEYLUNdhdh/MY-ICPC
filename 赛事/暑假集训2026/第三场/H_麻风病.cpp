#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";       \
    cerr << "\n";           \
}
#define cutline { cerr << "----------------------\n"; }
using namespace std;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
using db = double;
typedef pair<int, int> pii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;
constexpr ld eps = 1e-12;
constexpr ld PI = 3.1415926535897932384l;

using point_t = i64;

template<typename T> 
struct point
{
    T x, y;
    int id;
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

using Point = point<i64>;

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

    struct S
    {
        i64 s;
        int id1, id2, id3;
        bool operator>(const S &b) const
        {
            return s > b.s;
        }
    };
    int n;
    
    set<point<T>, Cmp> s;
    priority_queue<S, vector<S>, greater<S>> pq;
    dynamicHull() {}

    void init(point<T> p1, point<T> p2, point<T> p3)
    {
        p1.x *= 3;
        p1.y *= 3;
        p2.x *= 3;
        p2.y *= 3;
        p3.x *= 3;
        p3.y *= 3;
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

        auto it = s.lower_bound(P);
        auto R = (it == s.end() ? s.begin() : it);
        auto L = pre(R);
        return ((*R - *L) ^ (P - *L)) >= 0;
    }

    void add(point<T> P)
    {
        P.x *= 3;
        P.y *= 3;
        auto it = s.insert(P).first;
    }

    void initpq()
    {
        auto it = s.begin();
        for (int i = 1; i <= n;i++)
        {
            auto pv = pre(it);
            auto nx = nxt(it);
            pq.push({abs((*pv - *it) ^ (*nx - *it)), (*pv).id, (*nx).id, (*it).id});
            it++;
        }
    }
    void del(point<T> P)
    {
        P.x *= 3;
        P.y *= 3;

        auto it = s.lower_bound(P);
        auto pv = pre(it);
        auto nx = nxt(it);
        auto nnx = nxt(nx);
        auto ppv = pre(pv);
        pq.push({abs((*pv - *nx) ^ (*ppv - *pv)), (*ppv).id, (*nx).id, (*pv).id});
        pq.push({abs((*pv - *nx) ^ (*nnx - *nx)), (*pv).id, (*nnx).id, (*nx).id});
        s.erase(it);
    }
};

using DynamicHull = dynamicHull<i64>;

void solve()
{
    int n;
    cin >> n;
    vector<int> vis(n + 1, 0);

    vector<Point> pts(n + 1);
    for (int i = 1; i <= n;i++)
        cin >> pts[i].x >> pts[i].y, pts[i].id = i;

    DynamicHull dh;
    dh.n = n;
    dh.init(pts[1], pts[2], pts[3]);
    for (int i = 4; i <= n;i++)
        dh.add(pts[i]);
    dh.initpq();
    int turn;
    if(n % 2 == 0)
        cout << "Alberto" << endl, turn = 0;
    else
        cout << "Beatrice" << endl, turn = 1;

    for (int k = n - 2; k >= 1;k--)
    {
        if(turn == 1)
        {
            int q;
            cin >> q;
            dh.del(pts[q]);
            vis[q] = 1;
            turn ^= 1;
        }
        else
        {
            turn ^= 1;
            DynamicHull::S k;
            while(!dh.pq.empty())
            {
                auto [s, id1, id2, id3] = dh.pq.top();
                dh.pq.pop();
                if(vis[id1] || vis[id2] || vis[id3])
                    continue;
                else
                {
                    k = {s, id1, id2, id3};
                    break;
                }
            }
            auto &[s, id1, id2, id3] = k;
            vis[id3] = 1;
            dh.del(pts[id3]);
            cout << id3 << endl;
        }
    }
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    while(T--)
        solve();
    return 0;
}