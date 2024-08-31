/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:22:02 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/31 16:08:18 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "minishell.h"

// 🌟 General Function Prototypes ------------------------------------------ 🌟 */

char		*get_prompt(char *env[]);
int			execute(t_ast *ast);
void		signals_handler(void);
int			return_(int code, int token);

// 📜 History Module ------------------------------------------------------- 📜 */

char		*gnhell(int fd);
int			append_new_history(char *rl);
int			add_previous_history(void);
void		history(char *rl);

// 🔍 Lexing Module -------------------------------------------------------- 🔍 */

char		**lexer(char *str);
void		get_dollar(char **arr, int i, int k, int j);
void		get_tilde(char **arr);
char		*home_paths(char *to_find, int token);
char		***split_array(char ***arr, char **tok, int i, int k);
int			lexer_utils(char ****array, char **tokens);

// ✅ Condition Checks ----------------------------------------------------- ✅ */

int			is_sh_ope(char *s, int i, char token);
int			is_del(char c);
int			is_quotes(char *s, int i, char token);
int			is_pipe(char *s, int i, char token);
int			is_redir(char *s, int i, char token);
int			is_append(char *s, int i, char token);
int			is_heredoc(char *s, int i, char token);
int			is_dollar(char *s, int token);
int			is_dollar_del(char c);
int			is_dollar_in_arr(char **arr, int i, char tok, char pos);
int			is_dollar_utils(char **arr, int i, int k, int pos);
int			is_dollar_in_double_quotes(char *s, int k, int i);
int			is_tilde_in_arr(char **arr, int i);
int			is_pipe_in_arr(char **array);
int			is_redir_in_arr(char **array);
int			is_open_pipe_in_arr(char **array);
int			is_only_dollar(char *s);
int			is_builtin(t_ast *ast);
int			is_only_del(char *s);
int			is_there_quotes_in_da_shit(char *s);

// 🛠️ Utility Functions -------------------------------------------------- 🛠️ */

int			add_space(char **s, int i, int k, int token);
char		**splitter(char **array, char *s);
int			count_rows(char *s, int rows);
int			split_utils_char(t_split *i, char *s, char **array);
int			split_utils_quotes(t_split *i, char *s, char **array);
int			open_quotes(char *s);
int			array_len(char **tokens);
char		*open_pipe_manager(void);
char		*join_new_str(char *str, char *new_str, int len, int i);

void		init_lst(t_ast **ast);
t_ast		*return_tail(t_ast *ast);
int			cmd_path_init(t_ast **ast, int i);
int			check_if_directory(t_ast **ast);
int			check_if_directory_utils(t_ast **ast);

int			parse_redir(t_ast **ast, char **tokens, int i, int n);
int			parse_cmd(t_ast **ast, char **tokens, int *i, int j);
int			parse_heredoc(t_ast **ast, char **t, int *i, int n);
int			parse_append(t_ast **ast, char **tokens, int *i);

char		*quotes_destroyer(char *s, int i, int k, int token);
int			strlen_minus_quotes(char *s, int token, int len, int i);
int			cmdlen(char **tokens, int *i);

void		*mem_manager(size_t size, void *ptr, int fd, int token);
void		ff(t_memman *mem_list, int i);
void		ff_lock(t_memman *mem_lock);
void		close_all_fds(t_memman *mem_list);
int			error(char *msg, char *file, int return_code);
char		*error_init(char *msg, char *file);

void		*get_node_at(void *list, const int n);
t_bool		is_numeric(const char c);
t_bool		is_safe_operation(long long previous, long long current);
t_bool		is_whitespace(const char c);

int			close_file_descriptor(const t_fd fd);
int			duplicate_fd(const t_fd fd, const int std);
int			set_pipe(t_pipe_fd *fd);

// ⚙️ Parsing Module ----------------------------------------------------- ⚙️ */

int			parser(t_ast **ast, char *s);

// 🚀 Builtins ------------------------------------------------------------- 🚀 */

void		call_builtins(t_ast *cmd_node, const int builtin_command);
void		exitt(const t_string *cmd);
t_string	get_cwdd(const t_string cwd, t_string new_dir, const int action);
size_t		count_dir(t_string path);
void		*get_envv(t_string env[], const t_string var, const int action);
void		echoo(t_string *args);
void		pwdd(void);
int			cd(t_string *args);
void		exportt(const t_string new_var, const int action);
void		init_export(t_string env[], t_export **exp);
void		add_node_exp(t_export **exp_list, const t_string var);
void		quit(int status);
t_bool		is_only_n(t_string arg);
int			cd_utils(t_string *args);
t_string	join_cwd(t_cwd *cwd);
void		init_env(t_string env[], t_env **env_head);
void		add_env_var(t_env **env_list, const t_string var);

t_bool		is_valid_env_var(t_string var);
t_string	find_env_var_value(t_env *env, const t_string to_find);
t_string	*retrieve_or_display_env(t_env *env_list, const int action);

void		modify_exp_var(t_export *export_list, const t_string var);
void		wait_for_children(t_ast *cmd);
void		display_errors(t_ast *cmd);

t_bool		is_in_execution(const t_action action);
t_bool		is_in_heredoc(const t_action action);

void		set_signals(void);

#endif