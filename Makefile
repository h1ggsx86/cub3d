# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/24 19:27:15 by tnedel            #+#    #+#              #
#    Updated: 2025/02/25 15:45:00 by tnedel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3
MLXFLAGS= -L/usr/lib -Lmlx_linux -lmlx_Linux -lXext -lX11 -lm -lz -lbsd

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

MLX_DIR = mlx_linux
INC_DIR	= includes
NAME	= cub3d

MLX_LIB = mlx_linux/libmlx_Linux.a
SRC_DIR	= srcs
OBJ_DIR = obj
SRC		= $(SRC_DIR)/init_game.c $(SRC_DIR)/init_struct.c \
			$(SRC_DIR)/exit_game.c $(SRC_DIR)/put_pixel.c \
			$(SRC_DIR)/main.c
SRC_OBJ	= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: title $(NAME)
		@echo
		@echo "$(NEWLINE)\e[0;32mCompilation Done !\e[0m"
		@echo

$(NAME): $(MLX_LIB) $(SRC_OBJ)
		@$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ $^ $(MLXFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
		@echo -n "Compilings..."
		@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(MLX_DIR) -O3 -c $< -o $@
		@echo -n "$< "
		@echo "-> \e[0;32m[OK]\e[0m"

$(MLX_LIB):
		@echo "Compiling mlx..."
		@(make --no-print-directory -C mlx_linux)
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
		@echo "Cleaning mlx..."
		@(make --no-print-directory -C mlx_linux clean)
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

re: fclean all

.PHONY: all clean fclean re bonus title