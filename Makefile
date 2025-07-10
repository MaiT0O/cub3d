NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c parsing.c parsing_map.c display.c free.c

LIBFT = libft/libft.a

OBJS = $(SRCS:.c=.o) $(GNL:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re