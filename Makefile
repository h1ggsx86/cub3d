# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/24 19:27:15 by tnedel            #+#    #+#              #
#    Updated: 2025/02/24 15:10:33 by tnedel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3 -O0

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


INC_DIR	= includes
NAME	= cub3d

SRC_DIR	= srcs
OBJ_DIR = obj
SRC		= $(SRC_DIR)/main.c
SRC_OBJ	= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: title $(NAME)
		@echo
		@echo "$(NEWLINE)\e[0;32mCompilation Done !\e[0m"
		@echo

$(NAME): $(SRC_OBJ)
		@$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
		@echo -n "Compiling..."
		@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@
		@echo -n "$< "
		@echo "-> \e[0;32m[OK]\e[0m"

$(OBJ_DIR):
		@mkdir -p $@

title:
		@$(call title_var)

clean: title
		@echo "$(NEWLINE)\e[0;33mRemoving obj..."
		@if [ ! -d "$(OBJ_DIR)" ]; \
		then \
			echo "Repo '.o' already clean\e[0m"; echo ; \
		else \
			rm -rfv $(OBJ_DIR); \
			echo "\e[0m"; \
		fi

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