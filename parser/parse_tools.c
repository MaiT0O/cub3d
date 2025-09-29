/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:08:40 by ebansse           #+#    #+#             */
/*   Updated: 2025/09/29 15:30:56 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_atoi_neuille(const char *str)
{
	int	nbr;
	int	i;

	i = 0;
	nbr = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (!str[i])
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '\0')
		return (nbr);
	else
		return (-1);
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
