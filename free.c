/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:53:21 by cguinot           #+#    #+#             */
/*   Updated: 2025/07/17 15:01:18 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_config *config)
{
	int	i;

	i = 0;
	while (i < 4) // 4 correspond au nombre de textures (NO, SO, WE, EA)
	{
		if (config->textures[i].img)
		{
			mlx_destroy_image(config->mlx_ptr, config->textures[i].img);
			config->textures[i].img = NULL;
		}
		i++;
	}
}

int	free_all(t_config *config)
{
    int	i;

    // Libération des textures
    /*free_textures(config);*/

    // Libération des chemins de textures
    if (config->no_texture)
        free(config->no_texture);
    if (config->so_texture)
        free(config->so_texture);
    if (config->we_texture)
        free(config->we_texture);
    if (config->ea_texture)
        free(config->ea_texture);

    // Libération de la carte
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

    // Destruction de la fenêtre et du display
    if (config->win_ptr)
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
