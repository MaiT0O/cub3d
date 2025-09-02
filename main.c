/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:30:11 by cguinot           #+#    #+#             */
/*   Updated: 2025/09/02 13:53:04 by ebansse          ###   ########.fr       */
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
	visited = init_visited_array(config);
	while (config->map[i] && i < config->map_height)
	{
		j = 0;
		while (config->map[i][j])
		{
			if (config->map[i][j] == 'N' || config->map[i][j] == 'S'
				|| config->map[i][j] == 'E' || config->map[i][j] == 'W')
			{
				config->player.mapX = j;
				config->player.mapY = i;
				config->player.boussole = config->map[i][j];
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

int		initialisation(t_config *config, char **argv)
{
	config->mlx_ptr = NULL;
	config->win_ptr = NULL;
	init_config(config);
	if (!parsing(argv[1], config))
	{
		printf("Error in map descriptor\n");
		free_all(config);
		return (0);
	}
	if (!map_closed(config))
	{
		printf("Error in player or wall\n");
		free_all(config);
		return (0);
	}
	config->mlx_ptr = mlx_init();
	init_textures(config);
	init_player(&config->player, config);
	return (1);
}

int init_game(t_config *config)
{
	config->win_ptr = mlx_new_window(config->mlx_ptr, WIN_W, WIN_H, "cub3d");
	config->frame.img = mlx_new_image(config->mlx_ptr, WIN_W, WIN_H);
	config->frame.addr = mlx_get_data_addr(config->frame.img, &config->frame.bpp
		, &config->frame.line_length, &config->frame.endian);
	mlx_put_image_to_window(config->mlx_ptr, config->win_ptr
		, config->frame.img, 0, 0);
	return (0);
}




int	main(int argc, char **argv)
{
	t_config	config;

	if (argc != 2)
		return (printf("Error format ./cub3d [map_file] \n"), 0);
	else
	{
		if (initialisation(&config, argv))
		{
			display_config(&config);
			init_game(&config);
			printf("map width : %d / map_heigth : %d\n", config.map_width, config.map_height);
			mlx_hook(config.win_ptr, 17, 0, free_all, &config);
			mlx_hook(config.win_ptr, 2, 1L<<0, key_press, &config);
			mlx_hook(config.win_ptr, 3, 1L<<1, key_release, &config.player);
			mlx_loop_hook(config.mlx_ptr, draw_loop, &config);
			mlx_loop(config.mlx_ptr);
		}
	}
	free_all(&config);
	return (0);
}
