/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:24:05 by adesille          #+#    #+#             */
/*   Updated: 2024/06/11 12:01:39 by adesille         ###   ########.fr       */
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
	char	*name;
	char	*pos;
	char	*curr_dir;
	char	*root_dir;
}	t_prompt;	

typedef	struct s_split
{
	int		i;
	int		k;
	size_t	j;
	int		token;
}	t_split;


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
int		closing_quotes_pos(char *s, int i);

int		count_rows(char *s, int rows);
int		add_space(char **s, int i, int k, int token);
char	**splitter(char **array, char *s);
int		split_utils_char(t_split *i, char *s, char **array);
int		split_utils_quotes(t_split *i, char *s, char **array);
void	free_mem(char **array, size_t j);
int		get_dollar(char **arr);

		// is_??? //
int		is_dollar(char **arr, int i, char token, char pos);
int		is_sh_ope(char *s, int i, char token);
int		is_del(char c);
int		is_quotes(char *s, int i, char token);
int		is_pipe(char *s, int i, char token);
int		is_redir(char *s, int i, char token);
int		is_append(char *s, int i, char token);
int		is_heredoc(char *s, int i, char token);

	/// Parsing ///
int		parser(t_ast **ast, char **tokens);
void	free_memory(char **array);

#endif