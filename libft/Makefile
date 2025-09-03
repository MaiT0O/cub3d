# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/17 17:53:43 by cguinot           #+#    #+#              #
#    Updated: 2024/11/17 17:53:43 by cguinot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Définir les chemins des sous-dossiers
LIBFT_DIR    = libft
PRINTF_DIR   = ft_printf
GNL_DIR      = get_next_line

# Les fichiers sources
SRCS         = $(LIBFT_DIR)/ft_isalnum.c $(LIBFT_DIR)/ft_isprint.c $(LIBFT_DIR)/ft_memcmp.c $(LIBFT_DIR)/ft_putchar_fd.c \
              $(LIBFT_DIR)/ft_strlcat.c $(LIBFT_DIR)/ft_strncmp.c $(LIBFT_DIR)/ft_atoi.c $(LIBFT_DIR)/ft_isalpha.c \
              $(LIBFT_DIR)/ft_memcpy.c $(LIBFT_DIR)/ft_putendl_fd.c $(LIBFT_DIR)/ft_strchr.c $(LIBFT_DIR)/ft_strlcpy.c \
              $(LIBFT_DIR)/ft_strnstr.c $(LIBFT_DIR)/ft_tolower.c $(LIBFT_DIR)/ft_bzero.c $(LIBFT_DIR)/ft_isascii.c \
              $(LIBFT_DIR)/ft_memmove.c $(LIBFT_DIR)/ft_putnbr_fd.c $(LIBFT_DIR)/ft_strdup.c $(LIBFT_DIR)/ft_strlen.c $(LIBFT_DIR)/ft_strrchr.c \
              $(LIBFT_DIR)/ft_toupper.c $(LIBFT_DIR)/ft_calloc.c $(LIBFT_DIR)/ft_isdigit.c $(LIBFT_DIR)/ft_memchr.c $(LIBFT_DIR)/ft_memset.c \
              $(LIBFT_DIR)/ft_putstr_fd.c $(LIBFT_DIR)/ft_substr.c $(LIBFT_DIR)/ft_strjoin.c $(LIBFT_DIR)/ft_strtrim.c $(LIBFT_DIR)/ft_itoa.c \
              $(LIBFT_DIR)/ft_strmapi.c $(LIBFT_DIR)/ft_striteri.c $(LIBFT_DIR)/ft_split.c

PRINTF      = $(PRINTF_DIR)/ft_print_type.c $(PRINTF_DIR)/ft_print_type2.c $(PRINTF_DIR)/ft_printf.c

GNL         = $(GNL_DIR)/get_next_line_utils.c $(GNL_DIR)/get_next_line.c

# Nom de la librairie
NAME         = libft.a

# Compilateur et options
CC           = gcc
CFLAGS       = -Wall -Wextra -Werror
AR           = ar rcs

# Objet des fichiers sources
OBJS         = ${SRCS:.c=.o} ${PRINTF:.c=.o} ${GNL:.c=.o}
BONUS_OBJS   = ${BONUS:.c=.o}

# Règles de compilation
%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

# Règle pour créer la libft.a
${NAME}: ${OBJS}
	@${AR} ${NAME} ${OBJS}

# Règle pour la version bonus
bonus: ${OBJS} ${BONUS_OBJS}
	@${AR} ${NAME} ${OBJS} ${BONUS_OBJS}

# Règle par défaut
all: ${NAME}

# Nettoyer les fichiers objets
clean:
	@rm -f ${OBJS} ${BONUS_OBJS}

# Nettoyer et supprimer la librairie
fclean: clean
	@rm -f ${NAME}

# Recompiler complètement
re: fclean all

