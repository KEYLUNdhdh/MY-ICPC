#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;

const ld EPS = 1e-8;
const ld INF_DB = 1e100;

i128 abs(i128 x)
{
    return x < 0 ? -x : x;
}

i128 gcd(i128 a, i128 b) 
{
    a = abs(a);
    b = abs(b);
    while (b)
    {
        i128 t = a % b;
        a = b;
        b = t;
    }
    return a;
}

ostream &operator<<(ostream &os, i128 n) {
    string s;
    int f = 0;
    if(n == 0)
        s = "0";
    if(n < 0)
    {
        f = 1;
        n = -n;
    }
    while (n) {
        s += '0' + n % 10;
        n /= 10;
    }
    reverse(s.begin(), s.end());
    if(f)
        s = '-' + s;
    return os << s;
}

istream &operator>>(istream &is,i128& n)
{
    n = 0;
    string s;
    is >> s;
    int sign = 1, start = 0;
    if(s[0] == '-')
    {
        sign = -1;
        start = 1;
    }
    for (int i = start; i < s.size();i++)
    {
        n = n * 10 + s[i] - '0';
    }
    n *= sign;
    return is;
}

struct Frac
{
    i128 num;
    i128 den;
    
    Frac(i128 num_ = 0, i128 den_ = 1) : num(num_), den(den_)
    {
        normalize();
    }

    void normalize() 
    {
        if (den < 0)
        {
            num = -num;
            den = -den;
        }

        i128 g = gcd(num, den);

        if (g)
        {
            num /= g;
            den /= g;
        }
    }

    explicit operator ld() const
    {
        return (ld)num / (ld)den;
    }
    
    Frac &operator+=(const Frac &rhs)
    {
        num = num * rhs.den + rhs.num * den;
        den *= rhs.den;
        normalize(); 
        return *this;
    }
    Frac &operator-=(const Frac &rhs)
    {
        num = num * rhs.den - rhs.num * den;
        den *= rhs.den;
        normalize(); 
        return *this;
    }
    Frac &operator*=(const Frac &rhs)
    {
        num *= rhs.num;
        den *= rhs.den;
        normalize(); 
        return *this;
    }
    Frac &operator/=(const Frac &rhs)
    {
        num *= rhs.den;
        den *= rhs.num;
        if(den < 0)
        {
            num = -num;
            den = -den;
        }
        normalize();
        return *this;
    }
    friend Frac operator+(Frac lhs, const Frac &rhs)
    {
        return lhs += rhs;
    }
    friend Frac operator-(Frac lhs, const Frac &rhs)
    {
        return lhs -= rhs;
    }
    friend Frac operator*(Frac lhs, const Frac &rhs)
    {
        return lhs *= rhs;
    }
    friend Frac operator/(Frac lhs, const Frac &rhs)
    {
        return lhs /= rhs;
    }
    friend Frac operator-(const Frac &a)
    {
        return Frac(-a.num, a.den);
    }
    friend bool operator==(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den == rhs.num * lhs.den;
    }
    friend bool operator!=(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den != rhs.num * lhs.den;
    }
    friend bool operator<(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den < rhs.num * lhs.den;
    }
    friend bool operator>(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den > rhs.num * lhs.den;
    }
    friend bool operator<=(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den <= rhs.num * lhs.den;
    }
    friend bool operator>=(const Frac &lhs, const Frac &rhs) 
    {
        return lhs.num * rhs.den >= rhs.num * lhs.den;
    }
    friend ostream &operator<<(ostream &os, Frac x)
    {
        i128 g = gcd(x.num, x.den);
        if(x.den == g)
            return os << x.num / g;
        else
            return os << x.num / g << "/" << x.den / g;
    }
};

int cmp(ld x)
{
    if(abs(x) < EPS)
        return 0;
    return x < 0 ? -1 : 1;
}

struct Point
{
    ld x, y;
    bool operator<(const Point& o) const 
    {
        if (cmp(x - o.x) != 0) 
            return cmp(x - o.x) < 0;
        return cmp(y - o.y) < 0;
    }
    bool operator==(const Point& o) const 
    {
        return cmp(x - o.x) == 0 && cmp(y - o.y) == 0;
    }
};


struct EPoint
{
    Frac x, y;

    friend bool operator<(const EPoint &a, const EPoint &b)
    {
        if (a.x != b.x)
            return a.x < b.x;
        return a.y < b.y;
    }

    friend bool operator==(const EPoint &a, const EPoint &b)
    {
        return a.x == b.x && a.y == b.y;
    }
};

struct IPoint
{
    i128 x, y;
};

struct Segment
{
    IPoint a, b;
    int id;
};

i128 crossVec(i128 ax, i128 ay, i128 bx, i128 by)
{
    return ax * by - ay * bx;
}

