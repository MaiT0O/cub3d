/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:01:15 by cguinot           #+#    #+#             */
/*   Updated: 2025/07/23 18:55:24 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft/libft.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_player
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
}   t_player;

typedef struct s_display
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	double	sideDistX;
	double	sideDistY;
	double	perpWallDist;
	int		x;
}	t_display;

typedef struct s_texture
{
    void    *img;
    int     *data;      // tableau de pixels (int ARGB)
    int		bits_per_pixels;
	int		size_line;
	int		endian;
	int     width;
    int     height;
}   t_texture;

typedef struct s_config
{
	void    *mlx_ptr;
    void    *win_ptr;
	int		win_w;
	int 	win_h;
	t_color	floor_color;
	t_color	ceiling_color;
	t_player	player;
	t_display	display;
	t_texture	textures[4];
	char	**map;
	char	boussole;
	int		pY;
	int		pX;
	int		map_height;
	int		map_width;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
}			t_config;

int			check_extension(char *filename);
int			valid_text(char **texture, char *identifier, char *line);
int			valid_text_2(void);
int			text_parse(t_config *config, char *line);
int			parsing(char *filename, t_config *config);

int			add_map_line(t_config *config, char *line);
int			is_map_line(char *line);

int			flood_fill(t_config *map, char **visited, int x, int y);
char		**init_visited_array(t_config *map);

void		init_config(t_config *config);
int			free_all(t_config *config);
// pour afficher les stats de la map
void		display_config(t_config *config);
void		display_map(t_config *config);

void		init_player(t_config *config);
void    	init_textures(t_config *config);

void		free_textures(t_config *config);

int			key_press(int keycode, t_config *config);
void		raycasting(t_config *config, t_player *player, t_display *display);

#endif