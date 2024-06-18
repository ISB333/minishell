# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 11:33:14 by adesille          #+#    #+#              #
#    Updated: 2024/06/18 10:45:32 by isb3             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## ARGUMENTS ########################

NAME = minishell
CFLAGS += -Wall -Wextra -MP -MD -g3 -I. -lreadline -fsanitize=address
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
	./srcs/history/gnl.c \
	./srcs/history/gnl_utils.c \
	./srcs/history/manage_history.c \
	./srcs/lexing/lexer.c \
	./srcs/lexing/is_sh1.c \
	./srcs/lexing/is_sh2.c \
	./srcs/lexing/is_sh_in_arr.c \
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

# VALGRIND = valgrind -s --leak-check=full --track-origins=yes --track-fds=yes \
# 	--show-leak-kinds=all --trace-children=yes --gen-suppressions=all --suppressions=valgrind.supp --quiet ./minishell

######################## RULES ########################

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	@echo "$(GREEN)\n$@ is ready !$(DEFAULT)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@if [ ! -f .obj/*.o ]; then \
	    echo "$(RED)\nCompiling minishell files...$(DEFAULT)"; \
	fi
	@$(CC) $(OFLAGS) -c $< -o $@

$(LIBFT) :
	@if [ ! -f $(LIBFT)/*.o ]; then \
	    echo "$(BLUE)\nCompiling libft files...$(DEFAULT)"; \
	fi
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

clean :
	@rm -rf $(OBJ_DIR) $(DEPFILES)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(WHITE)\nEvery files are cleaned$(DEFAULT)"

fclean : clean
	@rm -f $(NAME)

re : fclean all

-include $(DEPFILES)

.PHONY : all clean fclean re