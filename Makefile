# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 11:33:14 by adesille          #+#    #+#              #
#    Updated: 2024/06/07 11:42:34 by nkieffer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## ARGUMENTS ########################

NAME = minishell
CFLAGS += -Wall -Wextra -Werror -g3 -I. -lreadline -fsanitize=address
CC = cc

######################## SOURCES ########################

SRCS = main.c \
	./srcs/get_prompt.c \
	./srcs/lexing/lexer.c \
	./srcs/lexing/tokenization.c \
	./srcs/lexing/is_sh.c \
	./srcs/lexing/utils1.c

OFLAGS += -Wall -Wextra -g3 -I.
OBJ_DIR = .obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

######################## LIBRARY ########################

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# VALGRIND = valgrind -s --leak-check=full --track-origins=yes --track-fds=yes \
# 	--show-leak-kinds=all --trace-children=yes --gen-suppressions=all --suppressions=valgrind.supp --quiet ./minishell

######################## RULES ########################

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(CC) $(OFLAGS) -c $< -o $@

$(LIBFT) :
	@$(MAKE) -C $(LIBFT_DIR)

clean :
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean


fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re