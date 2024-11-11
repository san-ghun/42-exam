#include <unistd.h>
#include <stdlib.h>

#define MAX_LEN 10
#define MAX_PERM 3628800  // 10!

char perms[MAX_PERM][MAX_LEN];  // Array to store all permutations
int perm_count = 0;

void swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

int len(char *s)
{
    int i = 0;
    while (s[i]) i++;
    return i;
}

void store(char *s)
{
    int i = 0;
    while (s[i]) {
        perms[perm_count][i] = s[i];
        i++;
    }
    perms[perm_count][i] = '\0';
    perm_count++;
}

void perm(char *s, int l, int r)
{
    if (l == r)
    {
        store(s);
        return;
    }
    for (int i = l; i <= r; i++)
    {
        swap(s + l, s + i);
        perm(s, l + 1, r);
        swap(s + l, s + i);
    }
}

int str_cmp(const char *s1, const char *s2)
{
    while (*s1 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

void sort_perms()
{
    char temp[MAX_LEN];
    for (int i = 0; i < perm_count - 1; i++)
    {
        for (int j = 0; j < perm_count - 1 - i; j++)
        {
            if (str_cmp(perms[j], perms[j + 1]) > 0)
            {
                int k = 0;
                while (perms[j][k])
                {
                    temp[k] = perms[j][k];
                    k++;
                }
                temp[k] = '\0';

                k = 0;
                while (perms[j + 1][k])
                {
                    perms[j][k] = perms[j + 1][k];
                    k++;
                }
                perms[j][k] = '\0';

                k = 0;
                while (temp[k])
                {
                    perms[j + 1][k] = temp[k];
                    k++;
                }
                perms[j + 1][k] = '\0';
            }
        }
    }
}

void print_perms()
{
    for (int i = 0; i < perm_count; i++)
    {
        int j = 0;
        while (perms[i][j])
        {
            write(1, &perms[i][j], 1);
            j++;
        }
        write(1, "\n", 1);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        write(2, "Usage: ./a.out <string>\n", 23);
        exit(1);
    }
    
    if (len(argv[1]) >= MAX_LEN)
    {
        write(2, "String too long\n", 15);
        exit(1);
    }
    
    perm(argv[1], 0, len(argv[1]) - 1);
    sort_perms();
    print_perms();
    
    return 0;
}
