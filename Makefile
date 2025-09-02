# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 14:30:24 by ebansse           #+#    #+#              #
#    Updated: 2025/09/02 13:28:57 by ebansse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

INCLUDES = -I/usr/include -Imlx -Ilibft

MLX_LD_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm -lz -Llibft -l:libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c display.c free.c render.c move.c init_tex_player.c raycast.c
PARSER_SRCS = parser/parsing.c parser/parsing_map.c

OBJS = $(SRCS:.c=.o) $(PARSER_SRCS:.c=.o)

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