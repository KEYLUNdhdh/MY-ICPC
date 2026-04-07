#include <stdio.h>
#include <stdlib.h>

#define KMAXVERTEX 1010
#define NIL -1

typedef struct EdgeNode {
    int dest;
    int weight;
    struct EdgeNode* next;
} EdgeNode;

typedef struct HeadNode {
    EdgeNode* adj;
} HeadNode;

typedef struct LGraph {
    int n_verts;
    int m_edges;
    HeadNode ver_list[KMAXVERTEX];
    int directed;
} LGraph;

// 初始化图
LGraph* InitGraph(int directed) {
    LGraph* graph = (LGraph*)malloc(sizeof(LGraph));
    graph->n_verts = 0;
    graph->m_edges = 0;
    graph->directed = directed;
    for(int i=0;i<KMAXVERTEX;i++)
        graph->ver_list[i].adj = NULL;
    return graph;
}

// 判断边是否存在
int ExistEdge(LGraph* graph, int u, int v) {
    EdgeNode* p = graph->ver_list[u].adj;
    while(p != NULL && p->dest != v)
        p = p->next;
    return p != NULL;
}

// 插入边
void InsertEdge(LGraph* graph, int u, int v, int weight) {
    //应该也是头插法
    if(!ExistEdge(graph, u, v)) {
        EdgeNode* p = (EdgeNode*)malloc(sizeof(EdgeNode));
        p->dest = v;
        p->weight = weight;
        p->next = graph->ver_list[u].adj;
        graph->ver_list[u].adj = p;
        graph->m_edges++;
        if(!graph->directed) {
            EdgeNode* q = (EdgeNode*)malloc(sizeof(EdgeNode));
            q->dest = u;
            q->weight = weight;
            q->next = graph->ver_list[v].adj;
            graph->ver_list[v].adj = q;
        }
    }
}

// 构建图
LGraph* BuildGraph() {
    int kMaxVertex, n, m;
    scanf("%d", &kMaxVertex);  // 输入最大顶点数，可忽略
    scanf("%d %d", &n, &m);
    LGraph* graph = InitGraph(1); // 有向图
    graph->n_verts = n;
    for(int i=0;i<m;i++){
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        InsertEdge(graph, u, v, weight);
    }
    return graph;
}

// 获取入度
void GetInDegree(LGraph* graph, int* in_degree) {
    int n = graph->n_verts;
    for(int i=0;i<n;i++) in_degree[i]=0;
    for(int u=0; u<n; u++) {
        EdgeNode* p = graph->ver_list[u].adj;
        while(p != NULL) {
            in_degree[p->dest]++;
            p = p->next;
        }
    }
}

// 拓扑排序
int TopSort(LGraph* graph, int* top_s) {
    int n = graph->n_verts;
    int in_degree[KMAXVERTEX];
    GetInDegree(graph, in_degree);
    int queue[KMAXVERTEX], front=0, rear=0;
    for(int i=0;i<n;i++)
        if(in_degree[i]==0) queue[rear++]=i;
    int count_v=0;
    while(front<rear){
        int u=queue[front++];
        top_s[count_v++]=u;
        EdgeNode* p = graph->ver_list[u].adj;
        while(p!=NULL){
            int v=p->dest;
            in_degree[v]--;
            if(in_degree[v]==0) queue[rear++]=v;
            p=p->next;
        }
    }
    return count_v==n;
}
//关键路径（Critical Path）： 从整个工程开始到工程结束，耗时最长的那条路径。因为只有这条路径上的所有任务都完成了，整个工程才算完成。
//关键活动（Critical Activity）： 也就是关键路径上的那些边（活动）。它们的特点是没有丝毫的松弛时间（机动时间）。也就是说，如果任何一个“关键活动”延期了，整个工程的最终完工时间就会被迫延期。

//计算关键活动的两个核心指标：
// 最早发生时间（Earliest Time, ve）： 顺着图的拓扑排序，计算从起点到某个事件可能发生的最早时间。
// 最迟发生时间（Latest Time, vl）： 逆着拓扑排序，从终点的 ve 倒推回来，计算为了不拖延整个工程，某个事件最迟必须发生的时间。
// 当一条边（活动） <u, v> 满足：它的最早开始时间 == 它的最迟开始时间 时，它就是关键活动。

// 求关键活动的算法分为三步：
// 正向拓扑排序，求每个顶点的最早发生时间 ve。
// 逆向拓扑排序，求每个顶点的最迟发生时间 vl。
// 遍历所有边，计算每条边的最早开始时间和最迟开始时间，如果相等，则输出这条边。

// 关键路径分析 本题要求实现
int CriticalAnalysis(LGraph* graph)
{
    int n = graph->n_verts;
    int top_s[KMAXVERTEX];
    if(!TopSort(graph, top_s))
        return 0;
    int ve[KMAXVERTEX];
    int vl[KMAXVERTEX];

    for (int i = 0; i < n;i++)
        ve[i] = 0;
    for (int i = 0; i < n;i++)
    {
        int u = top_s[i];
        EdgeNode *p = graph->ver_list[u].adj;
        while(p)
        {
            int v = p->dest;
            if(ve[u] + p->weight > ve[v])
                ve[v] = ve[u] + p->weight;
            p = p->next;
        }
    }
    int max_ve = 0;
    for (int i = 0; i < n;i++)
    {
        if(ve[i] > max_ve)
            max_ve = ve[i];
    }
    for (int i = 0; i < n;i++)
        vl[i] = max_ve;
    for (int i = n - 1; i >= 0;i--)
    {
        int u = top_s[i];
        EdgeNode *p = graph->ver_list[u].adj;
        while(p)
        {
            int v = p->dest;
            if(vl[v] - p->weight < vl[u])
                vl[u] = vl[v] - p->weight;
            p = p->next;
        }
    }
    for (int u = 0; u < n;u++)
    {
        for (int v = 0; v < n;v++)
        {
            EdgeNode *p = graph->ver_list[u].adj;
            int weight = -1;
            while(p)
            {
                if(p->dest == v)
                {
                    weight = p->weight;
                    break;
                }
                p = p->next;
            }
            if(weight != -1 )
            {
                int e = ve[u];
                int l = vl[v] - weight;
                if(e == l)
                    printf("<%d, %d>\n", u, v);
            }
        }
    }
    return 1;
}


int main() {
    LGraph* graph = BuildGraph();
    if(!CriticalAnalysis(graph))
        printf("关键路径分析结果为 False");
    else printf("关键路径分析结果为 True");
    return 0;
}