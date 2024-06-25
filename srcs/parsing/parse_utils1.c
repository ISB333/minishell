/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:10:33 by adesille          #+#    #+#             */
/*   Updated: 2024/06/25 07:45:58 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_lst(t_ast **ast)
{
	(*ast)->cmd = NULL;
	(*ast)->cmd_path = NULL;
	(*ast)->heredoc = NULL;
	(*ast)->fd_in = 0;
	(*ast)->fd_out = 0;
	(*ast)->fd_append = 0;
	(*ast)->pipe = 0;
}

t_ast	*return_tail(t_ast *ast)
{
	if (!ast->next)
		return (ast);
	while (ast && ast->next)
		ast = ast->next;
	return (ast);
}

char	**extract_path(void)
{
	char	**path;
	char	*trimm_path;

	trimm_path = getenv("PATH");
	if (!trimm_path)
		return (NULL);
	path = ft_split(trimm_path, ':');
	if (!path)
		return (NULL);
	return (path);
}

int	cmd_path_init(t_ast *ast)
{
	char	**path;
	char	*cmd;
	char	*test_path;
	int		i;

	path = extract_path();
	if (!path)
		return (printf("path not existing\n"), 1);
	i = -1;
	cmd = ft_strjoin("/", ast->cmd[0]);
	if (!cmd)
		return (1);
	while (path[++i])
	{
		test_path = ft_strjoin(path[i], cmd);
		if (!access(test_path, R_OK))
		{
			ast->cmd_path = test_path;
			return (0);
		}
	}
	return (printf("%s: notexisting\n", ast->cmd[0]), 1);
}
