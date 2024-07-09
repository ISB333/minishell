# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 11:33:14 by adesille          #+#    #+#              #
#    Updated: 2024/07/09 07:41:12 by isb3             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## ARGUMENTS ########################

NAME = minishell
CFLAGS += -Wall -Wextra -MP -MD -g3 -I. -I/usr/include/readline
CC = cc 

DEFAULT = \033[0;39m
BLUE = \033[0;34m
GREEN = \033[0;32m
RED = \033[31;1m
WHITE = \033[0;37m

######################## SOURCES ########################

SRCS = main.c ./srcs/get_prompt.c \
	./srcs/memory_manager.c ./srcs/memory_manager_utils.c \
	./srcs/execution.c ./srcs/signals.c

HISTORY = ./srcs/history/gnl.c ./srcs/history/gnl_utils.c \
	./srcs/history/manage_history.c 
	
LEXING = ./srcs/lexing/lexer.c ./srcs/lexing/is_sh1.c \
	./srcs/lexing/is_sh2.c ./srcs/lexing/is_sh_in_arr1.c \
	./srcs/lexing/is_sh_in_arr2.c ./srcs/lexing/is_dollar.c \
	./srcs/lexing/utils1.c ./srcs/lexing/utils2.c \
	./srcs/lexing/utils3.c 
	
PARSING = ./srcs/parsing/parsing.c ./srcs/parsing/parse_utils1.c \
	./srcs/parsing/parse_utils2.c ./srcs/parsing/parse_utils3.c \
	./srcs/parsing/parse_utils4.c 

BUILTINS = ./srcs/builtins/get_env.c ./srcs/builtins/get_cwd.c \
		./srcs/builtins/builtins.c ./srcs/builtins/builtins_utils1.c \
		./srcs/builtins/builtins_utils2.c ./srcs/builtins/builtins_utils3.c

OFLAGS += -Wall -Wextra -g3 -I. -I/usr/include/readline
OBJ_DIR = .obj
DEPFILES = $(SRCS:%.c=$(OBJ_DIR)/%.o.d) \
		$(HISTORY:%.c=$(OBJ_DIR)/%.o.d) \
		$(LEXING:%.c=$(OBJ_DIR)/%.o.d) \
		$(PARSING:%.c=$(OBJ_DIR)/%.o.d) \
		$(BUILTINS:%.c=$(OBJ_DIR)/%.o.d)

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o) \
		$(HISTORY:%.c=$(OBJ_DIR)/%.o) \
		$(LEXING:%.c=$(OBJ_DIR)/%.o) \
		$(PARSING:%.c=$(OBJ_DIR)/%.o) \
		$(BUILTINS:%.c=$(OBJ_DIR)/%.o)

######################## UTILS ########################

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

GREEN = \033[0;92m
CURRENT_DATE	:= $(shell date +"%Y-%m-%d %H:%M")

VALGRIND = valgrind -s --leak-check=full --track-origins=yes --track-fds=yes \
	--show-leak-kinds=all --trace-children=yes --gen-suppressions=all --suppressions=valgrind.supp --quiet ./minishell

######################## RULES ########################

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

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
	@valgrind -s --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all --trace-children=yes --suppressions=valgrind.supp --quiet ./minishell

clean :
	@rm -rf $(OBJ_DIR) $(DEPFILES)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(BLUE)\nEvery files are cleaned$(DEFAULT)"

fclean : clean
	@rm -f $(NAME)

re : fclean all

git:
	@git add . > /dev/null 2>&1
	@git commit -m "$(CURRENT_DATE)" > /dev/null 2>&1
	@git push > /dev/null 2>&1
	@echo "$(GREEN)┌(メ▼▼)┘ GIT UPDATE └(▼▼メ)┐ $(DEF_COLOR)"

-include $(DEPFILES)

.PHONY : all clean fclean re val