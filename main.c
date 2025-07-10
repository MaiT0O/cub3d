/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:30:11 by cguinot           #+#    #+#             */
/*   Updated: 2025/07/10 18:52:44 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_visited(char **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

int	map_closed(t_config *config)
{
	int		i;
	int		j;
	char	**visited;

	i = 0;
	j = 0;
	visited = init_visited_array(config);
	while (config->map[i] && i < config->map_height)
	{
		j = 0;
		while (config->map[i][j])
		{
			if (config->map[i][j] == 'N' || config->map[i][j] == 'S'
				|| config->map[i][j] == 'E' || config->map[i][j] == 'W')
			{
				config->player_x = j;
				config->player_y = i;
				if (!flood_fill(config, visited, j, i))
					return (free_visited(visited, config-> map_height), 0);
			}
			j++;
		}
		i++;
	}
	return (free_visited(visited, config-> map_height), 1);
}

int	parsing(char *filename, t_config *config)
{
	char	*line;
	int		text_count;
	int		fd;

	text_count = 0;
	if (!check_extension(filename))
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error cannot open file \n"), 0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (text_parse(config, line))
			text_count += 1;
		free(line);
		line = get_next_line(fd);
	}
	if (text_count != 6)
	{
		printf("Error not enough textures \n");
		return (0);
	}
	return (free(line), close(fd), 1);
}

int	main(int argc, char **argv)
{
	t_config	config = {0};

	free_and_init_config(&config, 0);
	if (argc != 2)
		return (printf("Error format ./cub3d [map_file] \n"), 0);
	else
	{
		if (!parsing(argv[1], &config))
		{
			free_and_init_config(&config, 1);
			return (printf("Error in map descriptor\n"), 0);
		}
		if (!map_closed(&config))
		{
			free_and_init_config(&config, 1);
			return (printf("Error in player or wall\n"), 0);
		}
	}
	display_config(&config);
	display_map(&config);
	free_and_init_config(&config, 1);
}
