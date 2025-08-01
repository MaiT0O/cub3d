/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:19:24 by ebansse           #+#    #+#             */
/*   Updated: 2025/07/23 18:58:26 by ebansse          ###   ########.fr       */
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

void draw_vertical_line(t_config *game, int start, int end, int color)
{
    for (int y = start; y <= end; y++)
        mlx_pixel_put(game->mlx_ptr, game->win_ptr, game->display.x, y, color);
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
	
	color = 0xFF0000;
	draw_vertical_line(config, drawStart, drawEnd, color);
}

void	algo_dda(t_config *config, t_player *player, t_display *display)
{
	int	hit;
	int	side;

	hit = 0;
	while(!hit)
	{
		if (display->sideDistX < display->sideDistX)
		{
			display->sideDistX += display->deltaDistX;
			config->pX += display->stepX;
			side = 0;
		}
		else
		{
			display->sideDistY += display->deltaDistY;
			config->pY += display->stepY;
			side = 1;
		}
		if (config->map[config->pY][config->pX] == '1')
			hit = 1;
	}
	if (side == 0)
		display->perpWallDist = (config->pX - player->posX + (1 - display->stepX) / 2.0) / display->rayDirX;
	else
		display->perpWallDist = (config->pY - player->posY + (1 - display->stepX) / 2.0) / display->rayDirX;
	draw_line(config, display);
}

void	step(t_config *config, t_player *player, t_display *display)
{
	if (display->rayDirX < 0)
	{
		display->stepX = -1;
		display->sideDistX = (player->posX - config->pX) * display->deltaDistX;
	}
	else
	{
		display->stepX = 1;
		display->sideDistX = (config->pX + 1.0 - player->posX) * display->deltaDistX;
	}

	if (display->rayDirY < 0)
	{
		display->stepY = -1;
		display->sideDistY = (player->posY - config->pY) * display->deltaDistY;
	}
	else
	{
		display->stepY = 1;
		display->sideDistY = (config->pY + 1.0 - player->posY) * display->deltaDistY;
	}
	algo_dda(config, player, display);
}

void	raycasting(t_config *config, t_player *player, t_display *display)
{
	double	cameraX;

	display->x = -1;
	while (++display->x < config->win_w)
	{
		cameraX = 2 * display->x / (double)config->win_w - 1;

		display->rayDirX = player->dirX + player->planeX * cameraX;
		display->rayDirY = player->dirX + player->planeX * cameraX;

		if (display->rayDirX == 0)
			display->deltaDistX = 1e30;
		else
			display->deltaDistX = fabs(1 / display->rayDirX);
		
		if (display->rayDirY == 0)
			display->deltaDistY = 1e30;
		else
			display->deltaDistY = fabs(1 / display->rayDirY);
	}
	step(config, player, display);
}
