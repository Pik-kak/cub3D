# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/25 08:54:03 by tsaari            #+#    #+#              #
#    Updated: 2024/11/12 11:33:11 by kkauhane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

CC = cc
RM = rm -rf

PIE_SUPPORTED := $(shell gcc -dumpspecs | grep 'pie' > /dev/null && echo yes || echo no)

ifeq ($(PIE_SUPPORTED), yes)
    CFLAGS += -fPIC
    LDFLAGS += -pie
endif

MLX_DIR = MLX42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLX_TARGET = $(MLX_BUILD_DIR)/libmlx42.a
CFLAGS += -Wall -Wextra -Werror -lm -g #-fsanitize=address
MLXFLAGS = -Iinclude -lglfw
GLFW_DIR = -L"/usr/lib/x86_64-linux-gnu"
LDFLAGS = -ldl -pthread -lm $(GLFW_DIR) -lglfw
LIBFT =	libft/libft.a

SRC_DIR		= src/
MAIN_SRCS	= main.c \
				init.c \
				init2.c \
				free_and_exit.c \
				key_hooks.c \
				raycaster.c \
				raycaster_utils.c \
				raycast_math.c \
				collissions.c \
				mouse_hook.c \
				player_movement.c

PARS_DIR	= $(SRC_DIR)parsing/
PARS_SRCS	= read_textr_col.c \
				parse_textr_col.c \
				parse_utils.c \
				parse_utils2.c \
				parse_map.c \
				fill_map.c \
				read_utils.c \
				copy_string.c
			
DRAW_DIR	= $(SRC_DIR)draw_and_texture/
DRAW_SRCS	= draw_scene.c \
				draw_walls.c \
				textures.c \
				draw_utils.c \
				draw_utils_color.c \
				draw_minimap.c \
				wand.c \
				draw_floor.c

BONUS_DIR	= bonus/
BSRCS		= 

VPATH		+= $(SRC_DIR):$(PARS_DIR):$(DRAW_DIR)


OBJS = $(MAIN_SRCS:%.c=$(OBJ_DIR)/%.o) $(PARS_SRCS:%.c=$(OBJ_DIR)/%.o) $(DRAW_SRCS:%.c=$(OBJ_DIR)/%.o)
BOBJS		= $(BSRCS:%.c=$(BOBJ_DIR)/%.o)

OBJ_DIR			= obj
BOBJ_DIR		= bobj

all:	$(NAME)

bonus: $(BONUS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BOBJ_DIR):
	@mkdir -p $(BOBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@$(CC) -c $< -o $@
	@echo "\033[0;36mObject $@ [\033[0;32mOK\033[0;36m]\033[0m"

$(BOBJ_DIR)/%.o: $(BONUS_DIR)%.c
	@$(CC) -c $< -o $@
	@echo "\033[0;36mBonus Object $@ [\033[0;32mOK\033[0;36m]\033[0m"

$(MLX_TARGET):
	@mkdir -p $(MLX_BUILD_DIR)
	@cd $(MLX_DIR) && cmake -B build
	@cmake --build $(MLX_BUILD_DIR) -j4

$(LIBFT):
			@make -C "libft" CFLAGS="$(CFLAGS)"

$(NAME):	$(OBJ_DIR) $(OBJS) $(LIBFT) $(MLX_TARGET) libft/*.c
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_TARGET) $(MLXFLAGS) $(GLFW_DIR) $(LDFLAGS) -o $(NAME)
			@echo "\033[1;32mLibft library ready!\n\033[0m"
			@echo "\033[1;32mMLX42 library ready!\n\033[0m"
			@echo "\033[1;32mCub3D compile success!\n\033[0m"

.bonus:		$(BOBJ_DIR) $(BOBJS) $(LIBFT) $(MLX_TARGET) libft/*.c
			@$(CC) $(BOBJS) $(LIBFT) $(MLX_TARGET) $(MLXFLAGS) $(GLFW_DIR) $(LDFLAGS) -o $(NAME)
			@touch .bonus
			@echo "\033[1;32mLibft library ready!\n\033[0m"
			@echo "\033[1;32mMLX42 library ready!\n\033[0m"
			@echo "\033[1;32mCub3D Bonus objects compiled!\n\033[0m"

bonus:		$(BOBJ_DIR) .bonus

clean:
			@$(RM) $(OBJ_DIR) $(BOBJ_DIR) .bonus
			@make clean -C "libft"
			@echo "\033[0;36mClean Cub3D [\033[0;32mDONE\033[0;36m]\033[0m"

fclean:		clean
			@$(RM) $(NAME) $(OBJ_DIR) $(BOBJ_DIR)
			@echo "\033[0;36mFClean Cub3D [\033[0;32mDONE\033[0;36m]\033[0m"

re:			fclean all

rebonus:	fclean bonus

.PHONY:		all clean fclean re bonus