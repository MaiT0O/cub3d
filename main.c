/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:30:11 by cguinot           #+#    #+#             */
/*   Updated: 2025/09/11 14:14:17 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_closed(t_config *config)
{
	char	**visited;
	int		i;
	int		j;

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
				if (!handle_player_tile(config, visited, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (free_visited(visited, config->map_height), 1);
}

int	parsing(char *filename, t_config *config)
{
	char	*line;
	int		text_count;
	int		fd;
	int		res;

	text_count = 0;
	if (!check_extension(filename))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error\ncannot open file"), 0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		res = text_parse(config, line, text_count);
		if (res == 1)
			text_count += 1;
		else if (res == 2)
			return (cleanup_and_exit(fd, line, 0));
		free(line);
		line = get_next_line(fd);
	}
	if (config->map_height <= 0)
		return (printf("Error\nNo map"), free(line), close(fd), 0);
	return (free(line), close(fd), 1);
}

int	initialisation(t_config *config, char **argv)
{
	config->mlx_ptr = NULL;
	config->win_ptr = NULL;
	config->player.map_x = -1;
	config->player.map_y = -1;
	init_config(config);
	if (!parsing(argv[1], config))
		return (free_all(config), 0);
	if (!map_closed(config))
		return (free_all(config), 0);
	if (config->player.map_x == -1)
		return (printf ("Error\nNo player"), free_all (config), 0);
	config->mlx_ptr = mlx_init();
	init_textures(config);
	init_player(&config->player);
	return (1);
}

int	init_game(t_config *config)
{
	config->win_ptr = mlx_new_window(config->mlx_ptr, WIN_W, WIN_H, "cub3d");
	config->frame.img = mlx_new_image(config->mlx_ptr, WIN_W, WIN_H);
	config->frame.addr = mlx_get_data_addr(config->frame.img,
			&config->frame.bpp, &config->frame.line_length,
			&config->frame.endian);
	mlx_put_image_to_window(config->mlx_ptr, config->win_ptr,
		config->frame.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_config	config;

	ft_memset(&config, 0, sizeof(config));
	if (argc != 2)
		return (printf("Error\nformat ./cub3d [map_file]"), 0);
	else
	{
		if (initialisation(&config, argv))
		{
			init_game(&config);
			mlx_hook(config.win_ptr, 17, 0, free_all, &config);
			mlx_hook(config.win_ptr, 2, 1L << 0, key_press, &config);
			mlx_hook(config.win_ptr, 3, 1L << 1, key_release, &config.player);
			mlx_loop_hook(config.mlx_ptr, draw_loop, &config);
			mlx_loop(config.mlx_ptr);
		}
	}
	free_all(&config);
	return (0);
}
