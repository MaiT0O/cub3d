/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:19:24 by ebansse           #+#    #+#             */
/*   Updated: 2025/08/06 18:38:49 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

        ray->deltaDistX = fabs(1 / ray->dirX);
        ray->deltaDistY = fabs(1 / ray->dirY);

        if (ray->dirX < 0)
        {
            ray->stepX = -1;
            ray->sideDistX = (player->posX - player->mapX) * ray->deltaDistX;
        }
        else
        {
            ray->stepX = 1;
            ray->sideDistX = (player->mapX + 1.0 - player->posX) * ray->deltaDistX;
        }
        if (ray->dirY < 0)
        {
            ray->stepY = -1;
            ray->sideDistY = (player->posY - player->mapY) * ray->deltaDistY;
        }
        else
        {
            ray->stepY = 1;
            ray->sideDistY = (player->mapY + 1.0 - player->posY) * ray->deltaDistY;
        }

        while (true)
        {
            if (ray->sideDistX < ray->sideDistY)
            {
                ray->sideDistX += ray->deltaDistX;
                player->mapX += ray->stepX;
                side = 0;
            }
            else
            {
                ray->sideDistY += ray->deltaDistY;
                player->mapY += ray->stepY;
                side = 1;
            }
            if (config->map[player->mapY][player->mapX] == '1')
                break;
        }

        if (side == 0)
            ray->perpWallDist = (player->mapX - player->posX + (1 - ray->stepX) / 2.0) / ray->dirX;
        else
            ray->perpWallDist = (player->mapY - player->posY + (1 - ray->stepY) / 2.0) / ray->dirY;

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

    }
}

