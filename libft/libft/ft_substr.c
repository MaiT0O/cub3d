/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:52:03 by cguinot           #+#    #+#             */
/*   Updated: 2024/11/07 10:52:03 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *src, unsigned int start, size_t len)
{
	char			*copy;
	unsigned int	i;

	if (start >= ft_strlen(src))
		len = 0;
	else if (len > ft_strlen(src + start))
		len = ft_strlen(src + start);
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (start + i < ft_strlen(src) && i < len)
	{
		copy[i] = src[start + i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
