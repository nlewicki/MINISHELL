# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 11:07:18 by nlewicki          #+#    #+#              #
#    Updated: 2024/09/17 13:09:22 by mhummel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = ft_bzero.c \
		ft_atoi.c \
		ft_atol.c \
		ft_calloc.c \
		ft_isalpha.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strstrim.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_split.c \
		ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c \
		ft_strcmp.c \
		ft_strtok.c \
		ft_isspace.c \
		ft_strndup.c \
		ft_strcpy.c \
		ft_strtok_r.c \
		ft_strspn.c \
		ft_strcspn.c

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
OBJ_DIR	= Obj_libft
OFILES	= $(addprefix $(OBJ_DIR)/,$(notdir $(FILES:.c=.o)))
NAME	= libft.a

$(NAME): $(OBJ_DIR) $(OFILES)
	@ar rsc $(NAME) $(OFILES)

$(OBJ_DIR)/%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR):
	@echo "\033[35mCompiling $(NAME)\033[0m"
	@mkdir -p $(OBJ_DIR)

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
