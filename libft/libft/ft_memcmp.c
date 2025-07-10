/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcomp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:50:58 by cguinot           #+#    #+#             */
/*   Updated: 2024/11/07 10:50:58 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *src1, const void *src2, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && *(unsigned char *)(src1 + i) == *(unsigned char *)(src2
			+ i))
		i++;
	if (i < len)
		return (*(unsigned char *)(src1 + i) - *(unsigned char *)(src2 + i));
	return (0);
}
