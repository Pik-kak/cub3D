# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/25 08:54:03 by tsaari            #+#    #+#              #
#    Updated: 2024/11/05 14:32:01 by tsaari           ###   ########.fr        #
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
CFLAGS += -Wall -Wextra -Werror -lm -g -fsanitize=address
MLXFLAGS = -Iinclude -lglfw
GLFW_DIR = -L"/usr/lib/x86_64-linux-gnu"
LDFLAGS = -ldl -pthread -lm $(GLFW_DIR) -lglfw
LIBFT =	libft/libft.a

SRC_DIR		= src/
MAIN_SRCS	= main.c \
				init.c \
				free_and_exit.c \
				key_hooks.c \
				raycaster.c \
				raycaster_utils.c \
				raycast_math.c \
				collissions.c \
				mouse_hook.c \
				player_movement.c

PARS_DIR	= $(SRC_DIR)parsing/
PARS_SRCS	= parse_textr_col.c \
				parse_utils.c \
				parse_utils2.c \
				parse_map.c \
				fill_map.c \
				read_utils.c
			
DRAW_DIR	= $(SRC_DIR)draw_and_texture/
DRAW_SRCS	= draw_scene.c \
				draw_walls.c \
				textures.c \
				draw_utils.c \
				draw_utils_color.c \
				draw_minimap.c \
				wand.c

SRC_BONUS_DIR	= src_bonus/
BSRCS		= main_bonus.c \
				init_bonus.c \
				free_and_exit_bonus.c \
				key_hooks_bonus.c \
				raycaster_bonus.c \
				raycaster_utils_bonus.c \
				raycast_math_bonus.c \
				collissions_bonus.c \
				mouse_hook_bonus.c \
				player_movement_bonus.c
				
PARS_BONUS_DIR	= $(SRC_BONUS_DIR)parsing_bonus/
PARS_BONUS_SRCS	= parse_textr_col_bonus.c \
				parse_utils_bonus.c \
				parse_utils2_bonus.c \
				parse_map_bonus.c \
				fill_map_bonus.c \
				read_utils_bonus.c
			
DRAW_BONUS_DIR	= $(SRC_BONUS_DIR)draw_and_texture_bonus/
DRAW_BONUS_SRCS	= draw_scene_bonus.c \
				draw_walls_bonus.c \
				textures_bonus.c \
				draw_utils_bonus.c \
				draw_utils_color_bonus.c \
				draw_minimap_bonus.c \
				wand_bonus.c

VPATH += $(SRC_DIR):$(PARS_DIR):$(DRAW_DIR):$(SRC_BONUS_DIR):$(PARS_BONUS_DIR):$(DRAW_BONUS_DIR)


OBJS	= $(MAIN_SRCS:%.c=$(OBJ_DIR)/%.o) $(PARS_SRCS:%.c=$(OBJ_DIR)/%.o) $(DRAW_SRCS:%.c=$(OBJ_DIR)/%.o)
BOBJS	= $(BSRCS:%.c=$(BOBJ_DIR)/%.o) $(PARS_BONUS_SRCS:%.c=$(BOBJ_DIR)/%.o) $(DRAW_BONUS_SRCS:%.c=$(BOBJ_DIR)/%.o)

OBJ_DIR		= obj
BOBJ_DIR	= bobj

all:	$(NAME)

bonus: bonus_target

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BOBJ_DIR):
	@mkdir -p $(BOBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@$(CC) -c $< -o $@
	@echo "\033[0;36mObject $@ [\033[0;32mOK\033[0;36m]\033[0m"

$(BOBJ_DIR)/%.o: %.c
	@$(CC) -c $< -o $@
	@echo "\033[0;36mBonus Object $@ [\033[0;32mOK\033[0;36m]\033[0m"

$(MLX_TARGET):
	@mkdir -p $(MLX_BUILD_DIR)
	@cd $(MLX_DIR) && cmake -B build
	@cmake --build $(MLX_BUILD_DIR) -j4

$(LIBFT):
	@make -C "libft" CFLAGS="$(CFLAGS)"

$(NAME):	$(OBJ_DIR) $(OBJS) $(LIBFT) $(MLX_TARGET)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_TARGET) $(MLXFLAGS) $(GLFW_DIR) $(LDFLAGS) -o $(NAME)
	@echo "\033[1;32mLibft library ready!\n\033[0m"
	@echo "\033[1;32mMLX42 library ready!\n\033[0m"
	@echo "\033[1;32mCub3D compile success!\n\033[0m"

bonus_target:	$(BOBJ_DIR) $(BOBJS) $(LIBFT) $(MLX_TARGET)
	@$(CC) $(CFLAGS) $(BOBJS) $(LIBFT) $(MLX_TARGET) $(MLXFLAGS) $(GLFW_DIR) $(LDFLAGS) -o $(NAME)
	@touch .bonus
	@echo "\033[1;32mLibft library ready!\n\033[0m"
	@echo "\033[1;32mMLX42 library ready!\n\033[0m"
	@echo "\033[1;32mCub3D Bonus objects compiled!\n\033[0m"

clean:
	@$(RM) $(OBJ_DIR) $(BOBJ_DIR) .bonus
	@make clean -C "libft"
	@echo "\033[0;36mClean Cub3D [\033[0;32mDONE\033[0;36m]\033[0m"

fclean:		clean
	@$(RM) $(NAME) $(OBJ_DIR) $(BOBJ_DIR)
	@echo "\033[0;36mFClean Cub3D [\033[0;32mDONE\033[0;36m]\033[0m"

re: fclean all
rebonus: fclean bonus_target

.PHONY: all clean fclean re bonus
