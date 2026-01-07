#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_safe(int *tab, int col, int row)
{
    for(int i = 0; i < col; i++)
    {
        int j = tab[i];
        if(j == row || j - i == row - col || j + i == row + col)
            return 0;
    }
    return 1;
}
void solve(int *tab, int col, int n)
{
    if(col == n)
    {
        for(int i = 0; i < n; i++)
        {
            if(i > 0)
                printf (" ");
            printf("%d", tab[i]);
        }
        printf("\n");
        return;
    }
    for(int i = 0; i < n; i++)
    {
        if(is_safe(tab, col, i))
        {
            tab[col] = i;
            solve(tab, col + 1, n);
        }
    }
}
int main(int ac, char **av)
{
    if(ac == 2 && av[1][0] != '-')
    {
        int n = atoi(av[1]);
        int *tab = calloc(sizeof(int), n);
        solve(tab, 0, n);
    }
    return 0;
}