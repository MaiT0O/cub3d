/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:01:15 by cguinot           #+#    #+#             */
/*   Updated: 2025/08/07 19:36:12 by ebansse          ###   ########.fr       */
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

typedef enum e_cardinal_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}	t_cardinal_direction;

typedef struct s_player
{
    double posX;
    double posY;
	int		mapX;
	int		mapY;
	float	x;
	float	y;
	float	angle;

    double dirX;
    double dirY;
    double planeX;
    double planeY;

	char	boussole;

	bool	key_up;
	bool	key_down;
	bool	key_right;
	bool	key_left;
	bool	left_rotate;
	bool	right_rotate;
}   t_player;

typedef struct s_ray
{
    double dirX;      // direction du rayon
    double dirY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX;
    int stepY;
    int mapX;
    int mapY;
	double wallX;
}	t_ray;

typedef struct s_texture
{
    void    *img;
    int     *data;
	char	*addr;
    int		bpp;
	int		line_length;
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
	t_ray		ray;
	t_texture	textures[4];
	t_texture	frame;
	char	**map;
	int		map_height;
	int		map_width;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
}			t_config;
/*parsing*/
int			check_extension(char *filename);
int			valid_text(char **texture, char *identifier, char *line);
int			valid_text_2(void);
int			text_parse(t_config *config, char *line);
int			parsing(char *filename, t_config *config);

int			add_map_line(t_config *config, char *line);
int			is_map_line(char *line);

int			flood_fill(t_config *map, char **visited, int x, int y);
char		**init_visited_array(t_config *map);
/*init*/
void		init_config(t_config *config);
void		init_player(t_player *player);
void    	init_textures(t_config *config);
// pour afficher les stats de la map
void		display_config(t_config *config);
void		display_map(t_config *config);

/*free*/
void		free_textures(t_config *config);
int			free_all(t_config *config);

/*raycasting*/
void		raycasting(t_config *config, t_player *player, t_ray *ray);
/*draw*/
void    	put_pixel(int x, int y, int color, t_texture *frame);
void    	draw_square(int x, int y, int size, int color, t_config *game);
void 		clear_img(t_config *game);
void    	draw_map(t_config *game);
/*hook*/
int 		key_press(int keycode, t_config *config);
int 		key_release(int keycode, t_player *player);
void    	move_player(t_player *player);

# define WIN_H 720
# define WIN_W 1280
# define WALL_COLOR 0xFF2222
# define FLOOR_COLOR 0x222222
# define CEILING_COLOR 0xCCCCCC
# define W 119
# define A 97
# define S 115
# define D 100
# define PI 3.14159265359
# define BLOCK 64
# define RIGHT 65363
# define LEFT 65361

#endif