i128 cross(IPoint a, IPoint b, IPoint c)
{
    return crossVec(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

bool between(i128 l, i128 r, i128 x)
{
    if (l > r)
        swap(l, r);
    return l <= x && x <= r;
}

bool onSegmentInt(IPoint p, IPoint a, IPoint b)
{
    return cross(a, b, p) == 0 && between(a.x, b.x, p.x) && between(a.y, b.y, p.y);
}

EPoint toEPoint(IPoint p)
{
    return {Frac(p.x), Frac(p.y)};
}

Frac getParamOnSeg(IPoint p, const Segment &s)
{
    if (s.a.x != s.b.x)
        return Frac(p.x - s.a.x, s.b.x - s.a.x);
    else
        return Frac(p.y - s.a.y, s.b.y - s.a.y);
}

EPoint pointAt(const Segment &s, Frac t)
{
    Frac x = Frac(s.a.x) + Frac(s.b.x - s.a.x) * t;
    Frac y = Frac(s.a.y) + Frac(s.b.y - s.a.y) * t;
    return {x, y};
}
struct DSU
{
    vector<int> f, siz;
    int part;
    DSU() {};
    DSU(int n)
    {
        init(n);
    }
    //input n,open n + 1
    void init(int n)
    {
        f.resize(n + 1);
        iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
        part = n;
    }
    int find(int x)
    {
        while(x != f[x])
            x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x,int y)
    {
        return find(x) == find(y);
    }
    bool merge(int x,int y)
    {
        x = find(x);
        y = find(y);
        if(x == y)
            return false;
        if(siz[x] < siz[y])
            swap(x, y);
        siz[x] += siz[y];
        f[y] = x;
        part--;
        return true;
    }
    //x -> y
    void pretoSuf(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        f[x] = y;
        siz[y] += siz[x];
        part--;
    }
    int size(int x)
    {
        return siz[find(x)];
    }
};

struct PlanarGraph
{   
    DSU faceDsu;

    struct Edge
    {
        int to;
        int id;
        ld ang;
        int edgeIdx;
        int face;
    };

    vector<Segment> rawSegs;

    int n;
    vector<Point> pts;      
    vector<EPoint> epts;    
    vector<vector<Edge>> adj;
    vector<int> posInAdj;

    int faceCnt;
    vector<vector<int>> faces;
    vector<ld> area;
    int outFace;

    PlanarGraph () {}

    PlanarGraph(int n_) : n(n_), pts(n_), adj(n_)
    {
        faceCnt = 0;
    }

    void setPoint(int u, ld x, ld y)
    {
        pts[u] = {x, y};   
    }

    void addRawSegment(i64 x1, i64 y1, i64 x2, i64 y2, int id)
    {
        rawSegs.push_back({{(i128)x1, (i128)y1}, {(i128)x2, (i128)y2}, id});
    }

    int etot = 0;
    void addEdge(int u, int v, int id)
    {
        ld ang1 = atan2l(pts[v].y - pts[u].y, pts[v].x - pts[u].x);
        adj[u].push_back({v, id, ang1, etot++, -1});

        ld ang2 = atan2l(pts[u].y - pts[v].y, pts[u].x - pts[v].x);
        adj[v].push_back({u, id, ang2, etot++, -1});
    }

    void build()
    {
        if (!rawSegs.empty()) 
        {
            n = 0;
            pts.clear();
            epts.clear();
            adj.clear();
            posInAdj.clear();
            faces.clear();
            area.clear();
            faceCnt = 0;
            etot = 0;

            int m = rawSegs.size();

            vector<vector<pair<Frac, EPoint>>> segPts(m);

            for (int i = 0; i < m; i++)
            {
                segPts[i].push_back({Frac(0), toEPoint(rawSegs[i].a)});
                segPts[i].push_back({Frac(1), toEPoint(rawSegs[i].b)});
            }

            for (int i = 0; i < m; i++)
            {
                for (int j = i + 1; j < m; j++)
                {
                    auto &S = rawSegs[i];
                    auto &T = rawSegs[j];

                    i128 rx = S.b.x - S.a.x;
                    i128 ry = S.b.y - S.a.y;
                    i128 sx = T.b.x - T.a.x;
                    i128 sy = T.b.y - T.a.y;

                    i128 den = crossVec(rx, ry, sx, sy);

                    if (den != 0)
                    {
                        i128 qx = T.a.x - S.a.x;
                        i128 qy = T.a.y - S.a.y;

                        Frac t(crossVec(qx, qy, sx, sy), den);
                        Frac u(crossVec(qx, qy, rx, ry), den);

                        if (Frac(0) <= t && t <= Frac(1) &&
                            Frac(0) <= u && u <= Frac(1))
                        {
                            EPoint P = pointAt(S, t);

                            segPts[i].push_back({t, P});
                            segPts[j].push_back({u, P});
                        }
                    }
                    else
                    {
                        if (cross(S.a, S.b, T.a) != 0)
                            continue;

                        auto addCommon = [&](IPoint P)
                        {
                            if (onSegmentInt(P, S.a, S.b) && onSegmentInt(P, T.a, T.b))
                            {
                                EPoint EP = toEPoint(P);
                                segPts[i].push_back({getParamOnSeg(P, S), EP});
                                segPts[j].push_back({getParamOnSeg(P, T), EP});
                            }
                        };

                        addCommon(S.a);
                        addCommon(S.b);
                        addCommon(T.a);
                        addCommon(T.b);
                    }
                }
            }

            map<EPoint, int> id;

            auto getId = [&](const EPoint &P) -> int
            {
                auto it = id.find(P);
                if (it != id.end())
                    return it->second;

                int idx = pts.size();
                id[P] = idx;

                epts.push_back(P);
                pts.push_back({(ld)P.x, (ld)P.y});
                adj.push_back({});

                return idx;
            };

            for (int i = 0; i < m; i++)
            {
                auto &v = segPts[i];

                sort(v.begin(), v.end(), [](const auto &a, const auto &b)
                {
                    if (a.first != b.first)
                        return a.first < b.first;
                    return a.second < b.second;
                });

                v.erase(unique(v.begin(), v.end(), [](const auto &a, const auto &b)
                {
                    return a.first == b.first && a.second == b.second;
                }), v.end());

                for (int j = 0; j + 1 < (int)v.size(); j++)
                {
                    int u = getId(v[j].second);
                    int w = getId(v[j + 1].second);

                    if (u != w)
                        addEdge(u, w, rawSegs[i].id);
                }
            }

            n = pts.size();
        }

        posInAdj.assign(etot, 0);
        for (int u = 0; u < n;u++)
        {
            sort(adj[u].begin(), adj[u].end(), [](const Edge &a, const Edge &b){ return a.ang < b.ang; });

            for (int i = 0;i < adj[u].size();i++)
            {
                posInAdj[adj[u][i].edgeIdx] = i;
            }
        }

        faceCnt = 0;
        for (int u = 0; u < n;u++)
        {
            for (int i = 0; i < adj[u].size();i++)
            {
                if(adj[u][i].face != -1)
                    continue;

                int curu = u;
                int curidx = i;
                faces.emplace_back();
                ld curarea = 0;

                while(adj[curu][curidx].face == -1)
                {
                    adj[curu][curidx].face = faceCnt;
                    faces.back().push_back(curu);

                    int v = adj[curu][curidx].to;
                    curarea += (pts[curu].x * pts[v].y - pts[v].x * pts[curu].y);

                    int revidx = posInAdj[adj[curu][curidx].edgeIdx ^ 1];
                    int nxtidx = revidx - 1;
                    if(nxtidx < 0)
                        nxtidx += adj[v].size();

                    curu = v;
                    curidx = nxtidx;
                }
                area.push_back(curarea / 2.);
                faceCnt++;
            }
        }
        outFace = 0;
        for (int i = 1;i < faceCnt;i++)
        {
            if(area[i] < area[outFace])
                outFace = i;
        }
        
        faceDsu.init(faceCnt);

        for (int i = 0; i < faceCnt; i++)
        {
            if (area[i] >= -EPS || i == outFace)
                continue;

            int vid = faces[i][0];
            for (int u : faces[i])
            {
                if (epts[vid].x < epts[u].x)
                    vid = u;
                else if (epts[vid].x == epts[u].x && epts[vid].y < epts[u].y)
                    vid = u;
            }

            Point V = pts[vid];

            ld py = V.y;
            ld px = V.x;

            int closestFace = outFace;
            ld minX = INF_DB;

            for (int u = 0; u < n; u++)
            {
                for (auto &edge : adj[u])
                {
                    Point A = pts[u];
                    Point B = pts[edge.to];

                    if (cmp(A.y - py) <= 0 && cmp(B.y - py) > 0)
                    {
                        ld xInt = A.x + (B.x - A.x) * (py - A.y) / (B.y - A.y);

                        if (cmp(xInt - px) > 0 && xInt < minX)
                        {
                            minX = xInt;
                            closestFace = edge.face;
                        }
                    }
                }
            }

            faceDsu.pretoSuf(i, closestFace);
        }
    }

    vector<vector<pii>> getDual()
    {
        outFace = faceDsu.find(outFace);
        vector<vector<pii>> dualadj(faceCnt);
        for (int u = 0; u < n;u++)
        {
            for (int i = 0; i < adj[u].size();i++)
            {
                int v = adj[u][i].to;
                int id = adj[u][i].id;
                int eidx = adj[u][i].edgeIdx;

                if(eidx % 2 == 0)
                {
                    int f1 = faceDsu.find(adj[u][i].face);
                    int f2 = faceDsu.find(adj[v][posInAdj[eidx ^ 1]].face);

                    if(f1 != f2)
                    {
                        dualadj[f1].push_back({f2, id});
                        dualadj[f2].push_back({f1, id});
                    }
                }
            }
        }

        return dualadj;
    }
};