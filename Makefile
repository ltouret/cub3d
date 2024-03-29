# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/20 13:00:20 by ltouret           #+#    #+#              #
#    Updated: 2020/11/30 10:57:07 by ltouret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D 

SRCS = srcs/check_key.c srcs/free_tab.c srcs/parsing.c srcs/retrieve_color.c \
		srcs/retrieve_reso.c srcs/retrieve_map.c srcs/retrieve_text.c \
		srcs/read_file.c srcs/init.c srcs/init_tools.c \
		srcs/validate_map.c srcs/retrieve_sprite.c srcs/add_data.c \
		srcs/error.c srcs/exit.c srcs/sort_sprites.c srcs/build_img.c \
		srcs/player_mov.c srcs/bmp.c srcs/keypress.c srcs/wall_casting.c \
		srcs/sprite_casting.c srcs/main.c 

OBJS = ${SRCS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

FSAN = -fsanitize=address

MATH_FLAGS	= -lm

MLX_FLAGS	= -Lmlx/ -lmlx -lXext -lX11 -lbsd

LIBFT_FLAGS	= -Llibft -lft

INCLUDES	= -I libft -I mlx 

.c.o:
		${CC} ${INCLUDES} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		make -C libft/ 
		make -C mlx/
		${CC} ${OBJS} ${LIBFT_FLAGS} ${MATH_FLAGS} ${MLX_FLAGS} -o ${NAME} 

all:	${NAME}

clean:
		make -C libft clean
		make -C mlx clean                                                       
		${RM} ${OBJS}

fclean:	clean
		make -C libft/ fclean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re
