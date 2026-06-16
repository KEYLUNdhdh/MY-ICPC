
int Max( int x, int y )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


bool IsCompatible(Activities a, int *room, int i, int k)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int ActivityScheduling(Activities a, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}
 

/* 更快的解决方案 */
//int ActivityScheduling(Activities a, int n)
//{ /* n个活动按照 a[i].start的非递减序存放 */
//	int *m, *room, i, k;
//	
//	m = (int *)malloc(sizeof(int) * (n+1));
//	room = (int *)malloc(sizeof(int) * (n+1));
//	m[0] = 1;    /* 第0个活动占用1个教室 */
//	room[1] = 0; /* 1号教室的最迟结束时间为0 */
//	for (i=1; i<=n; i++) {
//		/* 找到i可以排入的第一个教室的序号 */ 
//		for (k=1; k<=m[i-1]; k++) {
//			if (room[k] <= a[i].start) { /* 若i可以被放入第k个教室 */
//				break;
//			}
//		}
//		/* 如果i放不进任何教室，则k= m[i-1]+1 */ 
//		m[i] = Max(m[i-1], k);
//		room[k] = a[i].finish; /* 将i排入教室k */
//	}
//	return m[n];
//} 

