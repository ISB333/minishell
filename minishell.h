/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:24:05 by adesille          #+#    #+#             */
/*   Updated: 2024/06/04 10:09:29 by isb3             ###   ########.fr       */
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

typedef struct s_data
{
	char	*cmd_path;
	char	**args;
	int		pipe;
	int		infile;
	int		outfile;

}	t_data;

char	*get_prompt();

	/// Lexing ///
char	**lexer(char *str);
int		is_sh_ope(char *s, int i, char token);
int		is_del(char c);
int		is_quotes(char *s, int i, char token);
int		closing_quotes_pos(char *s, int i);
int		is_dollar(char **arr, int i, char token);
int		get_dollar(char **arr);
size_t	count_rows(char *s);
int		add_space(char **s, int i, int k);
char	**splitter(char **array, char *s, size_t i);

	/// History ///
char	*gnhell(int fd);
int		append_new_history(char *rl);
int		add_previous_history();

#endif