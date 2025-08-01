/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:19:24 by ebansse           #+#    #+#             */
/*   Updated: 2025/08/01 18:07:51 by ebansse          ###   ########.fr       */
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

void	draw_vertical_line(t_config *game, int x, int start, int end, int color)
{
    int y;
    
    for (y = start; y <= end; y++)
        mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, color);
}

void	draw_line(t_config *config, t_display *display)
{
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int 	color;

	lineHeight = (int)(config->win_h / display->perpWallDist);
	drawStart = -lineHeight / 2 + config->win_h / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + config->win_h / 2;
	if (drawEnd >= config->win_h)
		drawEnd = config->win_h - 1;
	
	color = 0xFF0000; // Rouge
	
	// IMPORTANT: Dessiner une ligne VERTICALE, pas horizontale !
	// Bon ordre : du haut vers le bas
	draw_vertical_line(config, display->x, drawStart, drawEnd, color);

}

void	algo_dda(t_config *config, t_player *player, t_display *display)
{
    int	hit = 0;
    int	side = 0;
    int mapX, mapY;

    // Initialiser les coordonnées de la grille à partir de la position du joueur
    mapX = (int)player->posX;
    mapY = (int)player->posY;

    while (!hit)
    {
        if (display->sideDistX < display->sideDistY)
        {
            display->sideDistX += display->deltaDistX;
            mapX += display->stepX;
            side = 0;
        }
        else
        {
            display->sideDistY += display->deltaDistY;
            mapY += display->stepY;
            side = 1;
        }
        
        if (mapY < 0 || mapY >= config->map_height ||
            mapX < 0 || mapX >= config->map_width)
        {
			printf("Out of bounds: mapY: %d, mapX: %d\n", mapY, mapX);
            hit = 1;
        }
        else if (config->map[mapY][mapX] == '1')
        {
            hit = 1;
        }
    }
    
    // Calculer la distance perpendiculaire
    if (side == 0)
        display->perpWallDist = (mapX - player->posX + (1 - display->stepX) / 2.0) / display->rayDirX;
    else
        display->perpWallDist = (mapY - player->posY + (1 - display->stepY) / 2.0) / display->rayDirY;
    
    // S'assurer que la distance est positive
    if (display->perpWallDist < 0)
        display->perpWallDist = -display->perpWallDist;
}

void	step(t_config *config, t_player *player, t_display *display)
{
	if (display->rayDirX < 0)
	{
		display->stepX = -1;
		display->sideDistX = (player->posX - (int)player->posX) * display->deltaDistX;
	}
	else
	{
		display->stepX = 1;
		display->sideDistX = ((int)player->posX + 1.0 - player->posX) * display->deltaDistX;
	}

	if (display->rayDirY < 0)
	{
		display->stepY = -1;
		display->sideDistY = (player->posY - (int)player->posY) * display->deltaDistY;
	}
	else
	{
		display->stepY = 1;
		display->sideDistY = ((int)player->posY + 1.0 - player->posY) * display->deltaDistY;
	}
	algo_dda(config, player, display);
}

void	raycasting(t_config *config, t_player *player, t_display *display)
{
    int x;
    double cameraX;

    for (x = 0; x < config->win_w; x++)
    {
        display->x = x;
        cameraX = 2 * x / (double)config->win_w - 1;

        // Calcul direction du rayon
        display->rayDirX = player->dirX + player->planeX * cameraX;
        display->rayDirY = player->dirY + player->planeY * cameraX;

        // Position de départ dans la map
        int mapX = (int)player->posX;
        int mapY = (int)player->posY;

        // Calcul des distances
        double deltaDistX = (display->rayDirX == 0) ? 1e30 : fabs(1 / display->rayDirX);
        double deltaDistY = (display->rayDirY == 0) ? 1e30 : fabs(1 / display->rayDirY);

        int stepX, stepY;
        double sideDistX, sideDistY;

        if (display->rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (player->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player->posX) * deltaDistX;
        }
        if (display->rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (player->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player->posY) * deltaDistY;
        }

        // DDA
        int hit = 0, side = 0;
        while (!hit)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (mapY < 0 || mapY >= config->map_height || mapX < 0 || mapX >= config->map_width)
                break;
            if (config->map[mapY][mapX] == '1')
                hit = 1;
        }

        // Calcul distance perpendiculaire
        double perpWallDist;
        if (side == 0)
            perpWallDist = (mapX - player->posX + (1 - stepX) / 2.0) / display->rayDirX;
        else
            perpWallDist = (mapY - player->posY + (1 - stepY) / 2.0) / display->rayDirY;

        // Calcul hauteur du mur
        int lineHeight = (int)(config->win_h / perpWallDist);

        // Calcul début et fin de la ligne à dessiner
        int drawStart = -lineHeight / 2 + config->win_h / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + config->win_h / 2;
        if (drawEnd >= config->win_h) drawEnd = config->win_h - 1;

        // Couleur selon le côté du mur
        int color = (side == 0) ? 0xFF0000 : 0x880000;

        // Dessin de la ligne verticale
        draw_vertical_line(config, x, drawStart, drawEnd, color);
    }
}
