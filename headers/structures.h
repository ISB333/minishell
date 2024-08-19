/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:58:14 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/19 17:59:07 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minishell.h"

// 🌳 Abstract Syntax Tree (AST) ------------------------------------------- 🌳 */

typedef struct s_ast
{
	t_string			*cmd;
	t_string			cmd_path;
	int					fd_in;
	int					fd_out;
	int					pipe_fd[2];
	pid_t				pid;
	t_string			error;
	int					error_code;
	struct s_ast		*next;
}						t_ast;

// 🏗️ Current Working Directory (CWD) ------------------------------------ 🏗️ */

typedef struct s_cwd
{
	t_string			dir;
	struct s_cwd		*next;
}						t_cwd;

// 🌱 Environment Variables ------------------------------------------------ 🌱 */

typedef struct s_env
{
	t_string			var;
	struct s_env		*next;
}						t_env;

// 📦 Exported Variables --------------------------------------------------- 📦 */

typedef struct s_export
{
	t_string			var;
	struct s_export		*next;
}						t_export;

// 📝 Heredoc Handling ----------------------------------------------------- 📝 */

typedef struct s_heredoc
{
	t_string			s;
	struct s_heredoc	*next;
}						t_heredoc;

// 🏠 Home Directory ------------------------------------------------------- 🏠 */

typedef struct s_home
{
	t_string			dir;
	t_string			path;
	struct s_home		*next;
}						t_home;

// 🧠 Memory Management ---------------------------------------------------- 🧠 */

typedef struct s_memman
{
	void				*ptr;
	t_ptr_type			type;
	struct s_memman		*next;
}						t_memman;

// 💻 Shell Prompt --------------------------------------------------------- 💻 */

typedef struct s_prompt
{
	t_string			name;
	t_string			pos;
	t_string			curr_dir;
	t_string			root_dir;
}						t_prompt;

// 🔀 String Splitting ----------------------------------------------------- 🔀 */

typedef struct s_split
{
	int					i;
	int					k;
	size_t				j;
	int					token;
}						t_split;

#endif