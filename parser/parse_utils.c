/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:40:54 by ebansse           #+#    #+#             */
/*   Updated: 2025/09/25 17:01:29 by ebansse          ###   ########.fr       */
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

int	is_line_color(char *line)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_isdigit(line[i]) && line[i] != ',' && line[i] != ' ' && line[i] != '\t')
			return (printf("Error\ninvalid color\n"), 0);
		i++;
	}
	return (1);
}

int	is_only_digit(char *nb)
{
	int	i;

	i = 0;
	if (nb[i] == '\0')
		return (0);
	while (nb[i])
	{
		if (!ft_isdigit(nb[i]))
			return (0);
		i++;
	}
	return (1);
}
