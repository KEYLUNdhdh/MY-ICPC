#include <stdio.h>
#include <stdlib.h>

const int MAXLEN = 1e5 + 10;
// 本题要求实现
void max_burst_location(int n, int h, int balloons[], int *pos, int *count)
{
    *pos = -1;
    *count = 0;
    int tmppos = balloons[0];
    int end = 0;
    for (int i = 0; i < n;i++)
    {
        while(end < n && balloons[end] <= balloons[i] + h)
            end++;
        int len = end - i;
        if(len > *count)
        {
            *count = len;
            *pos = balloons[i];
        }
    }
}

int main() {
    int n, h;
    scanf("%d %d", &n, &h);

    int balloons[MAXLEN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &balloons[i]);
    }
    
    int position, count;
    max_burst_location(n, h, balloons, &position, &count);

    printf("%d %d", position, count);
    return 0;
}