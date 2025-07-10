/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:17:22 by cguinot           #+#    #+#             */
/*   Updated: 2024/11/07 11:17:22 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include "../get_next_line/get_next_line.h"

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *src, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *d, const char *src, size_t destsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(char *str, int c);
char	*ft_strrchr(const char *str, int c);
int		ft_strncmp(char *first, char *second, size_t n);
void	*ft_memchr(const void *src, int c, size_t len);
int		ft_memcmp(const void *src1, const void *src2, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t len);
char	*ft_strdup(const char *src);

char	*ft_substr(char const *src, unsigned int start, size_t len);
char	*ft_strjoin(char const *src1, char const *src2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *src, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif