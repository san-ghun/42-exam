#ifndef FT_COMMON_H
#define FT_COMMON_H

#include <unistd.h>
#include <stdlib.h>

void ft_putchar(char c);
void ft_putstr(char *str);
void ft_putnbr(int nb);

int ft_atoi(char *str);

int ft_isdigit(int c);
int ft_isalpha(int c);
int ft_isalnum(int c);
int ft_isprint(int c);
int ft_toupper(int c);
int ft_tolower(int c);

int ft_strlen(char *str);
char *ft_strdup(char *str);
char *ft_strcat(char *dest, char *src);
char *ft_strjoin(char *s1, char *s2);
int ft_strcmp(char *s1, char *s2);
int ft_strncmp(char *s1, char *s2, unsigned int n);
char *ft_strcpy(char *dest, char *src);
char *ft_strncpy(char *dest, char *src, unsigned int n);
char *ft_strchr(char *str, int c);
char *ft_strrchr(char *str, int c);

void ft_swap(char *a, char *b);

int factorial(int n);
void sort(char *s);

#endif