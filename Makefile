NAME = cub3d

INCLUDES = -I/usr/include -Imlx -Ilibft

MLX_LD_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm -lz -Llibft -l:libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c parsing.c parsing_map.c display.c free.c

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): make_libs $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(MLX_LD_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

make_libs:
	make -C mlx
	make -C libft

clean:
	rm -f $(OBJS)
	make -C libft clean
	make -C mlx clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean
	make -C mlx fclean

re: fclean all