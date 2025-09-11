/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:53:21 by cguinot           #+#    #+#             */
/*   Updated: 2025/09/11 13:59:28 by ebansse          ###   ########.fr       */
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

void	free_img(t_config *config)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (config->textures[i].img && config->mlx_ptr)
		{
			mlx_destroy_image(config->mlx_ptr, config->textures[i].img);
			config->textures[i].img = NULL;
		}
		i++;
	}
	if (config->frame.img && config->mlx_ptr)
		mlx_destroy_image(config->mlx_ptr, config->frame.img);
}

void	free_path_map(t_config *config)
{
	int	i;

	if (config->no_texture)
		free(config->no_texture);
	if (config->so_texture)
		free(config->so_texture);
	if (config->we_texture)
		free(config->we_texture);
	if (config->ea_texture)
		free(config->ea_texture);
	if (config->map)
	{
		i = 0;
		while (i < config->map_height && config->map[i])
		{
			free(config->map[i]);
			config->map[i] = NULL;
			i++;
		}
		free(config->map);
		config->map = NULL;
	}
}

int	free_all(t_config *config)
{
	free_img(config);
	free_path_map(config);
	if (config->win_ptr && config->mlx_ptr)
	{
		mlx_destroy_window(config->mlx_ptr, config->win_ptr);
		config->win_ptr = NULL;
	}
	if (config->mlx_ptr)
	{
		mlx_destroy_display(config->mlx_ptr);
		free(config->mlx_ptr);
		config->mlx_ptr = NULL;
	}
	exit(0);
	return (1);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
