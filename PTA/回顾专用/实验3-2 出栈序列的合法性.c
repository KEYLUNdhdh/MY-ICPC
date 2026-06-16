#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1005

int a[MAXN];
int main()
{
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);

    while(k--)
    {
        for (int i = 0; i < n;i++)
            scanf("%d", &a[i]);

        int f = 1;
        for (int i = 0; i < n;i++)
        {
            int num = a[i];
            int maxx = 1000000000;
            int cnt = 0;
            for (int j = i + 1; j < n;j++)
            {
                if(a[j] < num)
                {
                    cnt++;
                    if(cnt >= m)
                    {
                        f = 0;
                        printf("NO\n");
                        break;
                    }
                    if(a[j] < maxx)
                    {
                        maxx = a[j];
                    }
                    else
                    {
                        f = 0;
                        printf("NO\n");
                        break;
                    }
                }
            }
            if(f == 0)
                break;
        }
        if(f)
            printf("YES\n");
    }
}