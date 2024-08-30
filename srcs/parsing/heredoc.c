/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:54:09 by isb3              #+#    #+#             */
/*   Updated: 2024/08/30 07:44:46 by aheitz           ###   ########.fr       */
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
			if (!hd->s[j + 1] || is_del(hd->s[j + 1]))
				return ;
			while (hd->s[j] && !is_del(hd->s[j]) && !is_dollar_del(hd->s[j]))
				j++;
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
	char		*s;
	char		*del;
	t_heredoc	*hd;
	char		*ss;

	hd = NULL;
	if (is_there_quotes_in_da_shit(tokens[*i + 1]))
		del = quotes_destroyer(tokens[*i + 1], 0, 0, 0);
	else
		del = ft_substr(tokens[*i + 1], 0, ft_strlen(tokens[*i + 1]));
	in_heredoc(TRUE);
	while (1)
	{
		s = readline("> ");
		if (sig_in_heredoc(FALSE))
			return (-1);
		if (!s)
			break ;
		ss = ft_strdup(s);
		free(s);
		if (!ft_strcmp(ss, del))
			break ;
		add_node_hd(&hd, ss);
	}
	in_heredoc(TRUE);
	get_dollar_hd(hd, 0, 0);
	add_to_ast(ast, hd, ++n);
	*i += 2;
	return (0);
}
