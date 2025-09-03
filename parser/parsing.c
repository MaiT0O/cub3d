/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:30:16 by cguinot           #+#    #+#             */
/*   Updated: 2025/09/03 14:13:45 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
	{
		printf("Error wrong extension \n");
		return (0);
	}
	return (1);
}

int	valid_text(char **texture, char *identifier, char *line)
{
	char	*path;
	char	*trimmed_path;
	int		fd;

	path = line + ft_strlen(identifier);
	trimmed_path = ft_strtrim(path, " \t\n\r");
	fd = open(trimmed_path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error cannot open texture \n");
		free(trimmed_path);
		return (0);
	}
	close(fd);
	if (*texture != NULL)
	{
		printf("Error double path assignation \n");
		free(trimmed_path);
		return (0);
	}
	*texture = ft_strdup(trimmed_path);
	free(trimmed_path);
	return (1);
}

int	valid_color(t_color *color, char *line)
{
	char	**rgb;
	int		*rgb_int;
	char	*temp[3];

	if (color->r != -1)
		return (printf("Error double color assignation \n"), 0);
	rgb_int = malloc(sizeof(int) * 3);
	rgb = ft_split(line + 2, ',');
	temp[0] = ft_strtrim(rgb[0], " \t\n\r");
	temp[1] = ft_strtrim(rgb[1], " \t\n\r");
	temp[2] = ft_strtrim(rgb[2], " \t\n\r");
	rgb_int[0] = ft_atoi(temp[0]);
	rgb_int[1] = ft_atoi(temp[1]);
	rgb_int[2] = ft_atoi(temp[2]);
	if (rgb_int[0] < 0 || rgb_int[0] > 255 || rgb_int[1] < 0 || rgb_int[1] > 255
		|| rgb_int[2] < 0 || rgb_int[2] > 255)
		return (free(temp[0]), free(temp[1]), free(temp[2]),
			free(rgb[0]), free(rgb[1]), free(rgb[2]), free(rgb), free(rgb_int),
			printf("Error color problem \n"), 0);
	color->r = rgb_int[0];
	color->g = rgb_int[1];
	color->b = rgb_int[2];
	return (free(temp[0]), free(temp[1]), free(temp[2]),
		free(rgb[0]), free(rgb[1]), free(rgb[2]), free(rgb), free(rgb_int), 1);
}

int	text_parse(t_config *config, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (valid_text(&config->no_texture, "NO ", line));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (valid_text(&config->so_texture, "SO ", line));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (valid_text(&config->we_texture, "WE ", line));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (valid_text(&config->ea_texture, "EA ", line));
	if (ft_strncmp(line, "F ", 2) == 0)
		return (valid_color(&config->floor_color, line));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (valid_color(&config->ceiling_color, line));
	if (is_map_line(line))
	{
		add_map_line(config, line);
		return (0);
	}
	return (0);
}
