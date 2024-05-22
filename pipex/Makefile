# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 10:16:45 by adesille          #+#    #+#              #
#    Updated: 2024/04/21 10:58:18 by isb3             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## ARGUMENTS ########################

NAME = pipex
DEPFLAGS = -MP -MD
CFLAGS += -Wall -Wextra -Werror $(DEPFLAGS)
CC = cc

######################## SOURCES ########################

SRCS = pipex.c utils.c utils2.c
OBJDIR = 0_obj
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

GREEN = \033[0;92m
CURRENT_DATE	:= $(shell date +"%Y-%m-%d %H:%M")

######################## LIBRARY ########################

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

######################## RULES ########################

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) # Here we're saying that in order to build this binary, we need to create all of this
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Regular expression where % is a wildcard (Char(s) used to match multiple chars in a str)
$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@ 
# $@ is the Target ($(OBJDIR)/%.o)

$(LIBFT): # Call the MAKE inside the LIBFT Directory
	@$(MAKE) -C $(LIBFT_DIR) 

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

git:
	@git add . > /dev/null 2>&1
	@git commit -m "$(CURRENT_DATE)" > /dev/null 2>&1
	@git push > /dev/null 2>&1
	@echo "$(GREEN)┌(メ▼▼)┘ GIT UPDATE └(▼▼メ)┐ $(DEF_COLOR)"

-include $(DEPFILES)

.PHONY: all clean fclean re git
