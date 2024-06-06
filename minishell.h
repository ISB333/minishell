/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:24:05 by adesille          #+#    #+#             */
/*   Updated: 2024/06/06 12:35:15 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <termcap.h>
# include <curses.h>
# include "libft/libft.h"

typedef struct s_prompt
{
	char	*logname;
	char	*pos;
	char	*curr_dir;
	char	*root_dir;
}	t_prompt;	

typedef struct s_ast
{
	char			**cmd;
	char			*cmd_path;
	int				fd_in;
	int				fd_out;
	struct s_ast	*next;
}	t_ast;

char	*get_prompt();

	/// History ///
char	*gnhell(int fd);
int		append_new_history(char *rl);
int		add_previous_history();

	/// Lexing ///
char	**lexer(char *str);
int		is_sh_ope(char *s, int i, char token);
int		is_del(char c);
int		quotes_manager(char **tokens);
// int		is_quotes(char *s, int i, char token);
int		closing_quotes_pos(char *s, int i);

size_t	count_rows(char *s);
int		add_space(char **s, int i, int k);
char	**splitter(char **array, char *s, size_t i);

int		is_dollar(char **arr, int i, char token, char pos);
int		get_dollar(char **arr);

	/// Parsing ///
int		parser(t_ast **ast, char **tokens);
void	free_memory(char **array);

#endif