# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/24 19:27:15 by tnedel            #+#    #+#              #
#    Updated: 2025/04/02 16:30:23 by arotondo         ###   ########.fr        #
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

NAME = Cub3d
MLX_DIR = mlx-linux
INC_DIR	= includes
LIBFT_DIR = libft

MLX_LIB = mlx-linux/libmlx_Linux.a
LIBFT_LIB = libft/libft.a
SRC_DIR	= srcs
OBJ_DIR = obj
SRC		= 	$(SRC_DIR)/init/init_game.c $(SRC_DIR)/init/init_struct.c \
			$(SRC_DIR)/init/get_textures.c \
			$(SRC_DIR)/loop_game.c $(SRC_DIR)/input.c $(SRC_DIR)/main.c \
			$(SRC_DIR)/parsing/check_map.c $(SRC_DIR)/parsing/parsing_utils.c \
			$(SRC_DIR)/parsing/parse_textures.c $(SRC_DIR)/parsing/parse_map.c \
			$(SRC_DIR)/parsing/parse_colors.c $(SRC_DIR)/parsing/parsing.c \
			$(SRC_DIR)/raycast/loop_raycast.c $(SRC_DIR)/raycast/door_handler.c \
			$(SRC_DIR)/utils/ft_get_time.c $(SRC_DIR)/utils/exit_game.c \
			$(SRC_DIR)/utils/put_pixel_lines.c $(SRC_DIR)/raycast/render.c \
			$(SRC_DIR)/utils/put_pixel.c $(SRC_DIR)/utils/free.c
SRC_OBJ	= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: title $(NAME)
		@echo
		@echo "$(NEWLINE)\e[0;32mCompilation Done !\e[0m"
		@echo

$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(SRC_OBJ)
		@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) -o $@ $^ $(MLXFLAGS) $(LIBFT_LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
		@echo -n "Compilings..."
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
		@echo "\e[0;33mRemoving archive..."
		@(make --no-print-directory -C $(LIBFT_DIR) fclean)
		@echo "\e[0m"

re: fclean all

.PHONY: all clean fclean re bonus title