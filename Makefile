# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbray <hbray@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/23 17:10:15 by asauvage          #+#    #+#              #
#    Updated: 2026/04/08 14:11:04 by hbray            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc

CFLAGS = -Wall -Werror -Wextra -g3 -I include/

NAME = minishell

SRC_DIR = src
OBJ_DIR = obj

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_INC = $(LIBFT_DIR)

SRCS = src/split.c \
	   src/split_utils.c \
	   src/init_struct.c \
	   src/free.c \
	   src/utils_linked_lst.c \
	   src/lexer.c \
	   src/envp.c \
	   src/ast.c \
	   src/exec_ast.c \
	   src/expander/expander.c \
	   src/main.c \
	   src/new_node.c \
	   src/search_cmd.c \
	   src/exec_cmd.c \
	   src/build_in/ft_cd.c \
	   src/build_in/ft_env.c \
	   src/build_in/ft_export_utils.c \
	   src/build_in/ft_export.c \
	   src/build_in/ft_pwd.c \
	   src/build_in/ft_unset.c \
	   src/build_in/ft_echo.c \
	   src/build_in/ft_exit.c \

OBJS := $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
OBJS := $(SRCS:build_in/%.c=$(OBJ_DIR)/%.o)

all : $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		mkdir -p $(@D)
		$(CC) $(CFLAGS) -I $(LIBFT_INC) -c $< -o $@

clean:
		rm -rf $(OBJ_DIR)
		make -C $(LIBFT_DIR) clean

fclean: clean
		rm -rf $(NAME)
		make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re