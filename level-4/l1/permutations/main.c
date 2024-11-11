// permutations-malloc.c

#include <unistd.h>
#include <stdlib.h>

char **perms;  // Dynamic array to store permutations
int perm_count = 0;
int str_len;

void swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

int len(char *s)
{
    int i = 0;
    while (s[i])
		i++;
    return i;
}

int factorial(int n)
{
    int f = 1;
    while (n > 1)
		f *= n--;
    return f;
}

void store(char *s)
{
    perms[perm_count] = (char *)malloc(str_len + 1);
    int i = 0;
    while (s[i])
	{
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
    for (int i = 0; i < perm_count - 1; i++)
	{
        for (int j = 0; j < perm_count - 1 - i; j++)
		{
            if (str_cmp(perms[j], perms[j + 1]) > 0)
			{
                char *temp = perms[j];
                perms[j] = perms[j + 1];
                perms[j + 1] = temp;
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

void free_perms()
{
    for (int i = 0; i < perm_count; i++)
        free(perms[i]);
    free(perms);
}

int main(int argc, char **argv)
{
    if (argc != 2)
	{
        write(2, "Usage: ./a.out <string>\n", 23);
        exit(1);
    }
    
    str_len = len(argv[1]);
    int total_perms = factorial(str_len);
    
    // Allocate memory for array of string pointers
    perms = (char **)malloc(total_perms * sizeof(char *));
    if (!perms)
	{
        write(2, "Memory allocation failed\n", 23);
        exit(1);
    }
    
    perm(argv[1], 0, str_len - 1);
    sort_perms();
    print_perms();
    
    free_perms();
    return 0;
}
