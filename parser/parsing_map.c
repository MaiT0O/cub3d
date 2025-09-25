/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:49:04 by cguinot           #+#    #+#             */
/*   Updated: 2025/09/23 20:01:36 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	find_player(t_config *config)
{
	int		x;
	int		y;

	x = 0;
	while (config->map[x])
	{
		y = 0;
		while (config->map[x][y])
		{
			if (config->map[x][y] == 'N' || config->map[x][y] == 'S'
						|| config->map[x][y] == 'E' || config->map[x][y] == 'W')
			{
				if (!handle_player_tile(config, x, y))
					return (0);
				else
					config->map[x][y] = '0';
			}
			y++;
		}
		x++;
	}
	return (1);
}

int	is_position_valid(t_config *config, int x, int y)
{
	if (x < 0 || x >= config->map_height)
		return (0);
	if (y < 0)
		return (0);
	if (!config->map[x])
		return (0);
	if (y >= (int)ft_strlen(config->map[x]))
		return (0);
	return (1);
}

int	check_zero_neighbors(t_config *config, int x, int y)
{
	if (x == 0 || y == 0)
		return (0);
	if (!is_position_valid(config, x - 1, y))
		return (0);
	if (config->map[x - 1][y] != '0' && config->map[x - 1][y] != '1')
		return (0);
	if (!is_position_valid(config, x + 1, y))
		return (0);
	if (config->map[x + 1][y] != '0' && config->map[x + 1][y] != '1')
		return (0);
	if (!is_position_valid(config, x, y - 1))
		return (0);
	if (config->map[x][y - 1] != '0' && config->map[x][y - 1] != '1')
		return (0);
	if (!is_position_valid(config, x, y + 1))
		return (0);
	if (config->map[x][y + 1] != '0' && config->map[x][y + 1] != '1')
		return (0);
	return (1);
}
