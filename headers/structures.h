/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:58:14 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/21 17:35:30 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minishell.h"

// 🌳 Abstract Syntax Tree (AST) ------------------------------------------- 🌳 */

typedef struct s_ast
{
	struct s_ast			*next;
	t_string				*cmd;
	t_string				cmd_path;
	int						fd_in;
	int						fd_out;
	int						pipe_fd[2];
	pid_t					pid;
	t_string				error;
	int						error_code;
}							t_ast;

// 🏗️ Current Working Directory (CWD) ------------------------------------ 🏗️ */

typedef struct s_cwd
{
	struct s_cwd			*next;
	t_string				dir;
}							t_cwd;

// 🌱 Environment Variables ------------------------------------------------ 🌱 */

typedef struct s_env
{
	struct s_env			*next;
	t_string				var;
}							t_env;

// 📦 Exported Variables --------------------------------------------------- 📦 */

typedef struct s_export
{
	struct s_export			*next;
	t_string				var;
}							t_export;

// 📝 Heredoc Handling ----------------------------------------------------- 📝 */

typedef struct s_heredoc
{
	struct s_heredoc		*next;
	t_string				s;
}							t_heredoc;

// 🏠 Home Directory ------------------------------------------------------- 🏠 */

typedef struct s_home
{
	struct s_home			*next;
	t_string				dir;
	t_string				path;
}							t_home;

// 🧠 Memory Management ---------------------------------------------------- 🧠 */

typedef struct s_memman
{
	struct s_memman			*next;
	void					*ptr;
	t_ptr_type				type;
}							t_memman;

// 💻 Shell Prompt --------------------------------------------------------- 💻 */

typedef struct s_prompt
{
	t_string				name;
	t_string				pos;
	t_string				curr_dir;
	t_string				root_dir;
}							t_prompt;

// 🔀 String Splitting ----------------------------------------------------- 🔀 */

typedef struct s_split
{
	int						i;
	int						k;
	size_t					j;
	int						token;
}							t_split;

// 🧩 Linked List Structure ------------------------------------------------ 🧩 */

typedef struct s_linked_list
{
	struct s_linked_list	*next;
}							t_linked_list;

#endif