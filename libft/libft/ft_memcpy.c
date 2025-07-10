/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:51:01 by cguinot           #+#    #+#             */
/*   Updated: 2024/11/07 10:51:01 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t	i;

	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*(char *)(dest + i) = *(char *)(src + i);
		i++;
	}
	return (dest);
}
