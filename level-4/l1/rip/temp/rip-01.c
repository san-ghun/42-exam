#include <unistd.h>
#include <stdlib.h>

// Custom string length function
int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

// Custom string duplication
char *ft_strdup(char *str)
{
    int len = ft_strlen(str);
    char *dup = malloc(len + 1);
    int i = 0;

    if (!dup)
        return (NULL);
    while (str[i])
    {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

// Write number function for debugging
void ft_putnbr(int n)
{
    char digit;
    
    if (n >= 10)
        ft_putnbr(n / 10);
    digit = (n % 10) + '0';
    write(1, &digit, 1);
}

// Check if string has valid parentheses
int is_valid(char *str)
{
    int count = 0;
    int i = 0;

    while (str[i])
    {
        if (str[i] == '(')
            count++;
        else if (str[i] == ')')
        {
            count--;
            if (count < 0)
                return (0);
        }
        i++;
    }
    return (count == 0);
}

// Print string followed by newline
void print_result(char *str)
{
    write(1, str, ft_strlen(str));
    write(1, "\n", 1);
}

// Try removing characters one by one
void solve(char *str)
{
    int len = ft_strlen(str);
    int i;
    int j;
    char *temp;

    // Try removing each character
    for (i = 0; i < len; i++)
    {
        if (str[i] != '(' && str[i] != ')')
            continue;
            
        // Create temporary string without current character
        temp = malloc(len);
        if (!temp)
            return;
            
        // Copy string without character at position i
        for (j = 0; j < i; j++)
            temp[j] = str[j];
        for (j = i; j < len - 1; j++)
            temp[j] = str[j + 1];
        temp[len - 1] = '\0';

        // Check if valid and print
        if (is_valid(temp))
            print_result(temp);
            
        free(temp);
    }
}

int main(int ac, char **av)
{
    char *str;

    // Check arguments
    if (ac != 2)
    {
        write(2, "Usage: ./program \"parentheses\"\n", 29);
        return (1);
    }

    str = av[1];
    
    // Check if already valid
    if (is_valid(str))
    {
        write(1, "Already valid: ", 14);
        print_result(str);
        return (0);
    }

    // Find and print valid combinations
    write(1, "Valid combinations:\n", 19);
    solve(str);

    return (0);
}
