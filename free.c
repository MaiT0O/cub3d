/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:53:21 by cguinot           #+#    #+#             */
/*   Updated: 2025/07/10 18:59:38 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(t_config *config)
{
	int	i;

	i = 0;
	if (config->no_texture)
		free(config->no_texture);
	if (config->so_texture)
		free(config->so_texture);
	if (config->we_texture)
		free(config->we_texture);
	if (config->ea_texture)
		free(config->ea_texture);
	while (i < config->map_height && config->map[i])
	{
		free(config->map[i]);
		i++;
	}
	free(config->map);
}

void	free_and_init_config(t_config *config, int n)
{
	if (n == 1)
		free_all(config);
	config->no_texture = NULL;
	config->so_texture = NULL;
	config->we_texture = NULL;
	config->ea_texture = NULL;
	config->map = NULL;
	config->map_height = 0;
	config->map_width = 0;
	config->floor_color.r = -1;
	config->floor_color.g = -1;
	config->floor_color.b = -1;
	config->ceiling_color.r = -1;
	config->ceiling_color.g = -1;
	config->ceiling_color.b = -1;
}
