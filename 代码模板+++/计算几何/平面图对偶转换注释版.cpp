#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
typedef pair<int, int> pii;

const db EPS = 1e-8;
const db INF_DB = 1e100;
//这个板子可以转化不是完全图的图为对偶图，内置了许多神器
//浮点数比较神器
int cmp(db x)
{
    if(abs(x) < EPS)
        return 0;
    return x < 0 ? -1 : 1;
}

struct Point
{
    db x, y;
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

struct Segment 
{ 
    Point p1, p2;
    int id; 
};  

//计算向量 AB 和 AC 构成的平行四边形有向面积。
db cross(Point a, Point b, Point c) // 叉积
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); 
}

//计算向量 AB 和 AC 的点乘
db dot(Point a, Point b, Point c) // 点积
{ 
    return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y); 
}

//功能：判断点 p 是否严格落在线段 ab 上（包含端点）。实现原理：
bool onSegment(Point p, Point a, Point b) 
{ 
    return cmp(cross(a, b, p)) == 0 && cmp(dot(p, a, b)) <= 0; 
}

//利用面积比例（相似三角形原理）推导出的直线交点公式。
Point getIntersection(Point a, Point b, Point c, Point d) 
{
    db s1 = cross(c, d, a), s2 = cross(c, d, b);
    return {(a.x * s2 - b.x * s1) / (s2 - s1), (a.y * s2 - b.y * s1) / (s2 - s1)};
}

