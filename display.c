/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:53:17 by cguinot           #+#    #+#             */
/*   Updated: 2025/07/10 18:59:38 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_config(t_config *config)
{
	printf("NO: %s\n", config->no_texture ? config->no_texture : "NULL");
	printf("SO: %s\n", config->so_texture ? config->so_texture : "NULL");
	printf("WE: %s\n", config->we_texture ? config->we_texture : "NULL");
	printf("EA: %s\n", config->ea_texture ? config->ea_texture : "NULL");
	printf("Player pos: x = %d, y = %d\n", config->player_x, config->player_y);
	printf("Floor: R=%d G=%d B=%d\n", config->floor_color.r,
		config->floor_color.g, config->floor_color.b);
	printf("Ceiling: R=%d G=%d B=%d\n", config->ceiling_color.r,
		config->ceiling_color.g, config->ceiling_color.b);
}

void	display_map(t_config *config)
{
	int	i;

	if (!config->map)
	{
		ft_putendl_fd("Map: NULL", 1);
		return ;
	}
	ft_putstr_fd("Map height: ", 1);
	ft_putnbr_fd(config->map_height, 1);
	ft_putstr_fd(",  en comptant les espaces vide a la fin width: ", 1);
	ft_putnbr_fd(config->map_width, 1);
	ft_putendl_fd("", 1);
	ft_putendl_fd("Map:", 1);
	i = 0;
	while (i < config->map_height && config->map[i])
	{
		ft_putendl_fd(config->map[i], 1);
		i++;
	}
	ft_putendl_fd("--- End of map ---", 1);
}
