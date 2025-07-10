/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:30:16 by cguinot           #+#    #+#             */
/*   Updated: 2025/07/10 17:37:55 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	if (color->r != -1)
	{
		printf("Error double color assignation \n");
		return (0);
	}
	rgb_int = malloc(sizeof(int) * 3);
	rgb = ft_split(line + 2, ',');
	rgb_int[0] = ft_atoi(ft_strtrim(rgb[0], " \t\n\r"));
	rgb_int[1] = ft_atoi(ft_strtrim(rgb[1], " \t\n\r"));
	rgb_int[2] = ft_atoi(ft_strtrim(rgb[2], " \t\n\r"));
	if (rgb_int[0] < 0 || rgb_int[0] > 255 || rgb_int[1] < 0 || rgb_int[1] > 255
		|| rgb_int[2] < 0 || rgb_int[2] > 255)
	{
		printf("Error color problem \n");
		return (free(rgb), free(rgb_int), 0);
	}
	color->r = rgb_int[0];
	color->g = rgb_int[1];
	color->b = rgb_int[2];
	return (free(rgb), free(rgb_int), 1);
}

int	text_parse(t_config *config, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (valid_text(&config->NO_texture, "NO ", line));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (valid_text(&config->SO_texture, "SO ", line));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (valid_text(&config->WE_texture, "WE ", line));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (valid_text(&config->EA_texture, "EA ", line));
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
