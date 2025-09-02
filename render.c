/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:16:38 by ebansse           #+#    #+#             */
/*   Updated: 2025/09/02 13:37:07 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_rgb(int x, int y, t_color *color, t_texture *frame)
{
	int	index;

	if (x >= WIN_W || y >= WIN_H || x < 0 || y < 0)
		return ;
	index = y * frame->line_length + x * (frame->bpp / 8);
	frame->addr[index] = color->b & 0xFF;
	frame->addr[index + 1] = color->g & 0xFF;
	frame->addr[index + 2] = color->r & 0xFF;
}

void	put_pixel(int x, int y, int color, t_texture *frame)
{
	int	index;

	if (x >= WIN_W || y >= WIN_H || x < 0 || y < 0)
		return ;
	index = y * frame->line_length + x * frame->bpp / 8;
	frame->addr[index] = color & 0xFF;
	frame->addr[index + 1] = (color >> 8) & 0xFF;
	frame->addr[index + 2] = (color >> 16) & 0xFF;
}

int	get_texture_pixel(t_texture *tex, int x, int y)
{
	int	offset;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	offset = y * tex->line_length + x * (tex->bpp / 8);
	return (*(int *)(tex->addr + offset));
}

void	draw_floor_ceiling(t_config *game)
{
	int		x;
	int		y;
	t_color	*color;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y < WIN_H / 2)
			{
				color = &game->ceiling_color;
				put_pixel_rgb(x, y, color, &game->frame);
			}
			else
			{
				color = &game->floor_color;
				put_pixel_rgb(x, y, color, &game->frame);
			}
			x++;
		}
		y++;
	}
}

void	clear_img(t_config *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(x, y, 0, &game->frame);
			x++;
		}
		y++;
	}
}
