# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/20 13:00:20 by ltouret           #+#    #+#              #
#    Updated: 2020/08/01 02:58:55 by ltouret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D 

SRCS = srcs/check_key.c srcs/free_tab.c srcs/parsing.c srcs/retrieve_color.c \
		srcs/retrieve_reso.c srcs/retrieve_map.c srcs/retrieve_text.c \
		srcs/read_file.c srcs/init.c srcs/validate_map.c test.c \
		srcs/add_data.c srcs/error.c

OBJS = ${SRCS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = #-Wall -Wextra -Werror -g3

FSAN = -fsanitize=address

MLX_FLAGS	= -Lmlx/ -lmlx -lXext -lX11 -lbsd

LIBFT_FLAGS	= -Llibft -lft

INCLUDES	= -I libft -I mlx 

.c.o:
		${CC} ${INCLUDES} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		make -C libft/ 
		make -C mlx/
		${CC} ${FSAN} ${OBJS} ${LIBFT_FLAGS} ${MLX_FLAGS} -o ${NAME} 

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
