# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 16:35:56 by arotondo          #+#    #+#              #
#    Updated: 2025/03/07 16:17:40 by arotondo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRC_FILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			ft_atoi.c ft_calloc.c ft_strcmp.c ft_strdup.c ft_strcat.c ft_atol.c \
			ft_swap.c ft_isspace.c
FILES_2 = ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
			ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c
BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c
SRC_HEADER = libft.h
OBJ_FILES = $(SRC_FILES:.c=.o) $(FILES_2:.c=.o)
OBJ_BONUS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC_HEADER) -c $(SRC_FILES) $(FILES_2) $(BONUS)
	ar -rcs $(NAME) $(OBJ_FILES) $(OBJ_BONUS)

bonus:
	$(CC) $(CFLAGS) $(SRC_HEADER) -c $(BONUS)
		ar -rcs $(NAME) $(OBJ_BONUS)
clean:
	rm -rf *.o

fclean: clean
	rm -f $(NAME) $(OBJ_FILES) $(OBJ_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
