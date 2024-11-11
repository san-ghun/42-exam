#include <unistd.h>
#include <stdlib.h>

void swap(char *a, char *b) {
    char t = *a;
    *a = *b;
    *b = t;
}

void print(char *s) {
    while (*s) write(1, s++, 1);
    write(1, "\n", 1);
}

void perm(char *s, int l, int r) {
    if (l == r) {
        print(s);
        return;
    }
    for (int i = l; i <= r; i++) {
        swap(s + l, s + i);
        perm(s, l + 1, r);
        swap(s + l, s + i);
    }
}

int len(char *s) {
    int i = 0;
    while (s[i]) i++;
    return i;
}

void sort(char *s) {
    int n = len(s);
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1; j++)
            if (s[j] > s[j + 1])
                swap(&s[j], &s[j + 1]);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        write(2, "Usage: ./a.out <string>\n", 23);
        exit(1);
    }
    sort(argv[1]);
    perm(argv[1], 0, len(argv[1]) - 1);
    return 0;
}