//利用叉积的正负号，严谨地判断两条线段是否在空间中呈现“X”型的交叉。
bool checkIntersect(Point a, Point b, Point c, Point d) 
{
    if (max(min(a.x, b.x), min(c.x, d.x)) > min(max(a.x, b.x), max(c.x, d.x)) + EPS ||
    max(min(a.y, b.y), min(c.y, d.y)) > min(max(a.y, b.y), max(c.y, d.y)) + EPS)    
        return false;

    return cmp(cross(a, c, d) * cross(b, c, d)) <= 0 && cmp(cross(c, a, b) * cross(d, a, b)) <= 0;
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
        int id;// 原图墙垣的编号（用于去重或对偶图建边）
        db ang;// 极角
        int edgeIdx;// 内部连续编号，成对分配：偶数为正向，奇数为反向 (e, e^1)
        int face;// 该有向边归属的面的编号，初始为 -1
    };

    vector<Segment> rawSegs;

    int n;
    vector<Point> pts;
    vector<vector<Edge>> adj;
    vector<int> posInAdj;// 记录内部边编号 edgeIdx 在 adj[u] 中的具体位置

    int faceCnt;
    vector<vector<int>> faces;// 记录每个面由哪些顶点按顺序构成
    vector<db> area;// 记录每个面的有向面积
    int outFace;// “虚空”（外围无界面）的编号

    PlanarGraph(int n_) : n(n_), pts(n_), adj(n_)
    {
        faceCnt = 0;
    }

    // 设置原图节点的坐标
    void setPoint(int u, db x, db y)
    {
        pts[u] = {x, y};   
    }

    void addRawSegment(db x1, db y1, db x2, db y2, int id)
    {
        rawSegs.push_back({{x1, y1}, {x2, y2}, id});
    }

    int etot = 0;
    // 加边（必须是双向加边，以配合最小左转法的遍历）
    void addEdge(int u, int v, int id)
    {
        db ang1 = atan2(pts[v].y - pts[u].y, pts[v].x - pts[u].x);
        adj[u].push_back({v, id, ang1, etot++, -1});

        db ang2 = atan2(pts[u].y - pts[v].y, pts[u].x - pts[v].x);
        adj[v].push_back({u, id, ang2, etot++, -1});
    }

    // 核心算法：提取所有面并定位虚空
    void build()
    {
        if (!rawSegs.empty()) 
        {
            vector<Point> allPts;// 先把所有原始长线段的端点扔进去

            for (auto& seg : rawSegs) 
            {
                allPts.push_back(seg.p1);
                allPts.push_back(seg.p2);
            }

            // O(N^2) 暴力两两匹配，找所有的“十字路口”
            for (int i = 0; i < rawSegs.size(); i++) 
            {
                for (int j = i + 1; j < rawSegs.size(); j++) 
                {
                    if (checkIntersect(rawSegs[i].p1, rawSegs[i].p2, rawSegs[j].p1, rawSegs[j].p2)) // 如果相交
                    {
                        // 排除端点刚好碰在一起的情况（因为端点已经加过了），提取真正的内部交点
                        //“点 $C$ 不在直线 $AB$ 上” 或者 “点 $D$ 不在直线 $AB$ 上”。
                        //反过来想，如果这两个条件都不满足（两个都等于0，整个 if 进不去），意味着什么？
                        // 意味着：点 $C$ 和点 $D$ 都在直线 $AB$ 上！
                        if (cmp(cross(rawSegs[i].p1, rawSegs[i].p2, rawSegs[j].p1)) != 0 || 
                            cmp(cross(rawSegs[i].p1, rawSegs[i].p2, rawSegs[j].p2)) != 0) 
                        {
                            allPts.push_back(getIntersection(rawSegs[i].p1, rawSegs[i].p2, rawSegs[j].p1, rawSegs[j].p2));
                        }
                    }
                }
            }
            
            sort(allPts.begin(), allPts.end());
            allPts.erase(unique(allPts.begin(), allPts.end()), allPts.end());
            
            n = allPts.size();// 图的节点总数敲定！
            pts = allPts;
            adj.assign(n, {});// 开辟邻接表

            for (auto& seg : rawSegs) // 重新审视每一条原始长墙垣
            {
                vector<pair<Point, int>> onSegPts;
                // 1. 遍历全世界所有的关键点，看看谁在这条长墙上？
                for (int i = 0; i < n; i++) 
                {
                    if (onSegment(pts[i], seg.p1, seg.p2)) 
                        onSegPts.push_back({pts[i], i});// 记录坐标和它的图论ID
                }
                
                // 2. 把墙上的点，顺着墙的方向排好队
                sort(onSegPts.begin(), onSegPts.end(), [](const pair<Point, int>& a, const pair<Point, int>& b) {
                    return a.first < b.first;
                });
                
                // 3. 将相邻的人两两用红线连起来！
                for (int i = 0; i + 1 < onSegPts.size(); i++) 
                {
                    addEdge(onSegPts[i].second, onSegPts[i + 1].second, seg.id);
                }
            }
        }

        posInAdj.assign(etot, 0);
        for (int u = 0; u < n;u++)
        {
            // 1. 对每个节点的所有出边按极角逆时针排序
            sort(adj[u].begin(), adj[u].end(), [](const Edge &a, const Edge &b){ return a.ang < b.ang; });

            // 2. 记录排序后每条边的位置
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
                    continue;// 已经被遍历过

                int curu = u;
                int curidx = i;
                faces.emplace_back();
                db curarea = 0;

                // 3. 一直沿着“最右（顺时针）”的边走，直到闭合
                while(adj[curu][curidx].face == -1)
                {
                    adj[curu][curidx].face = faceCnt;
                    faces.back().push_back(curu);

                    int v = adj[curu][curidx].to;
                    curarea += (pts[curu].x * pts[v].y - pts[v].x * pts[curu].y);

                    // 找到反向边在 v 的邻接表中的位置
                    int revidx = posInAdj[adj[curu][curidx].edgeIdx ^ 1];

                    // 最小左转 = 逆时针排序下的上一条边（即顺时针的第一条边）
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
        // 4. 定位“虚空”区域：有向面积最小（必定为负）的面就是无界外围面
        outFace = 0;
        for (int i = 1;i < faceCnt;i++)
        {
            if(area[i] < area[outFace])
                outFace = i;
        }
        // ========== 新增：用 DSU 合并非连通孤岛产生的嵌套外部面 ==========
        faceDsu.init(faceCnt);

        for (int i = 0; i < faceCnt; i++)
        {
            // 如果是内部区域（面积为正）或者是全局虚空，不需要合并
            if (area[i] >= -EPS || i == outFace)
                continue;

            // 找这个负面积面的最右侧顶点
            Point V = pts[faces[i][0]];
            for (int u : faces[i])
            {
                if (pts[u].x > V.x + EPS)
                    V = pts[u];
                else if (abs(pts[u].x - V.x) <= EPS && pts[u].y > V.y)
                    V = pts[u];
            }

            // 从最右侧顶点稍微上移，向右打射线，避免正好打到顶点
            db py = V.y + 1.234567e-5;
            db px = V.x;

            int closestFace = outFace;
            db minX = INF_DB;

            // 遍历图中所有的边，找最近的碰撞
            for (int u = 0; u < n; u++)
            {
                for (auto &edge : adj[u])
                {
                    Point A = pts[u];
                    Point B = pts[edge.to];

                    // 只拦截向上穿过射线的边（因为内部面永远在向上的边的左侧）
                    if (A.y < py && B.y >= py)
                    {
                        db xInt = A.x + (B.x - A.x) * (py - A.y) / (B.y - A.y);

                        if (xInt > px + 1e-7 && xInt < minX)
                        {
                            minX = xInt;
                            closestFace = edge.face;
                        }
                    }
                }
            }

            faceDsu.merge(i, closestFace);
        }
    }

    // 获取对偶图（点数为 faceCnt，虚空为 outFace）
    // 返回格式：dualAdj[面u] = vector<{面v, 穿越的原墙垣编号}>
    vector<vector<pii>> getDual()
    {
        vector<vector<pii>> dualadj(faceCnt);
        for (int u = 0; u < n;u++)
        {
            for (int i = 0; i < adj[u].size();i++)
            {
                int v = adj[u][i].to;
                int id = adj[u][i].id;
                int eidx = adj[u][i].edgeIdx;

                // 只利用正向边进行一次转移，避免对偶图重复加边
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