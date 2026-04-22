# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbray <hbray@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/23 17:10:15 by asauvage          #+#    #+#              #
#    Updated: 2026/04/22 13:43:40 by hbray            ###   ########.fr        #
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

SRCS = src/build_in/ft_cd_utils.c \
	   src/build_in/ft_cd.c \
	   src/build_in/ft_echo.c \
	   src/build_in/ft_env.c \
	   src/build_in/ft_exit.c \
	   src/build_in/ft_export_utils.c \
	   src/build_in/ft_export.c \
	   src/build_in/ft_pwd.c \
	   src/build_in/ft_unset.c \
	   src/execution/exec_ast_utils.c \
	   src/execution/exec_ast.c \
	   src/execution/exec_ast2.c \
	   src/execution/exec_cmd.c \
	   src/execution/here_doc.c \
	   src/execution/search_cmd.c \
	   src/expander/expander_utils.c \
	   src/expander/expander.c \
	   src/parsing/ast_utils.c \
	   src/parsing/ast.c \
	   src/parsing/lexer.c \
	   src/parsing/split_utils.c \
	   src/parsing/split.c \
	   src/signal/signal_ctrl_backslash.c \
	   src/signal/signal.c \
	   src/utils_lst/envp.c \
	   src/utils_lst/lst_token.c \
	   src/utils_lst/utils_linked_lst.c \
	   src/free.c \
	   src/main.c \

OBJS := $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

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