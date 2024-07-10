/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:24:05 by adesille          #+#    #+#             */
/*   Updated: 2024/07/10 10:46:31 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define DEF "\033[0m"

# define CD 301
# define PWD 302
# define EXPORT 303
# define UNSET 304
# define ENV 305
# define ECH 306
# define EXIT 307

# define DUP_STD 320
# define CLOSE_STD 321

# define INIT 330
# define ADD 331
# define PRINT 332
# define MODIF 333
# define FIND 334
# define GET 335
# define UPDATE 336

extern int				g_error_code;

typedef struct s_prompt
{
	char				*name;
	char				*pos;
	char				*curr_dir;
	char				*root_dir;
}						t_prompt;

typedef struct s_split
{
	int					i;
	int					k;
	size_t				j;
	int					token;
}						t_split;

typedef struct s_ast
{
	char				**cmd;
	char				*cmd_path;
	int					fd_in;
	int					fd_out;
	int					pipe_fd[2];
	pid_t				pid;
	char				*error;
	struct s_ast		*next;
}						t_ast;

typedef enum e_types
{
	FD,
	NONE
}						t_ptr_type;

typedef struct s_memman
{
	void				*ptr;
	t_ptr_type			type;
	struct s_memman		*next;
}						t_memman;

typedef struct s_heredoc
{
	char				*s;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_env
{
	char				*var;
	struct s_env		*next;
}						t_env;

typedef struct s_cwd
{
	char				*dir;
	struct s_cwd		*next;
}						t_cwd;

typedef struct s_export
{
	char				*var;
	struct s_export		*next;
}						t_export;

char					*get_prompt(void);
int						warlord_executor(t_ast *ast, char *env[]);
void					print_lst(t_ast *ast);
void					signals_handler(void);

void disable_raw_mode();
void enable_raw_mode();

/// History ///
char					*gnhell(int fd);
int						append_new_history(char *rl);
int						add_previous_history(void);

/// Lexing ///
char					**lexer(char *str);
void					get_dollar(char **arr);
char					***split_array(char ***arr, char **tok, int i, int k);
int						lexer_utils(char ****array, char **tokens);

// is_??? //
int						is_sh_ope(char *s, int i, char token);
int						is_del(char c);
int						is_quotes(char *s, int i, char token);
int						is_pipe(char *s, int i, char token);
int						is_redir(char *s, int i, char token);
int						is_append(char *s, int i, char token);
int						is_heredoc(char *s, int i, char token);
int						is_new_line(char **tokens, int i);
int						is_path(char *s);
int						is_dollar(char *s, int token);
int						is_dollar_in_arr(char **arr, int i, char tok, char pos);
int						is_dollar_utils(char **arr, int i, int k, int pos);
int						is_dollar_in_double_quotes(char *s, int k, int i);
int						is_pipe_in_arr(char **array);
int						is_new_line_in_arr(char **array);
int						is_redir_in_arr(char **array);
int						is_append_in_arr(char **array);
int						is_heredoc_in_arr(char **array);
int						is_open_pipe_in_arr_arr(char ***array);
int						is_open_pipe_in_arr(char **array);
int						is_builtin(t_ast *ast);
int						is_only_del(char *s);
int						is_there_quotes_in_da_shit(char *s);

// utils //
int						add_space(char **s, int i, int k, int token);
char					**splitter(char **array, char *s);
int						count_rows(char *s, int rows);
int						split_utils_char(t_split *i, char *s, char **array);
int						split_utils_quotes(t_split *i, char *s, char **array);
int						open_quotes(char *s);
int						array_len(char **tokens);
char					*open_pipe_manager(void);
char					*join_new_str(char *str, char *new_str, int len, int i);

/// Parsing ///
int						parser(t_ast **ast, char *s);

// utils //
void					init_lst(t_ast **ast);
t_ast					*return_tail(t_ast *ast);
int						cmd_path_init(t_ast **ast, int i);

int						parse_redir(t_ast **ast, char **tokens, int i, int n);
int						parse_cmd(t_ast **ast, char **tokens, int *i, int j);
int						parse_heredoc(t_ast **ast, char **t, int *i, int n);
void					get_dollar_hd(t_heredoc *hd);
int						parse_append(t_ast **ast, char **tokens, int *i);

char					*quotes_destroyer(char *s, int i, int k, int token);
int						strlen_minus_quotes(char *s, int token, int len, int i);
int						cmdlen(char **tokens, int *i);
char					**extract_path(void);
int						format_check(char *s, int *code);

void					*mem_manager(size_t size, void *ptr, int fd, int token);
void					ff(t_memman *mem_list, int i);
void					close_all_fds(t_memman *mem_list);
int						error(char *msg, char *file, int return_code);
char					*error_init(char *msg, char *file);

/// builtins ///
void					exit_check(t_ast *ast);
char					*get_cwdd(char *cwd, char *new_dir, int token);
int						count_dir(char *cwd);
char					*get_envv(char *env[], char *to_find, int token);
void					echoo(char **arr);
void					pwdd(void);
int						cd(char **arr);
void					exportt(char *env[], char *new_var, int token);
void					init_export(char *env[], t_export **exp);
void					print_export(t_export *exp);
void					add_node_exp(t_export **exp, char *var);
void					sort_export(t_export *exp);
int						quit(int token);
char					*env_var_search(t_env *envv, char *to_find);
void					print_env(t_env *envv);
int						modify_exp_var(t_export *exp, char *var);
int						is_only_n(char *s);
void					exit_check_utils(t_ast *ast);
int						modify_exp_var(t_export *exp, char *var);
int						is_only_n(char *s);

#endif