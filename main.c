/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:30:11 by cguinot           #+#    #+#             */
/*   Updated: 2025/08/21 13:53:16 by ebansse          ###   ########.fr       */
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
	init_config(config);
	if (!parsing(argv[1], config))
	{
		free_all(config);
		return (printf("Error in map descriptor\n"), 0);
	}
	if (!map_closed(config))
	{
		free_all(config);
		return (printf("Error in player or wall\n"), 0);
	}
	/*init_textures(config);*/
	init_player(&config->player);
	printf("angle : %f\n", config->player.angle);
	printf("boussole : %c\n", config->player.boussole);
	return (1);
}

int init_game(t_config *config)
{
	config->mlx_ptr = mlx_init();
	config->win_ptr = mlx_new_window(config->mlx_ptr, WIN_W, WIN_H, "cub3d");
	config->frame.img = mlx_new_image(config->mlx_ptr, WIN_W, WIN_H);
	config->frame.addr = mlx_get_data_addr(config->frame.img, &config->frame.bpp
		, &config->frame.line_length, &config->frame.endian);
	mlx_put_image_to_window(config->mlx_ptr, config->win_ptr
		, config->frame.img, 0, 0);
	return (0);
}


float distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float fixed_dist(float delta_x,float delta_y, t_config *game)
{
	float angle = atan2(delta_y, delta_x) - game->player.angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);
	return fix_dist;
}

void	draw_floor_ceiling(t_config *game)
{
	int x;
	int y;
	t_color *color;
	
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y < WIN_H / 2)
			{
				color = &game->ceiling_color;
				put_pixel_rgb(x, y, color, &game->frame);
			}
			else
			{
				color = &game->floor_color;
				put_pixel_rgb(x, y, color, &game->frame);
			}
			x++;
		}
		y++;
	}
}

bool	touch(float px, float py, t_config *game)
{
	int	x = px / BLOCK;
	int	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

void	draw_wall(t_config *game, float ray_x, float ray_y, int i)
{
	float dist;
	float height;
	int	start_y;
	int	end;

	dist = fixed_dist(ray_x - game->player.x, ray_y - game->player.y, game);
	height = (BLOCK / dist) * (WIN_W / 2);
	start_y = (WIN_H - height) / 2;
	end = start_y + height;
	while(start_y < end)
	{
		put_pixel(i, start_y, 0x0000FF, &game->frame);
		start_y++;
	}
}

void draw_line(t_player *player, t_config *game, float start_x, int i)
{
	float cos_angle;
	float sin_angle;
	float ray_x;
	float ray_y;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
	ray_y = player->y;
	while(!touch(ray_x, ray_y, game))
	{
		/*put_pixel(ray_x, ray_y, 0xFF0000, &game->frame);*/
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	draw_wall(game, ray_x, ray_y, i);
}

int	draw_loop(t_config *game)
{
	float fraction;
	float start_x;
	int	i;

	move_player(&game->player);
	clear_img(game);
	draw_floor_ceiling(game);
	/*draw_square(game->player.x, game->player.y, 10, 0x00FF00, game);
	draw_map(game);*/
	fraction = PI / 3 / WIN_W;
	start_x = game->player.angle - PI / 6;
	i = 0;
	while (i < WIN_W)
	{
		draw_line(&game->player, game, start_x, i);
		start_x += fraction;
		i++;		
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->frame.img, 0, 0);
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
