#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 105
// 每个人的信息
typedef struct {
    char name[15];
    int depth;      // 缩进深度/2，父节点深度就是我的深度-1
    int parent;     // 父节点的数组下标
    bool is_ancestor[MAXN]; // 所有祖先标记，is_ancestor[a] = true 说明a是我的祖先
} Person;

Person p[MAXN];

// 根据名字找下标
int find_id(char *name, int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(p[i].name, name) == 0)
            return i;
    }
    return -1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    getchar(); // 吃掉n后面的换行

    // 1. 读入所有家谱
    for (int i = 0; i < n; i++) {
        char line[200];
        fgets(line, 200, stdin);
        // 计算缩进空格数就是深度
        int depth = 0;
        while (line[depth] == ' ') depth++;
        p[i].depth = depth / 2;
        strcpy(p[i].name, line + depth);
        // 去掉末尾的换行符
        if (p[i].name[strlen(p[i].name)-1] == '\n')
            p[i].name[strlen(p[i].name)-1] = '\0';

        // 初始化祖先标记，先只标记自己
        memset(p[i].is_ancestor, 0, sizeof(p[i].is_ancestor));
        p[i].is_ancestor[i] = true;

        // 找父节点：往上找第一个深度 = 当前深度-1的结点
        if (p[i].depth > 0) {
            for (int j = i-1; j >= 0; j--) {
                if (p[j].depth == p[i].depth - 1) {
                    p[i].parent = j;
                    // 把父节点的所有祖先也标记成我的祖先
                    for (int k = 0; k < n; k++) {
                        if (p[j].is_ancestor[k])
                            p[i].is_ancestor[k] = true;
                    }
                    break;
                }
            }
        } else {
            p[i].parent = -1; // 根节点没有父节点
        }
    }

    // 2. 处理每个查询
    // 这个读入好好学一下
    char X[15], tmp[15], type[20], Y[15];
    while (m--) {
        bool res = false;
        scanf("%s is %s %s of %s", X, tmp, type, Y);
        int idx_x = find_id(X, n);
        int idx_y = find_id(Y, n);

        // 五种情况分别判断
        // 这个比较学一下
        if (strcmp(type, "child") == 0) {
            // X是Y的孩子 → X的父就是Y
            res = (p[idx_x].parent == idx_y);
        } else if (strcmp(type, "parent") == 0) {
            // X是Y的父母 → Y的父就是X
            res = (p[idx_y].parent == idx_x);
        } else if (strcmp(type, "sibling") == 0) {
            // X和Y是兄弟 → 父节点同一个
            res = (p[idx_x].parent == p[idx_y].parent);
        } else if (strcmp(type, "descendant") == 0) {
            // X是Y的后代 → Y是X的祖先
            res = p[idx_x].is_ancestor[idx_y];
        } else if (strcmp(type, "ancestor") == 0) {
            // X是Y的祖先 → X是Y的祖先
            res = p[idx_y].is_ancestor[idx_x];
        }

        printf(res ? "True\n" : "False\n");
    }

    return 0;
}
