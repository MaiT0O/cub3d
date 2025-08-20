/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:49:04 by cguinot           #+#    #+#             */
/*   Updated: 2025/08/20 14:38:11 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_array_values(char **visited, t_config *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->map_height)
	{
		j = 0;
		while (j < map->map_width)
		{
			visited[i][j] = '0';
			j++;
		}
		i++;
	}
}

char	**init_visited_array(t_config *map)
{
	char	**visited;
	int		i;

	visited = malloc(sizeof(char *) * map->map_height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < map->map_height)
	{
		visited[i] = malloc(sizeof(char) * map->map_width);
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		i++;
	}
	init_array_values(visited, map);
	return (visited);
}

int	flood_fill(t_config *map, char **visited, int x, int y)
{
	if (map->map[y][x] == ' ')
	{
		return (0);
	}
	if (x < 0 || x >= map->map_width || y < 0 || y >= map->map_height)
		return (0);
	if (map->map[y][x] == '0' && (y == 0 || x == 0 || y == map->map_height - 1
		|| x == map->map_width - 1))
	{
		return (0);
	}
	if (x < 0 || x >= map->map_width || y < 0 || y >= map->map_height
		|| visited[y][x] == '1' || map->map[y][x] == '1')
		return (1);
	visited[y][x] = '1';
	return (flood_fill(map, visited, x + 1, y)
		&& flood_fill(map, visited, x - 1, y)
		&& flood_fill(map, visited, x, y + 1)
		&& flood_fill(map, visited, x, y - 1));
	return (1);
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

int	check_spawn(char **map, t_config *config, int i, int j)
{
	int	found;

	found = 0;
	while (map[++i])
	{
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (found)
				{
					ft_putendl_fd("Error: multiple player positions\n", 2);
					exit(EXIT_FAILURE);
					return (0);
				}
				config->player.boussole = map[i][j];
				config->player.mapX = j;
				config->player.mapY = i;
				found = 1;
			}
		}
	}
	return (1);
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
	if (!check_spawn(new_map, config, -1, -1))
		return (0);
	config->map = new_map;
	config->map_height = map_height;
	return (1);
}
