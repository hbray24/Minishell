# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbray <hbray@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/23 17:10:15 by asauvage          #+#    #+#              #
#    Updated: 2026/03/31 14:52:14 by hbray            ###   ########.fr        #
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

SRCS = split.c \
	   split_utils.c \
	   init_struct.c \
	   free.c \
	   utils_linked_lst.c \
	   lexer.c \
	   brut_cmd.c \
	   envp.c \
	   ast.c \
	   main.c \

SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

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