/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:58:15 by ebansse           #+#    #+#             */
/*   Updated: 2025/09/03 13:11:44 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_config *config)
{
	t_player	*player;

	player = &config->player;
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	if (keycode == 65307)
		free_all(config);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

void	move_left_right(t_player *player, t_config *game, float cos, float sin)
{
	if (player->key_left && !touch(player->tmp_x + sin * game->speed
			, player->tmp_y - cos * game->speed, game))
	{
		player->x += sin * game->speed;
		player->y -= cos * game->speed;
	}
	if (player->key_right && !touch(player->tmp_x - sin * game->speed
			, player->tmp_y + cos * game->speed, game))
	{
		player->x -= sin * game->speed;
		player->y += cos * game->speed;
	}
}

void	move_step(t_player *player, t_config *game, float cos, float sin)
{
	player->tmp_x = player->x;
	player->tmp_y = player->y;
	if (player->key_up && !touch(player->tmp_x + cos * game->speed
			, player->tmp_y + sin * game->speed, game))
	{
		player->x += cos * game->speed;
		player->y += sin * game->speed;
	}
	if (player->key_down && !touch(player->tmp_x - cos * game->speed
			, player->tmp_y - sin * game->speed, game))
	{
		player->x -= cos * game->speed;
		player->y -= sin * game->speed;
	}
	move_left_right(player, game, cos, sin);
}

void	move_player(t_player *player, t_config *game)
{
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	angle_speed = 0.1;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	move_step(player, game, cos_angle, sin_angle);
}
