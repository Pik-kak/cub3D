# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 14:17:42 by kkauhane          #+#    #+#              #
#    Updated: 2024/09/26 14:17:46 by kkauhane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3D
CFLAGS	= -Wextra -Wall -Werror
LIBMLX := ./lib/MLX42
LIBFTNAME = libft.a
LIBFTDIR := ./libft
LIBMLX	:= ./MLX42
USER	:= kkauhane

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm
SRCS	:= main.c \
        map_parsing.c \
        
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFTDIR)
	@cp $(LIBFTDIR)/$(LIBFTNAME) .
	@mv $(LIBFTNAME) $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): libft $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(HEADERS) -L$(LIBFTDIR) -lft

clean:
	@rm -rf $(OBJS)
	@make -C $(LIBFTDIR) clean
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFTDIR) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
