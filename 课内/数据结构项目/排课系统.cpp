#include <bits/stdc++.h>
using namespace std;

class CourseScheduler 
{
private:
    int numCourses;
    // 课程名字映射 (为了让输出好看点，不用干巴巴的数字)
    vector<string> courseNames;
    // 邻接表：adj[u] 存储所有把 u 当作先修课的后续课程
    vector<vector<int>> adj;
    // 入度数组：记录每门课有多少门先修课还没上
    vector<int> inDegree;

public:
    CourseScheduler(int n, const vector<string>& names) : numCourses(n), courseNames(names) 
    {
        adj.resize(n);
        inDegree.assign(n, 0);
    }

    // 添加先修关系：prereq 是 course 的先修课 (prereq -> course)
    void addPrerequisite(int prereq, int course) 
    {
        adj[prereq].push_back(course);
        inDegree[course]++;
    }

    // 核心算法：分层的拓扑排序 (按最少学期排课)
    void scheduleMinSemesters() 
    {
        queue<int> q;
        
        // 1. 初始化：把所有没有先修课的课程（入度为0）放入队列
        for (int i = 0; i < numCourses; ++i) 
        {
            if (inDegree[i] == 0) 
            {
                q.push(i);
            }
        }

        int semester = 1;
        int completedCourses = 0;

        cout << "========== 按照最少学期排课计划 ==========" << endl;

        // 2. BFS 层序遍历（每一层就是一个学期）
        while (!q.empty()) 
        {
            // 获取当前学期可以同时上的课程数量
            int currentSemesterSize = q.size();
            cout << "【第 " << semester << " 学期】: ";

            // 遍历当前学期的所有课程
            for (int i = 0; i < currentSemesterSize; ++i) 
            {
                int curr = q.front();
                q.pop();
                
                cout << courseNames[curr] << "  ";
                completedCourses++;

                // 把当前课程的所有后续课程的入度减 1
                for (int nextCourse : adj[curr]) 
                {
                    inDegree[nextCourse]--;
                    // 如果后续课程的先修课已经全部上完，安排到下个学期
                    if (inDegree[nextCourse] == 0) 
                    {
                        q.push(nextCourse);
                    }
                }
            }
            cout << endl;
            semester++;
        }

        cout << "==========================================" << endl;

        // 3. 循环依赖检测（判断能否毕业）
        if (completedCourses < numCourses) 
        {
            cout << "\n[警告] 课程安排失败！" << endl;
            cout << "发现循环依赖（例如A依赖B，B又依赖A），有 " << (numCourses - completedCourses) << " 门课程永远无法修读。" << endl;
        } else {
            cout << "\n排课成功！修完所有课程最少需要 " << (semester - 1) << " 个学期。" << endl;
        }
    }
};

int main() 
{
    // 假设有 6 门课
    vector<string> names = 
    {
        "C语言",       // 0
        "离散数学",     // 1
        "数据结构",     // 2
        "算法设计",     // 3
        "操作系统",     // 4
        "人工智能"      // 5
    };
    
    CourseScheduler scheduler(names.size(), names);

    // 设置先修关系
    scheduler.addPrerequisite(0, 2); // C语言 -> 数据结构
    scheduler.addPrerequisite(1, 2); // 离散数学 -> 数据结构
    scheduler.addPrerequisite(2, 3); // 数据结构 -> 算法设计
    scheduler.addPrerequisite(2, 4); // 数据结构 -> 操作系统
    scheduler.addPrerequisite(3, 5); // 算法设计 -> 人工智能

    // 执行排课
    scheduler.scheduleMinSemesters();

    return 0;
}