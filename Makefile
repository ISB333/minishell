# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adesille <adesille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 11:33:14 by adesille          #+#    #+#              #
#    Updated: 2024/08/29 13:06:22 by adesille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## ARGUMENTS ########################

NAME = minishell
CFLAGS += -Wall -Wextra -MP -MD -g3 -I./headers
CC = cc 

DEFAULT = \033[0;39m
BLUE = \033[0;34m
DARK_GREEN =\033[0;3;32m
RED = \033[31;1m
WHITE = \033[0;37m
YELLOW = \033[0;33m

######################## UTILS ########################

GREEN = \033[0;92m
CURRENT_DATE	:= $(shell date +"%Y-%m-%d %H:%M")

VALGRIND = valgrind -s --leak-check=full --track-origins=yes --track-fds=yes \
	--show-leak-kinds=all --trace-children=yes --gen-suppressions=all --suppressions=valgrind.supp --quiet ./minishell

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

H_DIR = ./srcs/history
L_DIR = ./srcs/lexing
P_DIR = ./srcs/parsing
B_DIR = ./srcs/builtins
U_DIR = ./srcs/utils

######################## SOURCES ########################

SRCS = ./srcs/main.c 

HISTORY = $(H_DIR)/gnhell.c $(H_DIR)/gnhell_utils.c \
	$(H_DIR)/manage_history.c 
	
LEXING = $(L_DIR)/lexer.c \
	$(L_DIR)/is_functions/is_sh1.c $(L_DIR)/is_functions/is_sh2.c \
	$(L_DIR)/is_functions/is_sh_in_arr.c \
	$(L_DIR)/handle_dollar.c $(L_DIR)/handle_tilde.c \
	$(L_DIR)/split.c $(L_DIR)/count_rows.c \
	$(L_DIR)/add_space.c $(L_DIR)/utils.c
	
PARSING = $(P_DIR)/parsing.c $(P_DIR)/commands.c \
	$(P_DIR)/redirection.c $(P_DIR)/heredoc.c \
	$(P_DIR)/parse_utils.c

EXECUTION = ./srcs/execution/execution.c ./srcs/execution/wait_and_print.c

BUILTINS = $(B_DIR)/builtins.c $(B_DIR)/builtins_utils.c \
	$(B_DIR)/get_env.c $(B_DIR)/get_cwd.c \
	$(B_DIR)/exit.c $(B_DIR)/env.c \
	$(B_DIR)/export.c $(B_DIR)/export_utils.c \
	$(B_DIR)/join_cwd.c $(B_DIR)/init_env.c

UTILS = $(U_DIR)/get_prompt.c \
	$(U_DIR)/memory_manager.c $(U_DIR)/memory_manager_utils.c \
	$(U_DIR)/signals.c $(U_DIR)/get_node_at.c \
	$(U_DIR)/is_numeric.c $(U_DIR)/is_whitespace.c \
	$(U_DIR)/is_safe_operation.c $(U_DIR)/fd.c

OFLAGS += -Wall -Wextra -g3 -I./headers -I/usr/include/readline
OBJ_DIR = .obj
DEPFILES = $(SRCS:%.c=$(OBJ_DIR)/%.o.d) \
		$(HISTORY:%.c=$(OBJ_DIR)/%.o.d) \
		$(LEXING:%.c=$(OBJ_DIR)/%.o.d) \
		$(PARSING:%.c=$(OBJ_DIR)/%.o.d) \
		$(EXECUTION:%.c=$(OBJ_DIR)/%.o.d) \
		$(BUILTINS:%.c=$(OBJ_DIR)/%.o.d) \
		$(UTILS:%.c=$(OBJ_DIR)/%.o.d)

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o) \
		$(HISTORY:%.c=$(OBJ_DIR)/%.o) \
		$(LEXING:%.c=$(OBJ_DIR)/%.o) \
		$(PARSING:%.c=$(OBJ_DIR)/%.o) \
		$(EXECUTION:%.c=$(OBJ_DIR)/%.o) \
		$(BUILTINS:%.c=$(OBJ_DIR)/%.o) \
		$(UTILS:%.c=$(OBJ_DIR)/%.o)

######################## RULES ########################

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@if [ ! -f .obj/srcs/*.o ]; then \
	    echo "$(YELLOW)\nCompiling minishell files...$(DEFAULT)"; \
	fi
	@$(CC) $(OFLAGS) -c $< -o $@

$(LIBFT) :
	@if [ ! -f ./libft/*.o ]; then \
	    echo "$(RED)\nCompiling libft files...$(DEFAULT)\n"; \
	fi
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory; \

val :
	@$(VALGRIND)
#@valgrind -s --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all --trace-children=yes --suppressions=valgrind.supp --quiet ./minishell

clean :
	@rm -rf $(OBJ_DIR) $(DEPFILES)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(DARK_GREEN)\nEvery files are cleaned$(DEFAULT)"

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