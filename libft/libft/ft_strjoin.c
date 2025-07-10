/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:51:32 by cguinot           #+#    #+#             */
/*   Updated: 2024/11/07 10:51:32 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *src1, char const *src2)
{
	char	*copy;
	size_t	i;
	size_t	j;

	copy = malloc(sizeof(char) * (ft_strlen(src1) + ft_strlen(src2) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (src1[i])
	{
		copy[i] = src1[i];
		i++;
	}
	j = 0;
	while (src2[j])
	{
		copy[i + j] = src2[j];
		j++;
	}
	copy[i + j] = '\0';
	return (copy);
}
