/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:40:54 by ebansse           #+#    #+#             */
/*   Updated: 2025/09/29 15:30:29 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_visited_line(char *visited_line, int width)
{
	int	j;

	j = 0;
	while (j < width)
	{
		visited_line[j] = '0';
		j++;
	}
	visited_line[width] = '\0';
}

char	*create_normalized_line(char *original_line, int target_width)
{
	char	*new_line;
	int		current_len;
	int		j;

	current_len = ft_strlen(original_line);
	if (current_len >= target_width)
		return (NULL);
	new_line = malloc(target_width + 1);
	if (!new_line)
		return (NULL);
	j = 0;
	while (j < current_len && original_line[j] != '\n')
	{
		new_line[j] = original_line[j];
		j++;
	}
	while (j < target_width)
	{
		new_line[j] = ' ';
		j++;
	}
	new_line[target_width] = '\0';
	return (new_line);
}

int	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
	{
		printf("Error\nFilename too short\n");
		return (0);
	}
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
	{
		printf("Error\nwrong extension \n");
		return (0);
	}
	return (1);
}
