/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:54:09 by isb3              #+#    #+#             */
/*   Updated: 2024/09/04 16:22:54 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_dollar_hd(t_heredoc *hd, int j, int k)
{
	char	*env_var;
	char	*new_str;

	while (hd)
	{
		while (is_dollar(hd->s, '?'))
		{
			k = is_dollar(hd->s, 0);
			j = k;
			if (!hd->s[j + 1] || is_del(hd->s[j + 1]) || hd->s[j + 1] == '/')
				return ;
			while (hd->s[++j] && !is_del(hd->s[j]) && !is_dollar_del(hd->s[j]))
				;
			env_var = ft_substr(hd->s, k + 1, j - k - 1);
			if (!ft_strncmp(&hd->s[k], "$?", 2))
				new_str = ft_itoa(return_(0, GET));
			else
				new_str = get_envv(0, env_var, FIND);
			if (!new_str)
				new_str = ft_strdup("\0");
			hd->s = join_new_str(hd->s, new_str, j - k, 0);
		}
		hd = hd->next;
	}
}

void	add_node_hd(t_heredoc **hd, char *s)
{
	t_heredoc	*new_node;
	t_heredoc	*last_node;

	new_node = mem_manager(sizeof(t_heredoc), 0, 0, ALLOCATE);
	new_node->s = ft_strdup(s);
	new_node->next = NULL;
	if (!*hd)
		*hd = new_node;
	else
	{
		last_node = *hd;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

int	add_to_ast(t_ast **ast, t_heredoc *hd, int n)
{
	char	*path;
	int		fd;

	path = ft_strjoin(ft_strjoin(get_envv(0, "HOME", FIND), "/hd"), ft_itoa(n));
	fd = open(path, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (fd == -1)
		return (error(strerror(errno), path, 1));
	mem_manager(sizeof(int), 0, fd, SAVE_FD);
	while (hd)
	{
		ft_putstr_fd(hd->s, fd);
		ft_putstr_fd("\n", fd);
		hd = hd->next;
	}
	if ((*ast)->fd_in)
		mem_manager(0, 0, (*ast)->fd_in, CLOSE_FD);
	(*ast)->fd_in = open(path, O_RDONLY, 0644);
	if ((*ast)->fd_in == -1)
		return (error(strerror(errno), path, 1));
	mem_manager(sizeof(int), 0, (*ast)->fd_in, SAVE_FD);
	return (0);
}

int	parse_heredoc(t_ast **ast, char **tokens, int *i, int n)
{
	char		*line;
	int			pipefd[2];
	pid_t		pid;
	char		*del;
	t_heredoc	*hd;
	int			status;
	char		*buffer;

	hd = NULL;
	if (is_there_quotes_in_da_shit(tokens[*i + 1]))
		del = quotes_destroyer(tokens[*i + 1], 0, 0, 0);
	else
		del = ft_strdup(tokens[*i + 1]);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	is_in_heredoc(ENTRANCE);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (0);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	else if (pid == 0)
	{
		set_signals(1);
		// is_in_heredoc(ENTRANCE);
		close(pipefd[0]);
		mem_manager(0, 0, pipefd[1], SAVE_FD);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				printf("Warning: here-document at line 1 delimited by end-of-file (wanted `%s`)\n",
					del);
				mem_manager(0, 0, 0, CLEAR_MEMORY);
				exit(0);
			}
			if (strcmp(line, del) == 0)
			{
				// printf("aaaaaaaaaaa\n");
				free(line);
				mem_manager(0, 0, 0, CLEAR_MEMORY);
				printf("shiiiiiit\n");
				exit(0);
			}
			write(pipefd[1], line, strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		close(pipefd[1]);
		// printf("yeah\n");
		mem_manager(0, 0, 0, CLEAR_MEMORY);
		printf("shit\n");
		exit(0);
	}
	is_in_heredoc(FALSE);
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 130)
	{
		printf("\n");
		printf("lol\n");
		is_in_heredoc(INTERRUPTION);
		close(pipefd[0]);
		return_(130, ADD);
		// return(return_(130, ADD), 0);
	}
	else
	{
		buffer = gnhell(pipefd[0]);
		while (buffer)
		{
			buffer[ft_strlen(buffer) - 1] = '\0';
			add_node_hd(&hd, buffer);
			buffer = gnhell(pipefd[0]);
		}
		return_(0, ADD);
	}
	close(pipefd[0]);
	*i += 2;
	// set_signals(TRUE);
	get_dollar_hd(hd, 0, 0);
	add_to_ast(ast, hd, ++n);
	signal(SIGINT, SIG_DFL);
	return (0);
}

// int	parse_heredoc(t_ast **ast, char **tokens, int *i, int n)
// {
// 	char *s;
// 	char *del;
// 	t_heredoc *hd;
// 	int line;

// 	hd = NULL;
// 	if (is_there_quotes_in_da_shit(tokens[*i + 1]))
// 		del = quotes_destroyer(tokens[*i + 1], 0, 0, 0);
// 	else
// 		del = ft_substr(tokens[*i + 1], 0, ft_strlen(tokens[*i + 1]));
// 	is_in_heredoc(ENTRANCE);
// 	set_signals(FALSE);
// 	signal(SIGQUIT, SIG_IGN);
// 	while (1)
// 	{
// 		s = readline("> ");
// 		if (is_in_heredoc(CHECK_SIG) == INTERRUPTION)
// 		{
// 			(*ast)->error_code = return_(0, GET);
// 			break ;
// 		}
// 		if (!s)
// 		{
// 			error(ft_strjoin(ft_strjoin("warning: here-document at line ",
// 						ft_itoa(line)),
// 					ft_strjoin(ft_strjoin(" delimited by end-of-file (wanted '",
// 							del), "')")), 0, 0);
// 			break ;
// 		}
// 		if (!ft_strcmp(s, del))
// 			break ;
// 		add_node_hd(&hd, s);
// 		line++;
// 	}
// 	*i += 2;
// 	set_signals(TRUE);
// 	is_in_heredoc(EXITING);
// 	get_dollar_hd(hd, 0, 0);
// 	add_to_ast(ast, hd, ++n);
// 	return (0);
// }