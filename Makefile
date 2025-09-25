# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 14:30:24 by ebansse           #+#    #+#              #
#    Updated: 2025/09/25 17:16:45 by ebansse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

INCLUDES = -I/usr/include -Imlx -Ilibft

MLX_LD_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm -lz -Llibft -l:libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = main.c free.c  
PLAYER_SRCS = player/move.c player/init_tex_player.c
PARSER_SRCS = parser/parsing.c parser/parsing_map.c parser/parse_utils.c parser/parse_tools.c
RAYCAST_SRCS = raycasting/raycast.c raycasting/utils_ray.c raycasting/render.c

OBJS = $(SRCS:.c=.o) $(PARSER_SRCS:.c=.o) $(RAYCAST_SRCS:.c=.o) $(PLAYER_SRCS:.c=.o)

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

all: $(NAME)

$(NAME): make_libs $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(MLX_LD_FLAGS) -o $(NAME)
	@echo "${CYAN}$(NAME) compiled successfully!${RESET}"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

make_libs:
	@make -C mlx
	@make -C libft

clean:
	@rm -f $(OBJS)
	@make -C libft clean
	@make -C mlx clean
	@echo "${MAGENTA}${NAME} object files cleaned!${RESET}"

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@echo "${RED}${NAME} binaries cleaned!${RESET}"

re: fclean all