/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:19:24 by ebansse           #+#    #+#             */
/*   Updated: 2025/08/05 16:59:35 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_config *config)
{
	printf("%d\n", keycode);
	if (keycode == 65307)
		free_all(config);
	return (1);
}

void	my_mlx_pixel_put(t_texture *texture, int x, int y, int color)
{
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return;

	int pixels_per_line = texture->line_length / (texture->bpp / 8);
	texture->data[y * pixels_per_line + x] = color;
}

t_cardinal_direction	get_cardinal_direction(int side, t_ray *ray)
{
	if (side == 0) // Mur vertical (est/ouest)
	{
		if (ray->dirX > 0)
			return EAST;
		else
			return WEST;
	}
	else // Mur horizontal (nord/sud)
	{
		if (ray->dirY > 0)
			return SOUTH;
		else
			return NORTH;
	}
}


void	draw_texture_column(t_config *config, int x, int draw_start, int draw_end,
							int line_height, int side)
{
	t_ray	*ray = &config->ray;
	t_cardinal_direction dir;
	t_texture *tex;
	int		tex_x, tex_y;
	double	step;
	double	tex_pos;
	int		y;
	int		color;

	// 1. Déterminer la direction du mur touché
	dir = get_cardinal_direction(side, ray);
	tex = &config->textures[dir];

	// 2. Calcul de la coordonnée X dans la texture
	tex_x = (int)(ray->wallX * (double)TEXTURE_SIZE);
	if ((side == 0 && ray->dirX < 0) || (side == 1 && ray->dirY > 0))
		tex_x = TEXTURE_SIZE - tex_x - 1;

	// 3. Hauteur du pas dans la texture (compression/étirement)
	step = 1.0 * TEXTURE_SIZE / line_height;

	// 4. Position de départ dans la texture
	tex_pos = (draw_start - config->win_h / 2 + line_height / 2) * step;

	// 5. Boucle pour chaque pixel vertical
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (TEXTURE_SIZE - 1);
		tex_pos += step;

		color = tex->data[TEXTURE_SIZE * tex_y + tex_x];

		// Optionnel : ombrage sur les murs Nord/Sud
		if (dir == NORTH || dir == SOUTH)
			color = (color >> 1) & 0x7F7F7F;

		// Écrire le pixel dans ton image finale (à adapter à ta lib)
		my_mlx_pixel_put(&config->frame, x, y, color); // remplace par ton système d'affichage
		y++;
	}
}


void	raycasting(t_config *config, t_player *player, t_ray *ray)
{
    int x;
    int side;
    double cameraX;

    x = -1;
    while (++x < WIN_W)
    {
        cameraX = 2 * x / (double)WIN_W - 1;

        // Calcul direction du rayon
        ray->dirX = player->dirX + player->planeX * cameraX;
        ray->dirY = player->dirY + player->planeY * cameraX;

        // Calcul des distances
        ray->mapX = (int)player->posX;
        ray->mapY = (int)player->posY;

        ray->deltaDistX = fabs(1 / ray->dirX);
        ray->deltaDistY = fabs(1 / ray->dirY);

        if (ray->dirX < 0)
        {
            ray->stepX = -1;
            ray->sideDistX = (player->posX - ray->mapX) * ray->deltaDistX;
        }
        else
        {
            ray->stepX = 1;
            ray->sideDistX = (ray->mapX + 1.0 - player->posX) * ray->deltaDistX;
        }
        if (ray->dirY < 0)
        {
            ray->stepY = -1;
            ray->sideDistY = (player->posY - ray->mapY) * ray->deltaDistY;
        }
        else
        {
            ray->stepY = 1;
            ray->sideDistY = (ray->mapY + 1.0 - player->posY) * ray->deltaDistY;
        }

        while (true)
        {
            if (ray->sideDistX < ray->sideDistY)
            {
                ray->sideDistX += ray->deltaDistX;
                ray->mapX += ray->stepX;
                side = 0;
            }
            else
            {
                ray->sideDistY += ray->deltaDistY;
                ray->mapY += ray->stepY;
                side = 1;
            }
            if (config->map[ray->mapY][ray->mapX] == '1')
                break;
        }

        if (side == 0)
            ray->perpWallDist = (ray->mapX - player->posX + (1 - ray->stepX) / 2.0) / ray->dirX;
        else
            ray->perpWallDist = (ray->mapY - player->posY + (1 - ray->stepY) / 2.0) / ray->dirY;

        // Calcul hauteur du mur
        int lineHeight = (int)(WIN_H / ray->perpWallDist);

        // Calcul début et fin de la ligne à dessiner
        int drawStart = -lineHeight / 2 + WIN_H / 2;
        if (drawStart < 0) 
            drawStart = 0;

        int drawEnd = lineHeight / 2 + WIN_H / 2;
        if (drawEnd >= WIN_H) 
            drawEnd = WIN_H - 1;

        if (side == 0)
            ray->wallX = player->posY + ray->perpWallDist * ray->dirY;
        else
            ray->wallX = player->posX + ray->perpWallDist * ray->dirX;
        ray->wallX -= floor(ray->wallX);

        draw_texture_column(config, x, drawStart, drawEnd, lineHeight, side);
    }
}

