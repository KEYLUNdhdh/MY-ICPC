#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int n;
    scanf("%d\n", &n);
    char token[1005];
    char **ss = (char **)malloc((2005) * sizeof(char *));
    for (int i = 0; i < n;i++)
    {
        ss[i] =  (char*)malloc(26 * sizeof(char));
        fgets(ss[i], 25, stdin);
        for (int j = 0; j < 25;j++)
            if(ss[i][j] == '\n')
            {
                ss[i][j] = '\0';
                break;
            }
    }

    char *t = (char *)malloc(sizeof(char) * 30005);
    fgets(t, 30005, stdin);
    int idx = n;
    char *p = strtok(t, " \n");
    while(p)
    {
        strcpy(token, p);
        if(strcmp(token, "#") == 0)
            break;
        int f = 0;
        for (int i = 0; i < idx;i++)
        {
            if(strcmp(token, ss[i]) == 0)
            {
                f = 1;
                break;
            }
        }

        p = strtok(NULL, " \n");
        if(!f)
        {
            printf("%s\n", token);
            ss[idx] =  (char*)malloc(26 * sizeof(char));
            strcpy(ss[idx], token);
            idx++;
        }
    }
}