#include <stdio.h>
#include <memory.h>

#define kMaxV 500 /* 硬币的最大面值 */

int main(void)
{
	int n, m, v, i;
	int cnt[kMaxV+1]; /* 数组下标从0开始，cnt[0]冗余 */
	
	memset(cnt, 0, kMaxV+1); /* 初始化映射计数器为0 */
	scanf("%d %d", &n, &m);
	for (i=0; i<n; i++) {
		scanf("%d", &v);
		cnt[v]++; /* 将面值映射到计数器，对应计数器增1 */
	}
	for (v=1; v<=kMaxV; v++) { /* 顺序扫描每个可能的面值 */
		if (cnt[v] > 0) { /* 如果有这个面值的硬币 */
			cnt[v]--;   /* 取出该硬币，即该面值对应的计数器减1 */
			if ((m-v)>0 && (m-v)<=kMaxV && cnt[m-v]>0) {
				/* 如果面值为(m-v)的硬币是存在的 */
				printf("%d %d\n", v, m-v);
				break; /* 任务完成，退出循环 */
			}
		}
	}
	if (v > kMaxV) {  /* 若直到循环结束都没找到解 */
		printf("No Solution\n");
	}
	return 0;
}

