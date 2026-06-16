#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define kMaxSize 1001
typedef char TElemSet[kMaxSize];
typedef struct KaryTreeNode *Trie;
struct KaryTreeNode {
    TElemSet data;  /* 数据元素 */
    Trie *child;    /* 孩子指针数组 */
};

void InsertChild(Trie node_ptr, int index, Trie child_ptr)
{
    node_ptr->child[index] = child_ptr;
}


Trie CreateTrieNode(int k)
{
    Trie new_node = (Trie)malloc(sizeof(struct KaryTreeNode));
    new_node->child = (Trie *)malloc(k * sizeof(Trie));
    // 初始化结点：清空数据，所有孩子指针置空
    new_node->data[0] = '\0';
    for (int i = 0; i < k; i++) {
        new_node->child[i] = NULL;
    }
    return new_node;
}


Trie Insert(Trie trie, int k, char s[])
{
    // 根为空时创建根结点
    if (trie == NULL) {
        trie = CreateTrieNode(k);
    }

    Trie cur_ptr = trie;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        int char_idx = s[i] - 'a';
        // 当前字符对应位置为空则创建新结点
        if (cur_ptr->child[char_idx] == NULL) {
            InsertChild(cur_ptr, char_idx, CreateTrieNode(k));
        }
        cur_ptr = cur_ptr->child[char_idx];
        // 当前结点存入从当前位置开始的后缀，方便后续判断完整字符串
        strcpy(cur_ptr->data, s + i);
    }
    return trie;
}


bool IsIn(Trie trie, int k, char s[])
{
    // 空树直接返回不存在
    if (trie == NULL) {
        return false;
    }

    Trie cur_ptr = trie;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        int char_idx = s[i] - 'a';
        if (cur_ptr->child[char_idx] != NULL) {
            cur_ptr = cur_ptr->child[char_idx];
        } else {
            // 有字符不匹配，直接返回不存在
            return false;
        }
    }
    // 遍历完所有字符，通过后缀长度判断是否为完整插入的字符串（而非路径前缀）
    return strlen(cur_ptr->data) == 1;
}


/* 算法5-24：构建后缀树BuildSuffixTree(s, k) */ 
Trie BuildSuffixTree(char s[], int k)
{
    Trie root = NULL;
    int len = strlen(s);
    // 插入原串所有后缀，即可构建后缀树
    for (int i = 0; i < len; i++) {
        root = Insert(root, k, s + i);
    }
    return root;
}

/* 算法5-24 结束 */ 

int main(void)
{
	Trie suffix_trie;
	TElemSet s;
	int n, i;
	
	scanf("%s\n", s);
	suffix_trie = BuildSuffixTree(s, 26);
	scanf("%d\n", &n);
	for (i=0; i<n; i++) {
		scanf("%s\n", s);
		if (IsIn(suffix_trie, 26, s)==true) {
			printf("yes\n");
		}
		else {
			printf("no\n");
		}
	}
		
	return 0;
}
