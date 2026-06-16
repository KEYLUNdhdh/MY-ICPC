#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int Vertex;    /* 顶点编号类型 */

typedef struct EdgeNode *Position; /* 指针即结点位置 */
struct EdgeNode {
    Vertex dest;     /* 边的另一端点编号 */
    Position next;   /* 线性表中下一个元素的位置 */
};
typedef struct HeadNode *AdjList; /* 邻接表 */
struct HeadNode {
    Position adj;  /* 邻接表头指针 */
};
typedef struct LGraphNode *LGraph; /* 邻接表表示的图 */
struct LGraphNode {
    int n_verts; /* 顶点数 */
    int m_edges; /* 边数 */
    AdjList *ver_list; /* 存储顶点邻接表 */
    bool directed; /* true为有向图，false为无向图 */
};

typedef struct EulerNode *ECList; /* 欧拉回路链表 */
struct EulerNode {
    Vertex ver;    /* 顶点编号 */
    ECList next;   /* 线性表中下一个元素的位置 */
};
typedef struct CircPtrNode *Circuit; /* 欧拉回路 */
struct CircPtrNode {
	ECList first;  /* 回路首结点指针 */
	ECList last;   /* 回路尾结点指针 */
};

void InitGraph(LGraph graph, int kMaxVertex, bool directed) {
    graph->n_verts = 0;
    graph->m_edges = 0;
    graph->directed = directed;
    // 为每个顶点分配邻接表头空间
    graph->ver_list = (AdjList*)malloc(kMaxVertex * sizeof(AdjList));
    for (int i = 0; i < kMaxVertex; i++) {
        graph->ver_list[i] = (AdjList)malloc(sizeof(struct HeadNode));
        graph->ver_list[i]->adj = NULL;
    }
}

void InsertEdge(LGraph graph, Vertex u, Vertex v) {
    // 创建u→v的边结点
    Position newNode1 = (Position)malloc(sizeof(struct EdgeNode));
    newNode1->dest = v;
    // 头插法插入u的邻接表
    newNode1->next = graph->ver_list[u]->adj;
    graph->ver_list[u]->adj = newNode1;

    // 无向图需要再加一条v→u的反向边
    if (!graph->directed) {
        Position newNode2 = (Position)malloc(sizeof(struct EdgeNode));
        newNode2->dest = u;
        newNode2->next = graph->ver_list[v]->adj;
        graph->ver_list[v]->adj = newNode2;
    }
}

void RemoveEdge(LGraph graph, Vertex u, Vertex v) {
    Position prev = NULL;
    Position curr = graph->ver_list[u]->adj;
    // 遍历找到u邻接表里指向v的边
    while (curr != NULL && curr->dest != v) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) return; // 没找到边直接返回

    // 删除u→v的边
    if (prev == NULL) {
        graph->ver_list[u]->adj = curr->next; // 删头结点
    } else {
        prev->next = curr->next; // 删中间结点
    }
    free(curr);

    // 无向图同步删除反向边v→u
    if (!graph->directed) {
        prev = NULL;
        curr = graph->ver_list[v]->adj;
        while (curr != NULL && curr->dest != u) {
            prev = curr;
            curr = curr->next;
        }
        if (curr == NULL) return;
        if (prev == NULL) {
            graph->ver_list[v]->adj = curr->next;
        } else {
            prev->next = curr->next;
        }
        free(curr);
    }
}

LGraph Clone(LGraph graph) {
    LGraph newGraph = (LGraph)malloc(sizeof(struct LGraphNode));
    newGraph->n_verts = graph->n_verts;
    newGraph->m_edges = graph->m_edges;
    newGraph->directed = graph->directed;
    newGraph->ver_list = (AdjList*)malloc(graph->n_verts * sizeof(AdjList));
    
    // 逐顶点拷贝邻接表
    for (int u = 0; u < graph->n_verts; u++) {
        newGraph->ver_list[u] = (AdjList)malloc(sizeof(struct HeadNode));
        newGraph->ver_list[u]->adj = NULL;
        Position curr = graph->ver_list[u]->adj;
        // 逆序拷贝保证结构一致
        while (curr != NULL) {
            Position newNode = (Position)malloc(sizeof(struct EdgeNode));
            newNode->dest = curr->dest;
            newNode->next = newGraph->ver_list[u]->adj;
            newGraph->ver_list[u]->adj = newNode;
            curr = curr->next;
        }
    }
    return newGraph;
}

