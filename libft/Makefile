# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 11:16:18 by sesim             #+#    #+#              #
#    Updated: 2022/10/12 13:59:58 by sesim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f
NAME = libft.a
SHELL = /bin/bash

LIBFT_DIR = ./libft_src/
GNL_DIR = ./gnl_src/
PRINTF_DIR = ./ft_printf_src/

SRCS = $(LIBFT_DIR)ft_atoi.c \
	   $(LIBFT_DIR)ft_adtoi.c \
	   $(LIBFT_DIR)ft_atoi_hex.c \
	   $(LIBFT_DIR)ft_bzero.c \
	   $(LIBFT_DIR)ft_calloc.c \
	   $(LIBFT_DIR)ft_isalnum.c \
	   $(LIBFT_DIR)ft_isalpha.c \
	   $(LIBFT_DIR)ft_isascii.c \
	   $(LIBFT_DIR)ft_isdigit.c \
	   $(LIBFT_DIR)ft_isprint.c \
	   $(LIBFT_DIR)ft_itoa.c \
	   $(LIBFT_DIR)ft_memcpy.c \
	   $(LIBFT_DIR)ft_memchr.c \
	   $(LIBFT_DIR)ft_memcmp.c \
	   $(LIBFT_DIR)ft_memmove.c \
	   $(LIBFT_DIR)ft_memset.c \
	   $(LIBFT_DIR)ft_strchr.c \
	   $(LIBFT_DIR)ft_strrchr.c \
	   $(LIBFT_DIR)ft_strchr_idx.c \
	   $(LIBFT_DIR)ft_strdup.c \
	   $(LIBFT_DIR)ft_striteri.c \
	   $(LIBFT_DIR)ft_strjoin.c \
	   $(LIBFT_DIR)ft_strlcpy.c \
	   $(LIBFT_DIR)ft_strlcat.c \
	   $(LIBFT_DIR)ft_strlen.c \
	   $(LIBFT_DIR)ft_strmapi.c \
	   $(LIBFT_DIR)ft_strncmp.c \
	   $(LIBFT_DIR)ft_strnstr.c \
	   $(LIBFT_DIR)ft_strtrim.c \
	   $(LIBFT_DIR)ft_substr.c \
	   $(LIBFT_DIR)ft_split.c \
	   $(LIBFT_DIR)ft_toupper.c \
	   $(LIBFT_DIR)ft_tolower.c \
	   $(LIBFT_DIR)ft_putchar_fd.c \
	   $(LIBFT_DIR)ft_putstr_fd.c \
	   $(LIBFT_DIR)ft_putendl_fd.c \
	   $(LIBFT_DIR)ft_putnbr_fd.c \
	   $(LIBFT_DIR)ft_lstnew.c \
	   $(LIBFT_DIR)ft_lstadd_front.c \
	   $(LIBFT_DIR)ft_lstsize.c \
	   $(LIBFT_DIR)ft_lstlast.c \
	   $(LIBFT_DIR)ft_lstadd_back.c \
	   $(LIBFT_DIR)ft_lstdelone.c \
	   $(LIBFT_DIR)ft_lstclear.c \
	   $(LIBFT_DIR)ft_lstiter.c \
	   $(LIBFT_DIR)ft_lstmap.c \
	   $(GNL_DIR)get_file.c \
	   $(GNL_DIR)get_next_line.c \
	   $(GNL_DIR)get_next_line_utils.c \
	   $(PRINTF_DIR)ft_printf.c \
	   $(PRINTF_DIR)hex_form.c \
	   $(PRINTF_DIR)char_form.c \
	   $(PRINTF_DIR)num_form.c \
	   $(PRINTF_DIR)unum_form.c

OBJS = $(SRCS:%.c=%.o)

%.o : %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) $@ $^

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHNOY : all clean fclean re bonus
