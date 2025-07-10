/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:50:34 by cguinot           #+#    #+#             */
/*   Updated: 2024/11/07 10:50:34 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nbr, size_t size)
{
	void	*adresse;

	if (nbr == 0 || size == 0)
	{
		nbr = 1;
		size = 1;
	}
	adresse = malloc(nbr * size);
	if (!adresse)
	{
		return (NULL);
	}
	ft_bzero(adresse, size * nbr);
	return (adresse);
}
