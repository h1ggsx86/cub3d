# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/24 19:27:15 by tnedel            #+#    #+#              #
#    Updated: 2025/04/08 13:31:22 by tnedel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3
MLXFLAGS= -L/usr/lib -Lmlx-linux -lmlx_Linux -lXext -lX11 -lm -lz -lbsd

NEWLINE	= \033[2K\r
define title_var
		@clear
		@echo " _____       _      _____     _ "
		@echo "/  __ \     | |    |____ |   | |"
		@echo "| /  \/_   _| |__      / / __| |"
		@echo "| |   | | | | '_ \     \ \/ _' |"
		@echo "| \__/\ |_| | |_) |.___/ / (_| |"
		@echo " \____/\__,_|_.__/ \____/ \__,_|"
		@echo
endef

NAME = cub3d
BONUS_NAME = cub3d_bonus
MLX_DIR = mlx-linux
INC_DIR	= includes
INC_BONUS_DIR	= includes_bonus
LIBFT_DIR = libft

MLX_LIB = mlx-linux/libmlx_Linux.a
LIBFT_LIB = libft/libft.a
SRC_DIR	= srcs
OBJ_DIR = obj
SRC		= 	$(SRC_DIR)/init/init_game.c $(SRC_DIR)/init/init_struct.c \
			$(SRC_DIR)/init/get_textures.c $(SRC_DIR)/init/others_init.c \
			$(SRC_DIR)/loop_game.c $(SRC_DIR)/input.c $(SRC_DIR)/main.c \
			$(SRC_DIR)/parsing/parsing_checks.c $(SRC_DIR)/parsing/parsing_utils.c \
			$(SRC_DIR)/parsing/parse_textures.c $(SRC_DIR)/parsing/parse_map.c \
			$(SRC_DIR)/parsing/parse_colors.c $(SRC_DIR)/parsing/parsing.c \
			$(SRC_DIR)/raycast/loop_raycast.c \
			$(SRC_DIR)/utils/ft_get_time.c $(SRC_DIR)/utils/exit_game.c \
			$(SRC_DIR)/utils/put_pixel_lines.c $(SRC_DIR)/raycast/render.c \
			$(SRC_DIR)/utils/put_pixel.c $(SRC_DIR)/raycast/math_stuff.c \
			$(SRC_DIR)/utils/free.c \
			$(SRC_DIR)/utils/get_rgb.c
SRC_OBJ	= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SRC_BONUS_DIR = srcs_bonus
OBJ_BONUS_DIR = obj_bonus
SRC_BONUS	= 	$(SRC_BONUS_DIR)/init/init_game_bonus.c $(SRC_BONUS_DIR)/init/init_struct_bonus.c \
			$(SRC_BONUS_DIR)/init/get_textures_bonus.c $(SRC_BONUS_DIR)/init/others_init_bonus.c \
			$(SRC_BONUS_DIR)/loop_game_bonus.c $(SRC_BONUS_DIR)/input_bonus.c $(SRC_BONUS_DIR)/main_bonus.c \
			$(SRC_BONUS_DIR)/parsing/parsing_checks_bonus.c $(SRC_BONUS_DIR)/parsing/parsing_utils_bonus.c \
			$(SRC_BONUS_DIR)/parsing/parse_textures_bonus.c $(SRC_BONUS_DIR)/parsing/parse_map_bonus.c \
			$(SRC_BONUS_DIR)/parsing/parse_colors_bonus.c $(SRC_BONUS_DIR)/parsing/parsing_bonus.c \
			$(SRC_BONUS_DIR)/raycast/loop_raycast_bonus.c $(SRC_BONUS_DIR)/raycast/door_handler_bonus.c \
			$(SRC_BONUS_DIR)/utils/ft_get_time_bonus.c $(SRC_BONUS_DIR)/utils/exit_game_bonus.c \
			$(SRC_BONUS_DIR)/utils/put_pixel_lines_bonus.c $(SRC_BONUS_DIR)/raycast/render_bonus.c \
			$(SRC_BONUS_DIR)/utils/put_pixel_bonus.c $(SRC_BONUS_DIR)/raycast/math_stuff_bonus.c \
			$(SRC_BONUS_DIR)/utils/free_bonus.c $(SRC_BONUS_DIR)/raycast/floor_handler_bonus.c \
			$(SRC_BONUS_DIR)/utils/get_rgb_bonus.c $(SRC_BONUS_DIR)/raycast/door_helper_bonus.c
SRC_OBJ_BONUS	= $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

all: title $(NAME)
		@echo
		@echo "$(NEWLINE)\e[0;32mCompilation Done !\e[0m"
		@echo

$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(SRC_OBJ)
		@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) -o $@ $^ $(MLXFLAGS) $(LIBFT_LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
		@echo -n "Compiling..."
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR) -O3 -c $< -o $@
		@echo -n "$< "
		@echo "-> \e[0;32m[OK]\e[0m"

$(MLX_LIB):
		@echo "Compiling mlx..."
		@(make --no-print-directory -C $(MLX_DIR))
		@echo

$(LIBFT_LIB):
		@echo "Compiling libft..."
		@(make --no-print-directory -C $(LIBFT_DIR))
		@echo

$(OBJ_DIR):
		@mkdir -p $@

bonus: title $(BONUS_NAME)
		@echo
		@echo "$(NEWLINE)\e[0;32m[BONUS] Compilation Done !\e[0m"
		@echo

$(BONUS_NAME): $(MLX_LIB) $(LIBFT_LIB) $(SRC_OBJ_BONUS)
		@$(CC) $(CFLAGS) -I $(INC_BONUS_DIR) -I $(LIBFT_DIR) -o $@ $^ $(MLXFLAGS) $(LIBFT_LIB)

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
		@echo -n "[BONUS] Compiling..."
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -I $(INC_BONUS_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR) -O3 -c $< -o $@
		@echo -n "$< "
		@echo "-> \e[0;32m[OK]\e[0m"

$(OBJ_BONUS_DIR):
		@mkdir -p $@

title:
		@$(call title_var)

clean: title
		@echo "$(NEWLINE)\e[0;33mRemoving obj..."
		@if [ ! -d "$(OBJ_DIR)" ]; \
		then \
			echo "Repo '.o' already clean"; echo ; \
		else \
			rm -rfv $(OBJ_DIR); \
			echo ;\
		fi
		@if [ -d "$(OBJ_BONUS_DIR)" ]; \
		then \
			rm -rfv $(OBJ_BONUS_DIR); \
			echo ;\
		fi
		@echo "Cleaning libft..."
		@(make --no-print-directory -C $(LIBFT_DIR) fclean)
		@echo
		@echo "Cleaning mlx..."
		@(make --no-print-directory -C mlx-linux clean)
		@echo "\e[0m"

fclean: clean
		@echo "\e[0;33mRemoving executable..."
		@if [ -f "$(NAME)" ]; \
		then \
			rm -fv $(NAME); \
			echo "\e[0m"; \
		else \
			echo "Executable already removed\e[0m"; echo ; \
		fi
		@if [ -f "$(BONUS_NAME)" ]; \
		then \
			rm -fv $(BONUS_NAME); \
			echo "\e[0m"; \
		fi
		@echo "\e[0;33mRemoving archive..."
		@(make --no-print-directory -C $(LIBFT_DIR) fclean)
		@echo "\e[0m"

re: fclean all

.PHONY: all clean fclean re bonus title