#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KMAXVERTEX 10000
#define MAXDATA 50

typedef struct EdgeNode {
    int dest;
    int weight;
    struct EdgeNode* next;
} EdgeNode;

typedef struct HeadNode {
    EdgeNode* adj;
    char data[MAXDATA];
} HeadNode;

typedef struct Graph {
    int n_verts;
    int m_edges;
    int directed;
    HeadNode ver_list[KMAXVERTEX];
} Graph;

// 初始化图
Graph* InitGraph(int directed) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->n_verts = 0;
    graph->m_edges = 0;
    graph->directed = directed;
    for(int i=0;i<KMAXVERTEX;i++){
        graph->ver_list[i].adj = NULL;
        graph->ver_list[i].data[0] = '\0';
    }
    return graph;
}

// 判断边是否存在
int ExistEdge(Graph* graph, int u, int v) {
    EdgeNode* p = graph->ver_list[u].adj;
    while (p != NULL && p->dest != v) {
        p = p->next;
    }
    return p != NULL;
}

// 插入边
void InsertEdge(Graph* graph, int u, int v, int weight) {
    if (!ExistEdge(graph, u, v)) {
        EdgeNode* p = (EdgeNode*)malloc(sizeof(EdgeNode));
        p->dest = v;
        p->weight = weight;
        p->next = graph->ver_list[u].adj;
        graph->ver_list[u].adj = p;
        graph->m_edges++;
        if (!graph->directed) {
            EdgeNode* q = (EdgeNode*)malloc(sizeof(EdgeNode));
            q->dest = u;
            q->weight = weight;
            q->next = graph->ver_list[v].adj;
            graph->ver_list[v].adj = q;
        }
    }
}

// 构建图
Graph* BuildGraph() {
    int n, m;
    scanf("%d %d", &n, &m);
    Graph* graph = InitGraph(1);
    for(int i=0;i<n;i++){
        scanf("%s", graph->ver_list[i].data);
        graph->n_verts++;
    }
    for(int i=0;i<m;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        InsertEdge(graph, u, v, 1);
    }
    return graph;
}

// 获取入度
void GetInDegree(Graph* graph, int* in_degree) {
    for(int i=0;i<graph->n_verts;i++)
        in_degree[i] = 0;
    for(int u=0; u<graph->n_verts; u++){
        EdgeNode* p = graph->ver_list[u].adj;
        while(p != NULL){
            in_degree[p->dest]++;
            p = p->next;
        }
    }
}

// 拓扑排序 本题要求实现
int TopSort(Graph* graph, int* top_s)
{
    int n = graph->n_verts;
    int pos = 0, idx = 0;
    int po[n], ind[n];
    GetInDegree(graph, ind);
    for (int i = 0; i < n;i++)
    {
        if(ind[i] == 0)
        {
            po[pos++] = i;
        }
    }
    for (int i = 0; i < pos;i++)
    {
        int u = po[i];
        top_s[idx++] = u;
        EdgeNode *p = graph->ver_list[u].adj;
        while(p != NULL)
        {
            ind[p->dest]--;
            if(ind[p->dest] == 0)
                po[pos++] = p->dest;
            p = p->next;
        }
    }
    if(pos == n)
        return 1;
    else
        return 0;
}

int main() {
    Graph* graph = BuildGraph();
    int top_s[KMAXVERTEX];
    if(TopSort(graph, top_s)){
        printf("This graph can be topologically sorted!\nTopsort result: ");
        for(int i=0;i<graph->n_verts;i++){
            printf("%s ", graph->ver_list[top_s[i]].data);
        }
        printf("\n");
    } else {
        printf("The graph has circle!\n");
    }
    return 0;
}