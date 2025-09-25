/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:08:40 by ebansse           #+#    #+#             */
/*   Updated: 2025/09/25 17:09:45 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		printf("Error\ncannot open texture");
		free(trimmed_path);
		return (2);
	}
	close(fd);
	if (*texture != NULL)
	{
		printf("Error\ndouble path assignation");
		free(trimmed_path);
		return (2);
	}
	*texture = ft_strdup(trimmed_path);
	free(trimmed_path);
	return (1);
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

int	handle_player_tile(t_config *config, int i, int j)
{
	if (config->player.map_x != -1 && config->player.map_y != -1)
		return (printf("Error\nToo much player detected\n"), 0);
	else
	{
		config->player.map_x = j;
		config->player.map_y = i;
		config->player.boussole = config->map[i][j];
	}
	return (1);
}
