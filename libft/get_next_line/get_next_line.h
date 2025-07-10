/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:33:57 by cguinot           #+#    #+#             */
/*   Updated: 2025/01/08 15:33:57 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*gnl_ft_strjoin(char *s1, char *s2);
char	*gnl_ft_strchr(char *s, int c);
size_t	gnl_ft_strlen(char *s);
char	*ft_extract_line(char *str);
char	*ft_save_remainder(char *str);

#endif