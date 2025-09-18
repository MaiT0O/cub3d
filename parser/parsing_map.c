/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:49:04 by cguinot           #+#    #+#             */
/*   Updated: 2025/09/18 18:43:18 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	normalize_map_lines(t_config *config)
{
	int		i;
	char	*new_line;

	i = 0;
	while (i < config->map_height)
	{
		if ((int)ft_strlen(config->map[i]) < config->map_width)
		{
			new_line = create_normalized_line(config->map[i],
					config->map_width);
			if (new_line)
			{
				free(config->map[i]);
				config->map[i] = new_line;
			}
		}
		i++;
	}
}

char	**init_visited_array(t_config *map)
{
	char	**visited;
	int		i;

	normalize_map_lines(map);
	visited = malloc(sizeof(char *) * map->map_height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < map->map_height)
	{
		visited[i] = malloc(sizeof(char) * (map->map_width + 1));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		init_visited_line(visited[i], map->map_width);
		i++;
	}
	return (visited);
}

int	is_map_line(char *line)
{
	int	i;
	int	has_map_char;

	i = 0;
	has_map_char = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			has_map_char = 1;
		else if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (has_map_char);
}

int	add_map_line(t_config *config, char *line)
{
	int		i;
	char	**new_map;
	int		map_height;
	int		new_width;

	map_height = config->map_height + 1;
	new_map = malloc(sizeof(char *) * (map_height + 1));
	if (!new_map)
		return (0);
	i = -1;
	while (++i < config -> map_height)
		new_map[i] = config->map[i];
	new_map[config->map_height] = ft_strdup(line);
	new_width = ft_strlen(new_map[config->map_height]);
	new_map[map_height] = NULL;
	free(config->map);
	if (config->map_width < new_width)
		config->map_width = new_width;
	config->map = new_map;
	config->map_height = map_height;
	return (1);
}
