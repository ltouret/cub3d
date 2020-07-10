# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/20 13:00:20 by ltouret           #+#    #+#              #
#    Updated: 2020/07/10 23:28:56 by ltouret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D 

SRCS = srcs/check_key.c srcs/free_tab.c srcs/parsing.c srcs/retrieve_color.c \
		srcs/retrieve_reso.c srcs/retrieve_map.c srcs/retrieve_text.c \
		srcs/read_file.c srcs/init.c srcs/validate_map.c test.c

OBJS = ${SRCS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

LIBFT_FLAGS	= -Llibft -lft

INCLUDES	= -I libft

.c.o:
		${CC} ${INCLUDES} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		make -C libft/ 
		${CC} ${OBJS} ${LIBFT_FLAGS} -o ${NAME} 

all:	${NAME}

clean:
		${RM} ${OBJS}
		make -C libft/ clean

fclean:	clean
		${RM} ${NAME}
		make -C libft/ fclean

re:		fclean all

.PHONY: all clean fclean re
