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

void InsertChild(Trie node_ptr, int index, Trie child_ptr);
Trie CreateTrieNode(int k);
Trie Insert(Trie trie, int k, char s[]);
bool IsIn(Trie trie, int k, char s[]);

int main(void)
{
	Trie trie;
	TElemSet s;
	int n, i;
	
	trie = NULL;
	scanf("%d\n", &n);
	for (i=0; i<n; i++) {
		scanf("%s\n", s);
		trie = Insert(trie, 26, s);
	}
	scanf("%d\n", &n);
	for (i=0; i<n; i++) {
		scanf("%s\n", s);
		if (IsIn(trie, 26, s)==true) {
			printf("yes\n");
		}
		else {
			printf("no\n");
		}
	}
		
	return 0;
}

void InsertChild(Trie node_ptr, int index, Trie child_ptr)
{
	node_ptr->child[index] = child_ptr;
}


/* 算法5-21：创建前缀树结点 CreateTrieNode(k) */ 
Trie CreateTrieNode(int k)
{
	Trie node = (Trie)malloc(sizeof(struct KaryTreeNode));
	node->child = (Trie *)malloc(k * sizeof(Trie));

	node->data[0] = '\0';
	for (int i = 0; i < k;i++)
		node->child[i] = NULL;

	return node;
}

/* 算法5-21 结束 */ 

/* 算法5-22：前缀树中插入字符串 Insert(trie, k, s) */ 
Trie Insert(Trie trie, int k, char s[])
{
    if(trie == NULL)
		trie = CreateTrieNode(k);

	Trie cur = trie;
	int len = strlen(s);
	for (int i = 0; i < len;i++)
	{
		int idx = s[i] - 'a';
		if(cur->child[idx] == NULL)
			InsertChild(cur, idx, CreateTrieNode(k));

		cur = cur->child[idx];
		strcpy(cur->data, s + i);
	}
	return trie;
}

/* 算法5-22 结束 */ 

/* 算法5-23：判断给定字符串是否在前缀树中 IsIn(trie, k, s) */ 
bool IsIn(Trie trie, int k, char s[])
{
    if(trie == NULL)
    	return 0;

	Trie cur = trie;
	int len = strlen(s);
	for (int i = 0; i < len;i++)
	{
		int idx = s[i] - 'a';
		if(cur->child[idx])
			cur = cur->child[idx];
		else
			return 0;
	}
	for (int i = 0; i < 26;i++)
	{
		if(cur->child[i] != NULL)
			return 0;
	}
	return 1;
}

/* 算法5-23 结束 */ 

