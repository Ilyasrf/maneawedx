#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int balance = 0;

int ft_balance(char *str) {
    int open = 0;
    int close = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '(')
            open++;
        else if (str[i] == ')') {
            if (open > 0)
                open--;
            else
                close++;
        }
    }
    return open + close;
}

void solve(char *str, int change, int pos) {
    char c;

    if (balance == change && !ft_balance(str)) {
        puts(str);
        return ;
    }
    for (int i = pos; str[i]; i++) {
        if (str[i] == '(' || str[i] == ')') {
            c = str[i];
            str[i] = ' ';
            solve(str, change + 1, i + 1);
            str[i] = c;
        }
    }
}

int main(int ac, char **av) {
    (void)ac;
    balance = ft_balance(av[1]);
    solve(av[1], 0, 0);
} 