/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:51:17 by cguinot           #+#    #+#             */
/*   Updated: 2024/11/07 10:51:17 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static void	fill_line(char *new, char const *src, char c)
{
	size_t	i;

	i = 0;
	while (src[i] && src[i] != c)
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
}

static void	fill_tab(char **tab, char const *src, char c)
{
	size_t	count;
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (src[j])
	{
		count = 0;
		while (src[j + count] && src[j + count] != c)
			count++;
		if (count > 0)
		{
			tab[i] = malloc(sizeof(char) * (count + 1));
			if (!tab[i])
				return ;
			fill_line(tab[i], (src + j), c);
			i++;
			j = j + count;
		}
		else
			j++;
	}
	tab[i] = NULL;
}

char	**ft_split(char const *src, char c)
{
	size_t	words;
	char	**tab;

	words = count_words(src, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	fill_tab(tab, src, c);
	return (tab);
}
