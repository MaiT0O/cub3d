/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:50:55 by cguinot           #+#    #+#             */
/*   Updated: 2024/11/07 10:50:55 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (*(unsigned char *)(src + i) == (unsigned char)c)
			return ((void *)src + i);
		i++;
	}
	return (NULL);
}
