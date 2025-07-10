/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:01:15 by cguinot           #+#    #+#             */
/*   Updated: 2025/07/10 18:59:38 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_config
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	t_color	floor_color;
	t_color	ceiling_color;
	char	**map;
	int		player_y;
	int		player_x;
	int		map_height;
	int		map_width;
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

void		free_and_init_config(t_config *config, int n);
void		free_all(t_config *config);
// pour afficher les stats de la map
void		display_config(t_config *config);
void		display_map(t_config *config);
#endif