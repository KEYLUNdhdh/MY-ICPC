typedef int ElemSet;
ElemSet **Create2DArray(int row, int col)
{	/* 动态声明row行col列的二维数组 */
	ElemSet *a, **t;
	int i;

	a = (ElemSet *)malloc(sizeof(ElemSet) * row * col);
	t = (ElemSet **)malloc(sizeof(ElemSet *) * row);
	for (i=0; i<row; i++)
		t[i] = &a[col*i];
	return t;
}

void Free2DArray (ElemSet **t)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int Max( int x, int y )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void GetLCS(char x[], int i, char y[], int j, int **l, char *seq, int idx)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int LCS(char x[], int n, char y[], int m)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


