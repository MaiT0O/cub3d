/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:20:24 by ebansse           #+#    #+#             */
/*   Updated: 2025/09/11 17:01:45 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float delta_x, float delta_y, t_config *game)
{
	float	angle;
	float	fix_dist;

	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

bool	touch(float px, float py, t_config *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (x < 0 || y < 0 || y >= game->map_height || x >= game->map_width)
		return (true);
	if (!game->map[y] || (int)ft_strlen(game->map[y]) <= x)
		return (true);
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

int	is_only_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r')
			return (printf("Error\nUnknown argument: %s", line), 0);
		i++;
	}
	return (1);
}

int	handle_player_tile(t_config *config, char **visited, int i, int j)
{
	if (config->player.map_x != -1 && config->player.map_y != -1)
		return (printf("Error\ndouble player detected\n"),
			free_visited(visited, config->map_height), 0);
	config->player.map_x = j;
	config->player.map_y = i;
	if (j == 0 || i == 0 || j == config->map_width - 1
		|| i == config->map_height - 1)
		return (printf("Error\nSpawn out of map\n")
			, free_visited(visited, config->map_height), 0);
	config->player.boussole = config->map[i][j];
	if (!flood_fill(config, visited, j, i))
		return (printf("Error\nMap not closed\n")
			, free_visited(visited, config->map_height), 0);
	return (1);
}