// 辅助函数：把顶点加入欧拉回路尾部
void addToCircuit(Circuit circuit, Vertex v) {
    ECList newNode = (ECList)malloc(sizeof(struct EulerNode));
    newNode->ver = v;
    newNode->next = NULL;
    if (circuit->first == NULL) {
        circuit->first = newNode;
        circuit->last = newNode;
    } else {
        circuit->last->next = newNode;
        circuit->last = newNode;
    }
}

// Hierholzer算法递归找回路
void dfs(Vertex u, LGraph graph, Circuit circuit) {
    // 只要当前顶点u还有没走过的边，就继续走
    while (graph->ver_list[u]->adj != NULL) {
        // 取出这条边指向的下一个顶点v
        Vertex v = graph->ver_list[u]->adj->dest;
        // 把u→v这条边从图中删掉（欧拉回路每条边只能走一次）
        RemoveEdge(graph, u, v);
        // 递归走到v，继续往下找
        dfs(v, graph, circuit);
    }
    // 走到这里说明u已经没有边可以走了，把u加入回路
    addToCircuit(circuit, u);
}
// 给你举个简单例子，比如这个简单的三角形欧拉回路：0-1-2-0，走一遍流程你就懂了：

// 从起点0开始，当前还有边0→1，删掉这条边，递归走1
// 1还有边1→2，删掉，递归走2
// 2还有边2→0，删掉，递归走0
// 现在0已经没边了，把0加入回路 → 回路现在是：[0]，回溯到2
// 2也没边了，把2加入回路 → 回路现在是：[0, 2]，回溯到1
// 1也没边了，把1加入回路 → 回路现在是：[0, 2, 1]，回溯到0
// 0也没边了，把0加入回路 → 回路最终是：[0, 2, 1, 0]
// 倒过来就是我们要的欧拉回路 0 → 1 → 2 → 0，刚好和你main函数输出顺序对应？不对，这里为什么结果是对的？因为你是头插吗？不，你的代码是每次把结点加在尾部，最后链表顺序刚好就是递归逆序，直接输出就是正确的顺序，和上面例子最终输出0->1->2->0完全一致。

Circuit GetCircuit(LGraph graph, Vertex start) {
    Circuit circuit = (Circuit)malloc(sizeof(struct CircPtrNode));
    circuit->first = NULL;
    circuit->last = NULL;
    dfs(start, graph, circuit);
    return circuit;
}

// GetCircuit其实就是个初始化的包装：

// 先给欧拉回路结构体分配空间，把首指针和尾指针都初始化为空
// 调用上面的dfs递归从起点开始找
// 最终把生成好的回路返回给调用者
// start 可以任意选，这里题目规定0

Circuit EulerCircle(LGraph graph) {
    // 先计算每个顶点的度数，判断是否存在欧拉回路
    int *degree = (int*)calloc(graph->n_verts, sizeof(int));
    for (int u = 0; u < graph->n_verts; u++) {
        Position curr = graph->ver_list[u]->adj;
        while (curr != NULL) {
            degree[u]++;
            curr = curr->next;
        }
        // 存在奇数度数，直接返回NULL
        if (degree[u] % 2 != 0) {
            free(degree);
            return NULL;
        }
    }
    free(degree);

    // 拷贝原图，避免修改原结构
    LGraph cloned = Clone(graph);
    // 从0开始获取欧拉回路，题目要求起点固定为0
    Circuit res = GetCircuit(cloned, 0);
    return res;
}

LGraph BuildGraph() {
    int kMaxVertex, n, m;
    scanf("%d", &kMaxVertex);
    scanf("%d %d", &n, &m);

    LGraph graph = (LGraph)malloc(sizeof(struct LGraphNode));
    InitGraph(graph, kMaxVertex, false); // 本题是无向图
    graph->n_verts = n;
    graph->m_edges = m;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        InsertEdge(graph, u, v);
    }
    return graph;
}
 
int main(void) {
	LGraph graph;
	Circuit circuit;
	ECList cp;
	
	graph = BuildGraph();
	circuit = EulerCircle(graph);
	if (circuit != NULL) {
		for (cp=circuit->first; cp!=circuit->last; cp=cp->next) {
			printf("%d->", cp->ver);
		}
		printf("%d\n", cp->ver);
	}
	else {
		printf("No Euler circuit.\n");
	}
	
	return 0;
}


// Hierholzer算法原理：
// 从起点0出发深度优先搜索，每经过一条边就把这条边标记为已访问（避免重复走）
// 当前顶点所有边都走完之后，把顶点加入路径（回溯添加）
// 最后把路径反转，就是从起点出发的正确欧拉回路顺序

// 无向图存在欧拉回路的充要条件非常好记：图是连通的，且所有顶点的度数都是偶数，题目已经帮我们保证了连通性，我们只需要判断度数就可以了。