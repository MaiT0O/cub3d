/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:30:16 by cguinot           #+#    #+#             */
/*   Updated: 2025/09/25 17:21:22 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	print_array(char **array)
// {
// 	int i = 0;
// 	int j;
// 	while (array[i])
// 	{
// 		j = 0;
// 		while (array[i][j])
// 		{
// 			printf("%c", array[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

int parse_rgb_values(char *line, int **rgb_i)
{
	char	**rgb;
	char	*t[3];

	rgb = ft_split(line + 2, ',');
	if (!rgb[2])
		return (free_tab(rgb), 2);
	t[0] = ft_strtrim(rgb[0], " \t\n\r");
	t[1] = ft_strtrim(rgb[1], " \t\n\r");
	t[2] = ft_strtrim(rgb[2], " \t\n\r");
	if (!is_only_digit(t[0]) || !is_only_digit(t[1]) || !is_only_digit(t[2]))
		return (free_tab(rgb), 2);
	(*rgb_i)[0] = ft_atoi(t[0]);
	(*rgb_i)[1] = ft_atoi(t[1]);
	(*rgb_i)[2] = ft_atoi(t[2]);
	if ((*rgb_i)[0] < 0 || (*rgb_i)[0] > 255 || (*rgb_i)[1] < 0 || (*rgb_i)[1] > 255
		|| (*rgb_i)[2] < 0 || (*rgb_i)[2] > 255)
		return (free_tab(rgb), 2);
	return (free_tab(rgb), 1);
}

int valid_color(t_color *color, char *line)
{
	int	*rgb_i;

	if (!is_line_color(line))
		return (2);
	if (color->r != -1)
		return (printf("Error\ndouble color assignation \n"), 2);
	rgb_i = malloc(sizeof(int) * 3);
	if (parse_rgb_values(line, &rgb_i) != 1)
		return (free(rgb_i), printf("Error\ncolor problem"), 2);
	color->r = rgb_i[0];
	color->g = rgb_i[1];
	color->b = rgb_i[2];
	free(rgb_i);
	return (1);
}

int handle_texture_or_color(t_config *config, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (valid_text(&config->no_texture, "NO ", line));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return valid_text(&config->so_texture, "SO ", line);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return valid_text(&config->we_texture, "WE ", line);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return valid_text(&config->ea_texture, "EA ", line);
	if (ft_strncmp(line, "F ", 2) == 0)
		return valid_color(&config->floor_color, line);
	if (ft_strncmp(line, "C ", 2) == 0)
		return valid_color(&config->ceiling_color, line);
	return 0;
}

int	text_parse(t_config *config, char *line, int textcount)
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
		if (textcount == 6)
		{
			if (config->map_started == 0 || config->map_started == 1)
				return (config->map_started = 1, add_map_line(config, line), 0);
		}
		else
			return (printf("Error\nmap before argument or not enough arg"), 2);
	}
	else if (!is_only_whitespace(line))
		return (2);
	if (config->map_started == 1)
		config->map_started = 2;
	return (0);
}
