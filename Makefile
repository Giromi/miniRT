# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 09:14:03 by sesim             #+#    #+#              #
#    Updated: 2022/10/25 14:51:39 by sesim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 					:=		cc
NAME				:=		miniRT
RM 					:=		rm -vf
CFLAGS 				:=		-Wall -Wextra -Werror -g3# -fsanitize=address
FW_FLAGS			:=		-framework openGL -framework AppKit

# Libraries
LIBFT_DIR 			:=		libft/
LIBFT_INC 			:=		$(LIBFT_DIR)libft_src/
GNL_INC 			:=		$(LIBFT_DIR)gnl_src/
LIBFT				:=		libft.a
LIBMLX_DIR 			:=		mlx/
LIBMLX 				:=		libmlx.dylib

# Directories
INTER_DIR			:=		src_common/
MANDA_DIR			:=		src_mandatory/
BONUS_DIR			:=		src_bonus/
VECTOR_DIR			:=		vector/
MY_FUNC_DIR			:=		my_funcs/
ROTATION_DIR		:=		rotation_funcs/
DRAW_DIR			:=		draw_funcs/
LIGHT_DIR			:=		light_funcs/
PARSE_DIR			:=		parse_funcs/
MLX_FUNC_DIR		:=		mlx_funcs/

# Source files
MANDA_SRCS 			:=		minirt_mandatory.c		\
							mlx_func_mandatory.c

BONUS_SRCS 			:=		minirt_bonus.c			\
							compute_slave_bonus.c	\
							mlx_func_bonus.c

PARSE_SRCS			:=		init_func.c				\
							put_info.c				\
							put_camera.c			\
							put_light.c				\
							put_objects.c			\
							put_object_utils.c		\
							remove.c						# 필히  지지울울것것

LIGHT_SRCS			:=		spread_ray.c			\
							ray_at_utils.c			\
							ray_at_cap_plane.c		\
							ray_at_sphere.c			\
							ray_at_conlinder.c		\
							phong_light.c			\
							bump_utils.c			\
							get_diffuse_specular.c	\
							cal_root_funcs.c

DRAW_SRCS			:=		draw.c					\
							draw_utils.c			\

VECTOR_SRCS			:=		vector_arithmetic_op.c	\
							vector_expand_op.c		\
							vector_product_op.c

MY_FUNC_SRCS		:=		my_alloc_func.c			\
							my_free_func.c			\
							my_open_and_err_func.c	\
							ft_atoi_exit.c			\
							ft_atovec.c				\
							ft_atod.c

MLX_FUNC_SRCS		:=		mlx_key_func.c			\
							mlx_mouse_func.c		\
							mlx_key_obj_func.c

ROT_FUNC_SRCS		:=		rotate_func.c			\
							rotation_func_utils.c

INTER_SRCS			:=		$(addprefix $(MY_FUNC_DIR), $(MY_FUNC_SRCS))	\
							$(addprefix $(VECTOR_DIR), $(VECTOR_SRCS))		\
							$(addprefix $(ROTATION_DIR), $(ROT_FUNC_SRCS))	\
							$(addprefix $(DRAW_DIR), $(DRAW_SRCS))			\
							$(addprefix $(LIGHT_DIR), $(LIGHT_SRCS))		\
							$(addprefix $(PARSE_DIR), $(PARSE_SRCS))		\
							$(addprefix $(MLX_FUNC_DIR), $(MLX_FUNC_SRCS))

# Include files
INC_INTER	:=	-I$(LIBMLX_DIR)					\
				-I$(LIBFT_INC)					\
				-I$(GNL_INC)					\
				-I$(INTER_DIR)					\
				-I$(INTER_DIR)$(VECTOR_DIR)		\
				-I$(INTER_DIR)$(MY_FUNC_DIR)	\
				-I$(INTER_DIR)$(ROTATION_DIR)	\
				-I$(INTER_DIR)$(DRAW_DIR)		\
				-I$(INTER_DIR)$(LIGHT_DIR)		\
				-I$(INTER_DIR)$(PARSE_DIR)

INC_BONUS	:=	-I$(BONUS_DIR)

INTER_PATH_SRCS := $(addprefix $(INTER_DIR), $(INTER_SRCS))
MANDA_PATH_SRCS := $(addprefix $(MANDA_DIR), $(MANDA_SRCS))
BONUS_PATH_SRCS := $(addprefix $(BONUS_DIR), $(BONUS_SRCS))

# ifdef BONUS_FLAG
#     UNION_SRCS	=	$(INTER_PATH_SRCS) $(BONUS_PATH_SRCS)
#     INCS		=	$(INC_INTER) $(INC_BONUS)
# else
UNION_SRCS	=	$(INTER_PATH_SRCS) $(MANDA_PATH_SRCS)
INCS 		= 	$(INC_INTER)
# endif
#
# Object files
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

%.o: %.c
	@echo [$<] compiling ...
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# bonus:
#     @make BONUS_FLAG=1 all

bonus:
	@make \
	"UNION_SRCS		=	$(INTER_PATH_SRCS) $(BONUS_PATH_SRCS)"	\
	"INCS			=	$(INC_INTER) $(INC_BONUS)"				\
	all

clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBMLX_DIR)
	@echo ">>>>>>miniRT clean deleted list<<<<<<<"
	@$(RM)	$(INTER_PATH_SRCS:.c=.o) \
			$(MANDA_PATH_SRCS:.c=.o) \
			$(BONUS_PATH_SRCS:.c=.o)

fclean: clean
	@echo ">>>>>>fclean deleted list<<<<<<<"
	@$(RM) $(LIBFT_DIR)$(LIBFT)
	# @$(RM) $(LIBMLX)
	@$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re bonus
