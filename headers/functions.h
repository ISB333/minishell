/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:22:02 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/20 16:05:33 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "minishell.h"

// 🌟 General Function Prototypes ------------------------------------------ 🌟 */

char		*get_prompt(void);
int			warlord_executor(t_ast *ast);
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
int			is_new_line(char **tokens, int i);
int			is_path(char *s);
int			is_dollar(char *s, int token);
int			is_dollar_del(char c);
int			is_dollar_in_arr(char **arr, int i, char tok, char pos);
int			is_dollar_utils(char **arr, int i, int k, int pos);
int			is_dollar_in_double_quotes(char *s, int k, int i);
int			is_tilde_in_arr(char **arr, int i);
int			is_pipe_in_arr(char **array);
int			is_new_line_in_arr(char **array);
int			is_redir_in_arr(char **array);
int			is_append_in_arr(char **array);
int			is_heredoc_in_arr(char **array);
int			is_open_pipe_in_arr_arr(char ***array);
int			is_open_pipe_in_arr(char **array);
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
long long	ft_atoi_ll(const char *nptr);

int			parse_redir(t_ast **ast, char **tokens, int i, int n);
int			parse_cmd(t_ast **ast, char **tokens, int *i, int j);
int			parse_heredoc(t_ast **ast, char **t, int *i, int n);
void		get_dollar_hd(t_heredoc *hd);
int			parse_append(t_ast **ast, char **tokens, int *i);

char		*quotes_destroyer(char *s, int i, int k, int token);
int			strlen_minus_quotes(char *s, int token, int len, int i);
int			cmdlen(char **tokens, int *i);
int			format_check(char *s, long long *code);

void		*mem_manager(size_t size, void *ptr, int fd, int token);
void		ff(t_memman *mem_list, int i);
void		ff_lock(t_memman *mem_lock);
void		close_all_fds(t_memman *mem_list);
int			error(char *msg, char *file, int return_code);
char		*error_init(char *msg, char *file);

// ⚙️ Parsing Module ----------------------------------------------------- ⚙️ */

int			parser(t_ast **ast, char *s);

// 🚀 Builtins ------------------------------------------------------------- 🚀 */

int			call_builtins(t_ast *ast, int c, int token);
void		exit_check(t_ast *ast);
char		*get_cwdd(char *cwd, char *new_dir, int token);
int			count_dir(char *cwd);
void		*get_envv(t_string env[], const t_string var, const int action);
void		echoo(char **arr);
void		pwdd(void);
int			cd(char **arr);
void		exportt(char *env[], char *new_var, int token);
void		init_export(char *env[], t_export **exp);
void		print_export(t_export *exp);
void		add_node_exp(t_export **exp, char *var);
void		sort_export(t_export *exp);
int			lst_len(t_export *exp);
int			quit(int token);
char		*env_var_search(t_env *envv, char *to_find);
void		*print_or_get_env(t_env *envv, int token, int len);
int			modify_exp_var(t_export *exp, char *var);
int			is_only_n(char *s);
void		exit_check_utils(t_ast *ast);
int			modify_exp_var(t_export *exp, char *var);
int			is_only_n(char *s);
int			env_format_check(char *var);
int			check_if_exist_exp(t_export *exp, char *var);
int			cd_utils(char **arr);
void		add_node_cwd(t_cwd **cwdd, char *dirr);

#endif