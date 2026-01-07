#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

char *s;

void error() {
    if (*s)
        printf("Unexpected token '%c'\n", *s);
    else
        printf("Unexpected end of input\n");
    exit(1);
}

int expr();

int factor() {
    int res;

    if (isdigit(*s)) return (*s++ - '0');
    if (*s == '(') {
        s++;
        res = expr();
        if (*s != ')')
            error();
        s++;
        return (res);
    }
    error();
    return (0);
}

int term() {
    int left = factor();

    while (*s == '*') {
        s++;
        left *= factor();
    }
    return (left);
}

int expr() {
    int left = term();

    while (*s == '+') {
        s++;
        left += term();
    }
    return left;
}

int main(int ac, char **av) {
    if (ac != 2)
        return 1;
    s = av[1];
    int res = expr();
    if (*s) error();
    printf("%d", res);
}