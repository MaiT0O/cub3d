/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:30:11 by cguinot           #+#    #+#             */
/*   Updated: 2025/08/01 17:59:37 by ebansse          ###   ########.fr       */
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
				config->pX = j;
				config->pY = i;
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
	init_player(config);
	return (1);
}

// Fonction de rendu appelée à chaque frame
int render_frame(t_config *config)
{
    // Effacer l'écran
    mlx_clear_window(config->mlx_ptr, config->win_ptr);
    
    // Effectuer le raycasting
    raycasting(config, &config->player, &config->display);
    
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
			config.win_ptr = mlx_new_window(config.mlx_ptr, config.win_w, config.win_h, "cub3d");
			
			// CORRECTION : Appeler raycasting dans la boucle de rendu
			render_frame(&config);
			mlx_key_hook(config.win_ptr, key_press, &config);
			mlx_hook(config.win_ptr, 17, 0, free_all, &config);
			mlx_loop(config.mlx_ptr);
		}
	}
	display_map(&config);
	free_all(&config);
	return (0);
}
