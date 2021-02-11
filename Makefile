# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: charles <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/28 11:28:52 by charles           #+#    #+#              #
#    Updated: 2020/12/28 11:46:57 by charles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

LIBFLAGS	=	-lmlx -lXext -lX11 -lm

NAME		=	miniRT

SRC_BONUS	=	src/bonus/utils/utils.c \
			src/bonus/utils/utils2.c \
			src/bonus/minirt.c \
			src/bonus/utils/bmp_save.c \
			src/bonus/obj_inter/cylinder.c \
			src/bonus/obj_inter/intersection.c \
			src/bonus/obj_inter/light.c \
			src/bonus/obj_inter/sphere_plane.c \
			src/bonus/obj_inter/triangle_square.c \
			src/bonus/vector_maths/matrix_calc.c \
			src/bonus/vector_maths/vector.c \
			src/bonus/vector_maths/vector2.c \
			src/GNL/get_next_line.c \
			src/GNL/get_next_line_utils.c \
			src/bonus/antialiasing/antialiasing.c \
			src/bonus/antialiasing/spheres_mat.c \
			src/bonus/parsing/parsing.c \
			src/bonus/parsing/parsing2.c \
			src/bonus/parsing/parsing3.c \

SRC 		= 	src/utils/utils.c \
			src/utils/utils2.c \
			src/minirt.c \
			src/utils/bmp_save.c \
			src/obj_inter/cylinder.c \
			src/obj_inter/intersection.c \
			src/obj_inter/light.c \
			src/obj_inter/sphere_plane.c \
			src/obj_inter/triangle_square.c \
			src/vector_maths/matrix_calc.c \
			src/vector_maths/vector.c \
			src/vector_maths/vector2.c \
			src/GNL/get_next_line.c \
			src/GNL/get_next_line_utils.c \
			src/antialiasing/antialiasing.c \
			src/parsing/parsing.c \
			src/parsing/parsing2.c \
			src/parsing/parsing3.c \

HEADER		=	./include

MLX			=	./src/minilibx-linux

all: $(NAME)

$(NAME): 
	make -C ./src/minilibx-linux
	$(CC) -o $(NAME) -I$(HEADER) $(CFLAGS) $(SRC) -L$(MLX) $(LIBFLAGS)

bonus:
	make -C ./src/minilibx-linux
	$(CC) -o $(NAME) -I$(HEADER) $(CFLAGS) $(SRC_BONUS) -L$(MLX) $(LIBFLAGS)

clean:
	make -C ./src/minilibx-linux clean
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY: clean fclean all re
