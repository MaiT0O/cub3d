/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:28:54 by ebansse           #+#    #+#             */
/*   Updated: 2025/09/09 13:03:57 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_textures(t_config *config, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(config->mlx_ptr, path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		printf("Error: failed to load texture: %s\n", path);
		exit(EXIT_FAILURE);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_length, &tex->endian);
}

void	init_textures(t_config *config)
{
	load_textures(config, &config->textures[0], config->no_texture);
	load_textures(config, &config->textures[1], config->so_texture);
	load_textures(config, &config->textures[2], config->we_texture);
	load_textures(config, &config->textures[3], config->ea_texture);
}

void	check_boussole(t_player *player)
{
	if (player->boussole == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->angle = atan2(player->dir_y, player->dir_x);
	}
	else if (player->boussole == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->angle = atan2(player->dir_y, player->dir_x);
	}
}

void	init_player(t_player *player)
{
	player->x = BLOCK * player->map_x;
	player->y = BLOCK * player->map_y;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
	if (player->boussole == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->angle = atan2(player->dir_y, player->dir_x) * -3;
	}
	else if (player->boussole == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->angle = atan2(player->dir_y, player->dir_x);
	}
	else
		check_boussole(player);
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
	config->speed = 7;
}
