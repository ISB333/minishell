# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adesille <adesille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 11:33:14 by adesille          #+#    #+#              #
#    Updated: 2024/07/03 10:05:35 by adesille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## ARGUMENTS ########################

NAME = minishell
CFLAGS += -Wall -Wextra -MP -MD -g3 -I. -lreadline
CC = cc 

DEFAULT = \033[0;39m
BLUE = \033[0;34m
GREEN = \033[0;32m
RED = \033[31;1m
WHITE = \033[0;37m

######################## SOURCES ########################

SRCS = main.c \
	./srcs/get_prompt.c \
	./srcs/memory_manager.c \
	./srcs/memory_manager_utils.c \
	./srcs/history/gnl.c \
	./srcs/history/gnl_utils.c \
	./srcs/history/manage_history.c \
	./srcs/lexing/lexer.c \
	./srcs/lexing/is_sh1.c \
	./srcs/lexing/is_sh2.c \
	./srcs/lexing/is_sh_in_arr1.c \
	./srcs/lexing/is_sh_in_arr2.c \
	./srcs/lexing/is_dollar.c \
	./srcs/lexing/utils1.c \
	./srcs/lexing/utils2.c \
	./srcs/lexing/utils3.c \
	./srcs/parsing/parsing.c \
	./srcs/parsing/parse_utils1.c \
	./srcs/parsing/parse_utils2.c \
	./srcs/parsing/parse_utils3.c \
	./srcs/parsing/parse_utils4.c \
	./sigHandler.c

DEPFILES = $(SRCS:%c=$(OBJ_DIR)/%.o)
OFLAGS += -Wall -Wextra -g3 -I.
OBJ_DIR = .obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

######################## LIBRARY ########################

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

VALGRIND = valgrind -s --leak-check=full --track-origins=yes --track-fds=yes \
	--show-leak-kinds=all --trace-children=yes --gen-suppressions=all --suppressions=valgrind.supp --quiet ./minishell

######################## RULES ########################

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@if [ ! -d .obj/srcs ]; then \
	    echo "$(WHITE)\nCompiling minishell files...$(DEFAULT)"; \
	fi
	@$(CC) $(OFLAGS) -c $< -o $@

$(LIBFT) :
	@if [ ! -f $(LIBFT)/*.o ]; then \
	    echo "$(RED)\nCompiling libft files...$(DEFAULT)\n"; \
	fi
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

val :
# @$(VALGRIND)
	@valgrind -s --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all --suppressions=valgrind.supp --quiet ./minishell

clean :
	@rm -rf $(OBJ_DIR) $(DEPFILES)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(BLUE)\nEvery files are cleaned$(DEFAULT)"

fclean : clean
	@rm -f $(NAME)

re : fclean all

-include $(DEPFILES)

.PHONY : all clean fclean re val