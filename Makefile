# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 11:05:23 by sesim             #+#    #+#              #
#    Updated: 2022/10/20 15:31:55 by sesim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Cflags
CC 					:=		cc
NAME				:=		miniRT
RM 					:=		rm -vf
CFLAGS 				:=		-Wall -Wextra -Werror -g3 -fsanitize=address
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

# Source files
MANDA_SRCS 			:=		minirt_mandatory.c		\
							mlx_func_mandatory.c

BONUS_SRCS 			:=		minirt_bonus.c			\
							compute_slave_bonus.c	\
							mlx_func_bonus.c

PARSE_SRCS			:=		put_info.c				\
							init_func.c				\
							put_camera.c			\
							put_light.c				\
							put_objects.c			\
							remove.c				\
							put_object_utils.c

LIGHT_SRCS			:=		ray_at_utils.c			\
							phong_light.c			\
							spread_ray.c			\
							ray_at_cap_plane.c		\
							ray_at_sphere.c			\
							ray_at_conlinder.c		\
							bump_utils.c			\
							get_diffuse_specular.c

UTIL_SRCS			:=		ft_atod.c				\
							ft_atoi_exit.c			\
							ft_atovec.c				\
							draw.c					\
							draw_utils.c			\
							math.c

VECTOR_SRCS			:=		vector_arithmetic_op.c	\
							vector_expand_op.c		\
							vector_product_op.c

MY_FUNC_SRCS		:=		my_alloc_func.c			\
							my_free_func.c			\
							my_open_and_err_func.c

INTER_SRCS			:= 		$(UTIL_SRCS)									\
							$(PARSE_SRCS)									\
							$(LIGHT_SRCS)									\
							$(addprefix $(MY_FUNC_DIR), $(MY_FUNC_SRCS))	\
							$(addprefix $(VECTOR_DIR), $(VECTOR_SRCS))

# Include files
INC_INTER	:=	-I$(LIBMLX_DIR)					\
				-I$(LIBFT_INC)					\
				-I$(GNL_INC)					\
				-I$(INTER_DIR)					\
				-I$(INTER_DIR)$(VECTOR_DIR)		\
				-I$(INTER_DIR)$(MY_FUNC_DIR)
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
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

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
