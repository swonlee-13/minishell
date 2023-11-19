/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:40:34 by seongwol          #+#    #+#             */
/*   Updated: 2023/08/04 14:50:11 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef long long	t_l;
typedef char		t_c;
typedef int			t_i;
typedef void		t_v;
typedef size_t		t_s;

typedef struct s_list
{
	t_v				*content;
	struct s_list	*next;
}	t_list;

//mandatory
t_i	ft_isalpha(int c);
t_i	ft_isdigit(int c);
t_i	ft_isalnum(int c);
t_i	ft_isascii(int c);
t_i	ft_isprint(int c);
t_i	ft_toupper(int c);
t_i	ft_tolower(int c);
t_i	ft_atoi(const char *str);
t_i	ft_strncmp(const char *s1, const char *s2, size_t n);
t_i	ft_strcmp(const char *s1, const char *s2);
t_i	ft_memcmp(const void *s1, const void *s2, size_t n);
t_v	*ft_memset(void *b, int c, size_t len);
t_v	*ft_memchr(const void *s, int c, size_t n);
t_v	*ft_memcpy(void *dst, const void *src, size_t n);
t_v	*ft_memmove(void *dst, const void *src, size_t len);
t_v	*ft_bzero(void *s, size_t n);
t_v	*ft_calloc(size_t count, size_t size);
t_c	*ft_strchr(const char *s, int c);
t_c	*ft_strrchr(const char *s, int c);
t_c	*ft_strnstr(const char *haystack, const char *needle, size_t len);
t_c	*ft_strdup(const char *s1);
t_s	ft_strlen(const char *s);
t_s	ft_strlcpy(char *dst, const char *src, size_t dstsize);
t_s	ft_strlcat(char *dst, const char *src, size_t dstsize);
t_c	*ft_substr(char const *s, unsigned int start, size_t len);
t_c	*ft_strjoin(char const *s1, char const *s2);
t_c	*ft_strtrim(char const *s1, char const *s2);
t_c	**ft_split(char const *s, char c);
t_c	*ft_itoa(int n);
t_c	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
t_v	ft_striteri(char *s, void (*f)(unsigned int, char *));
t_v	ft_putchar_fd(char c, int fd);
t_v	ft_putstr_fd(char *s, int fd);
t_v	ft_putendl_fd(char *s, int fd);
t_v	ft_putnbr_fd(int n, int fd);

//added
t_i	ft_issign(char c);
t_i	ft_isspace(char c);
t_l	ft_atol(const char *str);
t_v	ft_error(char *str);
t_i	ft_strslen(char **strs);
t_v	ft_free(char **strs);
#endif
