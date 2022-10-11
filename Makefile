# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinypark <jinypark@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 17:01:08 by jinypark          #+#    #+#              #
#    Updated: 2022/10/11 18:39:06 by minsuki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			=	cc
NAME		=	miniRT
RM 			=	rm -vf
CFLAGS 		=	-Wall -Wextra -Werror -g3 -fsanitize=address
LIBFT_DIR 	=	libft
LIBFT		=	libft.a
LIBMLX_DIR 	=	mlx
LIBMLX 		=	libmlx.dylib

MANDA_SRCS 	=	minirt.c vector.c material.c utils.c object.c put.c remove.c
BONUS_SRCS 	=	minirt.c vector.c

OBJS_MANDA 	=	$(MANDA_SRCS:.c=.o)
OBJS_BONUS	=	$(BONUS_SRCS:.c=.o)

ifdef BONUS_FLAG
	OBJS = $(OBJS_BONUS)
else
	OBJS = $(OBJS_MANDA)
endif

all: | $(LIBFT_DIR)/$(LIBFT) $(LIBMLX) $(NAME)

$(NAME): $(OBJS)
	@echo "[$@] linking ..."
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L. -lmlx -L$(LIBFT_DIR)/ -lft -framework openGL -framework AppKit

$(LIBMLX):
	@make -C $(LIBMLX_DIR)
	@echo "[$@] making ..."
	@mv $(LIBMLX_DIR)/$(LIBMLX) .

$(LIBFT_DIR)/$(LIBFT):
	@make -C $(LIBFT_DIR)/
	@echo "[$@] making ..."


%.o : %.c
	@echo [$<] compiling ...
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(LIBMLX_DIR) -c $< -o $@

bonus:
	make BONUS_FLAG=1 all

clean:
	@echo ">>>>>>clean deleted list<<<<<<<"
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBMLX_DIR)
	@$(RM) $(OBJS) $(OBJS_BONUS)
# make clean -C $(MLX_DIR)

fclean: clean
	@echo ">>>>>>fclean deleted list<<<<<<<"
	@$(RM) $(LIBFT_DIR)/$(LIBFT)
	@$(RM) $(LIBMLX)
	@$(RM) $(NAME)

re:
	@make fclean
	@make all

run:
	@make all
	@make clean
	./miniRT

.PHONY: all clean fclean re bonus
