/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:16:38 by ebansse           #+#    #+#             */
/*   Updated: 2025/08/06 19:20:23 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    put_pixel(int x, int y, int color, t_texture *frame)
{
    int index;

    if (x >= WIN_W || y >= WIN_H || x < 0 || y < 0)
        return ;

    index = y * frame->line_length + x * frame->bpp / 8;
    frame->addr[index] = color & 0xFF;
    frame->addr[index + 1] = (color >> 8) & 0xFF;
    frame->addr[index + 2] = (color >> 16) & 0xFF;
}

void    draw_map(t_config *game)
{
    char    **map;
    int y;
	int	x;

    map = game->map;
	y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '1')
                draw_square(x * 64, y * 64, 64, 0x0000FF, game);
            x++;
        }
        y++;
    }
}

void draw_square(int x, int y, int size, int color, t_config *game)
{
    int i;

    i = -1;
    while (++i < size)
        put_pixel(x + i, y, color, &game->frame);
    i = -1;
    while (++i < size)
        put_pixel(x, y + i, color, &game->frame);
    i = -1;
    while (++i < size)
        put_pixel(x + size, y + i, color, &game->frame);
    i = -1;
    while (++i < size)
        put_pixel(x + i, y + size, color, &game->frame);
}

void clear_img(t_config *game)
{
    int y;
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
