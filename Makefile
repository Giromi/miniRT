# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 11:05:23 by sesim             #+#    #+#              #
#    Updated: 2022/10/19 18:10:49 by sesim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Cflags
CC 					=		cc
NAME				=		miniRT
RM 					=		rm -vf
CFLAGS 				=		-Wall -Wextra -Werror -g3 -fsanitize=address
FW_FLAGS			=		-framework openGL -framework AppKit

# Libraries
LIBFT_DIR 			=		libft/
LIBFT_INC 			=		$(LIBFT_DIR)libft_src/
GNL_INC 			=		$(LIBFT_DIR)gnl_src/
LIBFT				=		libft.a
LIBMLX_DIR 			=		mlx/
LIBMLX 				=		libmlx.dylib


# Directories
INTER_DIR			=		src_common/
MANDA_DIR			=		src_mandatory/
BONUS_DIR			=		src_bonus/
VECTOR_DIR			=		$(INTER_DIR)vector/
MY_FUNC_DIR			=		$(INTER_DIR)my_funcs/

# Source files
MANDA_SRCS 			=		minirt_mandatory.c

BONUS_SRCS 			=		minirt_bonus.c			\
							compute_slave.c

PARSE_SRCS			=		put_info.c				\
							init_func.c				\
							put_camera.c			\
							put_light.c				\
							put_objects.c			\
							remove.c				\
							put_object_utils.c

LIGHT_SRCS			=		ray_at_utils.c			\
							phong_light.c			\
							spread_ray.c			\
							ray_at_cap_plane.c		\
							ray_at_sphere.c			\
							ray_at_conlinder.c		\
							bump_utils.c			\
							get_diffuse_specular.c

UTIL_SRCS			=		ft_atod.c				\
							ft_atoi_exit.c			\
							ft_atovec.c				\
							draw.c					\
							draw_utils.c			\
							math.c

VECTOR_SRCS			=		vector_arithmetic_op.c	\
							vector_expand_op.c		\
							vector_product_op.c

MY_FUNC_SRCS		=		my_alloc_func.c			\
							my_free_func.c			\
							my_open_and_err_func.c

INTER_SRCS			= 		$(addprefix $(INTER_DIR), $(UTIL_SRCS))		\
							$(addprefix $(INTER_DIR), $(PARSE_SRCS))	\
							$(addprefix $(INTER_DIR), $(LIGHT_SRCS))	\
							$(addprefix $(MY_FUNC_DIR), $(MY_FUNC_SRCS))\
							$(addprefix $(VECTOR_DIR), $(VECTOR_SRCS))

# Object files

# Include files
INC_INTER	=	-I$(VECTOR_DIR)		\
				-I$(LIBMLX_DIR)		\
				-I$(MY_FUNC_DIR)	\
				-I$(LIBFT_INC)		\
				-I$(INTER_DIR)		\
				-I$(GNL_INC)

# INC_MANDA	=	-I$(MANDA_DIR)
INC_BONUS	=	-I$(BONUS_DIR)

# OBJS_INTER 	=	$(INTER_SRCS:.c=.o)
# OBJS_MANDA 	=	$(MANDA_SRCS:.c=.o)
# OBJS_BONUS	=	$(BONUS_SRCS:.c=.o)

ifdef BONUS_FLAG
	UNION_SRCS	=	$(INTER_SRCS) $(addprefix $(BONUS_DIR), $(BONUS_SRCS))
	INCS		=	$(INC_INTER) $(INC_BONUS)
else
	UNION_SRCS	=	$(INTER_SRCS) $(addprefix $(MANDA_DIR), $(MANDA_SRCS))
	INCS 		= 	$(INC_INTER)
endif

OBJS		=	$(UNION_SRCS:.c=.o)

all: | $(LIBFT_DIR)$(LIBFT) $(LIBMLX) $(NAME)

$(NAME): $(OBJS)
	@echo "[$@] linking ..."
	@$(CC) $(CFLAGS) -o $@ $^ -L. -lmlx -L$(LIBFT_DIR) -lft $(INCS) $(FW_FLAGS)

$(LIBMLX):
	@make -C $(LIBMLX_DIR)
	@echo "[$@] making ..."
	@mv $(LIBMLX_DIR)$(LIBMLX) .

$(LIBFT_DIR)$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "[$@] making ..."

%.o : %.c
	@echo [$<] compiling ...
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

bonus:
	@make BONUS_FLAG=1 all

clean:
	@echo ">>>>>>clean deleted list<<<<<<<"
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBMLX_DIR)
	@$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	@echo ">>>>>>fclean deleted list<<<<<<<"
	@$(RM) $(LIBFT_DIR)$(LIBFT)
	# @$(RM) $(LIBMLX)
	@$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re bonus
