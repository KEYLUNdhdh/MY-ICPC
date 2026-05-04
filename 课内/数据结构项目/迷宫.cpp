#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// 坐标结构体
struct Point 
{
    int x, y;
    bool operator==(const Point& other) const 
    {
        return x == other.x && y == other.y;
    }
};

// 并查集，用于Kruskal迷宫生成
struct DSU 
{
    vector<int> parent;
    DSU(int n) 
    {
        parent.resize(n);//开n的空间
        iota(parent.begin(), parent.end(), 0);//初始化每个节点的父亲是自己
    }
    int find(int i) 
    {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);//路径压缩，提升查找效率
    }
    bool unite(int i, int j) 
    {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) //如果不连通，就合并，并返回true
        {
            parent[root_i] = root_j;
            return true;
        }
        return false;//否则，返回false
    }
};  

class MazeSolver 
{
private:
    int rows, cols;
    vector<vector<int>> maze; // 1: 墙, 0: 路
    vector<Point> entrances;//存储入口
    vector<Point> exits;//存储出口
    
    // 方向数组 (上下左右)
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    // 记录找到的路径总数
    int path_count = 0;

    // 控制台颜色宏定义 (ANSI Escape Codes)
    const string COLOR_RESET = "\033[0m";
    const string COLOR_GREEN = "\033[32m"; // 绿色前景色

public:
    MazeSolver(int r, int c) : rows(r), cols(c) 
    {
        // 保证行列为奇数，方便基于墙和房间的模型生成迷宫
        if (rows % 2 == 0) rows++;
        if (cols % 2 == 0) cols++;
        maze.assign(rows, vector<int>(cols, 1));//一开始全是墙
    }

    // 基于并查集(Kruskal)随机生成迷宫
    void generateMaze() 
    {
        random_device rd;
        mt19937 gen(rd());
        
        int room_rows = rows / 2;
        int room_cols = cols / 2;
        DSU dsu(room_rows * room_cols);//算出实际上有多少房间，并初始化并查集
        
        // 存储所有候选墙壁: (墙壁坐标, 相邻房间1ID, 相邻房间2ID)
        struct Wall { int wx, wy, r1, r2; };
        vector<Wall> walls;

        // 初始化房间并收集内部墙壁
        for (int i = 0; i < room_rows; ++i) 
        {
            for (int j = 0; j < room_cols; ++j) 
            {
                int r_x = i * 2 + 1;
                int r_y = j * 2 + 1;
                maze[r_x][r_y] = 0; // 房间挖空
                
                int curr_id = i * room_cols + j;
                // 右侧墙壁
                if (j < room_cols - 1) 
                {
                    walls.push_back({r_x, r_y + 1, curr_id, curr_id + 1});
                }
                // 下方墙壁
                if (i < room_rows - 1) 
                {
                    walls.push_back({r_x + 1, r_y, curr_id, curr_id + room_cols});
                }
            }
        }

        // 打乱墙壁，实现随机迷宫
        shuffle(walls.begin(), walls.end(), gen);

        // 并查集建树
        for (const auto& w : walls) 
        {
            if (dsu.unite(w.r1, w.r2)) 
            {
                maze[w.wx][w.wy] = 0; // 打通不连通的房间
            } 
            else 
            {
                // 【核心修改】：人为制造多条通路
                // 对于已经连通的区域，我们有 5% 的概率依然把墙拆掉，制造环（Cycles）
                uniform_real_distribution<> dis(0.0, 1.0);
                if (dis(gen) < 0.05) 
                {
                    maze[w.wx][w.wy] = 0;
                }
            }
        }

        // 设置多入口和多出口 (为了演示，直接挖开左边界和右边界的几个点)
        entrances = {{1, 0}, {3, 0}};
        for (auto& p : entrances) maze[p.x][p.y] = 0;

        exits = {{rows - 2, cols - 1}, {rows - 4, cols - 1}};
        for (auto& p : exits) maze[p.x][p.y] = 0;
    }

    // --- 新增：独立封装的路径高亮打印函数 ---
    void printPathMap(const vector<Point>& path) {
        // 1. 将当前路径转换为二维布尔数组，方便 O(1) 快速查询
        vector<vector<bool>> is_path(rows, vector<bool>(cols, false));
        for (const auto& p : path) {
            is_path[p.x][p.y] = true;
        }

        // 2. 遍历原迷宫并渲染
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (is_path[i][j]) {
                    // 如果是路径，输出绿色方块
                    cout << COLOR_GREEN << "██" << COLOR_RESET;
                } else if (maze[i][j] == 1) {
                    // 如果是墙壁，输出默认颜色方块
                    cout << "██";
                } else {
                    // 空地
                    cout << "  ";
                }
            }
            cout << endl;
        }
        cout << "----------------------------------------" << endl;
    }

    // 递归 DFS 回溯函数 (利用系统栈)
    void dfs(Point curr, vector<Point>& current_path, vector<vector<bool>>& visited) 
    {
        // 剪枝或边界判断
        if (curr.x < 0 || curr.x >= rows || curr.y < 0 || curr.y >= cols) return;
        if (maze[curr.x][curr.y] == 1 || visited[curr.x][curr.y]) return;

        // 做选择：压栈并标记访问
        current_path.push_back(curr);
        visited[curr.x][curr.y] = true;

        // 检查是否到达任意出口
        bool is_exit = false;
        for (const auto& e : exits) 
        {
            if (curr == e) 
            {
                is_exit = true;
                break;
            }
        }

        if (is_exit) 
        {
            path_count++;
            // 这里可以处理或打印路径，为了控制输出刷屏，仅在数量较少时打印
            if (path_count <= 5) 
            {
                cout << "=> 找到第 " << path_count << " 条通路 (长度: " << current_path.size() << ")，地图如下：" << endl;
                printPathMap(current_path); // 调用封装好的打印函数
            }
            else if(path_count == 6)
                cout << "=> (通路较多，后续不再打印具体地图，仅作统计...)" << endl;
        }
        else 
        {
            // 继续向四个方向搜索
            for (int i = 0; i < 4; ++i) 
            {
                dfs({curr.x + dx[i], curr.y + dy[i]}, current_path, visited);
            }
        }

        // 撤销选择：出栈并清除标记 (回溯核心)
        visited[curr.x][curr.y] = false;
        current_path.pop_back();
    }

    // 外层入口：使用队列调度多个起点
    void findAndPrintAllPaths() {
        path_count = 0;
        queue<Point> q; // 队列调度器
        
        for (const auto& start : entrances) {
            q.push(start);
        }

        cout << "开始搜索所有通路..." << endl;
        
        while (!q.empty()) {
            Point start_point = q.front();
            q.pop();
            
            vector<Point> current_path;
            vector<vector<bool>> visited(rows, vector<bool>(cols, false));
            
            cout << "\n--- 从入口 (" << start_point.x << ", " << start_point.y << ") 开始搜索 ---" << endl;
            dfs(start_point, current_path, visited);
        }
        
        cout << "\n搜索完毕！在当前迷宫中共找到 " << path_count << " 条合法通路。" << endl;
    }

    // 打印迷宫看一眼
    void printMaze() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (maze[i][j] == 1) cout << "██"; // 墙
                else cout << "  "; // 路
            }
            cout << endl;
        }
    }
};

int main() {
    // 创建一个 15x15 的迷宫
    MazeSolver solver(15, 15);
    
    solver.generateMaze();
    cout << "生成的迷宫地形如下：" << endl;
    solver.printMaze();
    
    solver.findAndPrintAllPaths();
    
    return 0;
}