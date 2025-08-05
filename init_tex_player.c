/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:28:54 by ebansse           #+#    #+#             */
/*   Updated: 2025/08/05 17:00:04 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    load_textures(t_config *config, t_texture *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(config->mlx_ptr, path, &tex->width, &tex->height);
    if (!tex->img)
    {
        printf("Error: failed to load texture: %s\n", path);
        exit(EXIT_FAILURE);
    }
    tex->data = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_length, &tex->endian);
}

void    init_textures(t_config *config)
{
    load_textures(config, &config->textures[0], config->no_texture);
    load_textures(config, &config->textures[1], config->so_texture);
    load_textures(config, &config->textures[2], config->we_texture);
    load_textures(config, &config->textures[3], config->ea_texture);
}

void	check_boussole(t_config *config)
{
	if (config->boussole == 'E')
	{
		config->player.dirX = 1;
		config->player.dirY = 0;
		config->player.planeX = 0;
		config->player.planeY = 0.66;
	}
	else if (config->boussole == 'W')
	{
		config->player.dirX = -1;
		config->player.dirY = 0;
		config->player.planeX = 0;
		config->player.planeY = -0.66;
	}
}

void	init_player(t_config *config)
{
	config->player.posX = config->mapX + 0.5;
	config->player.posY = config->mapY + 0.5;
	if (config->boussole == 'N')
	{
		config->player.dirX = 0;
		config->player.dirY = -1;
		config->player.planeX = 0.66;
		config->player.planeY = 0;
	}
	else if (config->boussole == 'S')
	{
		config->player.dirX = 0;
		config->player.dirY = 1;
		config->player.planeX = -0.66;
		config->player.planeY = 0;
	}
	else
		check_boussole(config);
}

void	init_config(t_config *config)
{
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
	config->mlx_ptr = mlx_init();
	config->frame.img = mlx_new_image(config->mlx_ptr, WIN_W, WIN_H);
	config->frame.data = (int *)mlx_get_data_addr(config->frame.img,
									   &config->frame.bpp,
									   &config->frame.line_length,
									   &config->frame.endian);
}
