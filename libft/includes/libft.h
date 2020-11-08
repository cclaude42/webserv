/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:32:51 by cclaude           #+#    #+#             */
/*   Updated: 2020/11/08 12:54:41 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

# include "get_next_line.h"
# include "ft_printf.h"

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_iscount(int c, char *base);
int					ft_isdigit(int c);
int					ft_isin(int c, char *base);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_isspacenl(int c);

void				ft_lstadd_back(t_list **alst, t_list *newt);
void				ft_lstadd_front(t_list **alst, t_list *newt);
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void*),
					void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);

int					ft_abs(long n);
int					ft_nbrlen(long n);
int					ft_hexlen(long n);
int					ft_baselen(long n, int base);
int					ft_power(int nbr, int pow);

void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memdel(void *ptr);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);

void				ft_putchar(char c);
void				ft_putendl(char *s);
void				ft_putnbr(int n);
void				ft_putstr(char *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);

void				ft_skip_space(const char *str, int *i);
void				ft_skip_spacenl(const char *str, int *i);
void				ft_skip_char(const char *str, int *i, char c);
void				ft_skip_chars(const char *str, int *i, char *base);

char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(const char *s1);
int					ft_strisnum(const char *str);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack,
					const char *needle, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);

int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
#endif
