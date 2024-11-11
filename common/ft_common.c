#include <unistd.h>
#include <stdlib.h>

void ft_swap(char *a, char *b)
{
	char t = *a;
	*a = *b;
	*b = t;
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putstr(char *str)
{
	int i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void ft_putnbr(int nb)
{
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb < 10)
		ft_putchar(nb + '0');
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}

int ft_atoi(char *str)
{
	int i = 0;
	int res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

int ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

int ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

int ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 'A');
	return (c);
}

int ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 'a');
	return (c);
}

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

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

char *ft_strcat(char *dest, char *src)
{
	int i = 0;
	int j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *s = ft_strdup(s1);
	char *t = ft_strdup(s2);
	return (ft_strcat(s, t));
}

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int ft_strncmp(char *s1, char *s2, unsigned int n)
{
	int i = 0;
	while (s1[i] && s1[i] == s2[i] && i < n)
		i++;
	return (s1[i] - s2[i]);
}

char *ft_strcpy(char *dest, char *src)
{
	int i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *ft_strncpy(char *dest, char *src, unsigned int n)
{
	int i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char *ft_strchr(char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

char *ft_strrchr(char *str, int c)
{
	while (*str)
		str++;
	while (str--)
	{
		if (*str == c)
			return (str);
	}
	return (NULL);
}

int factorial(int n)
{
    int f = 1;
    while (n > 1)
		f *= n--;
    return f;
}

void sort(char *s) {
    int n = ft_strlen(s);
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1; j++)
            if (s[j] > s[j + 1])
                swap(&s[j], &s[j + 1]);
}
