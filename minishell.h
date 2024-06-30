/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:24:05 by adesille          #+#    #+#             */
/*   Updated: 2024/06/30 08:52:01 by isb3             ###   ########.fr       */
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
# include <errno.h>
# include "libft/libft.h"

# define RED "\033[0;31m"
# define DEF "\033[0m"

extern int error_code;

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
	int				pipe;
	int				new_line;

	int				append;
	int				infile;
	int				outfile;
	int				heredoc;
	char			*error;
	struct s_ast	*next;
}	t_ast;

typedef enum e_types {
	FD,
	NONE
} ptrType;

typedef struct s_memman
{
    void 	*ptr;
	ptrType type;
    struct s_memman *next;
} t_memman;

typedef struct s_heredoc
{
	char *s;
	struct s_heredoc *next;
} t_heredoc;

char	*get_prompt(void);

	/// History ///
char	*gnhell(int fd);
int		append_new_history(char *rl);
int		add_previous_history();

	/// Lexing ///
char	**lexer(char *str);
void	get_dollar(char **arr);
char	***split_array(char ***array, char **tokens, int i, int k);
int		lexer_utils(char ****array, char **tokens);

		// is_??? //
int		is_dollar(char **arr, int i, char token, char pos);
int		is_sh_ope(char *s, int i, char token);
int		is_del(char c);
int		is_quotes(char *s, int i, char token);
int		is_pipe(char *s, int i, char token);
int		is_redir(char *s, int i, char token);
int		is_append(char *s, int i, char token);
int		is_heredoc(char *s, int i, char token);
int		is_new_line(char **tokens, int i);
int		is_path(char *s);
int		is_pipe_in_arr(char **array);
int		is_new_line_in_arr(char **array);
int		is_redir_in_arr(char **array);
int		is_append_in_arr(char **array);
int		is_heredoc_in_arr(char **array);
int		is_open_pipe_in_arr_arr(char ***array);
int		is_open_pipe_in_arr(char **array);
int		is_there_quotes_in_da_shit(char *s);

		// utils //
int		add_space(char **s, int i, int k, int token);
char	**splitter(char **array, char *s);
int		count_rows(char *s, int rows);
int		split_utils_char(t_split *i, char *s, char **array);
int		split_utils_quotes(t_split *i, char *s, char **array);
int		open_quotes(char *s);
int		array_len(char **tokens);
char	*open_pipe_manager(void);

	/// Parsing ///
int		parser(t_ast **ast, char *s);

		// utils //
void	init_lst(t_ast **ast);
t_ast	*return_tail(t_ast *ast);
int		cmd_path_init(t_ast *ast, int i);

int		parse_redir(t_ast **ast, char **tokens, int i, int n);
int		parse_cmd(t_ast **ast, char **tokens, int *i, int j);
int		parse_heredoc(t_ast **ast, char **tokens, int *i, int n);
int		parse_append(t_ast **ast, char **tokens, int *i);

char	*quotes_destroyer(char *s, int i, int k, int token);
int		strlen_minus_quotes(char *s, int token, int len, int i);
int		cmdlen(char **tokens, int *i);

void	*mem_manager(size_t size, void *ptr, int fd, int token);
void	*ff(t_memman *mem_list);
int		error(char *msg, char *file, int return_code);
char	*error_init(char *msg, char *file);

//sigHandler.c
int	catchBackslash(void);
int	catchC(void);

#endif