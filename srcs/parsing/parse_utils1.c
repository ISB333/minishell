/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:10:33 by adesille          #+#    #+#             */
/*   Updated: 2024/06/27 13:37:13 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_lst(t_ast **ast)
{
	(*ast)->cmd = NULL;
	(*ast)->cmd_path = NULL;
	(*ast)->error = NULL;
	(*ast)->fd_in = 0;
	(*ast)->fd_out = 0;
	(*ast)->append = 0;
	(*ast)->infile = 0;
	(*ast)->outfile = 0;
	(*ast)->pipe = 0;
	(*ast)->new_line = 0;
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
	return (path);
}

int	cmd_path_init(t_ast *ast)
{
	char	**path;
	char	*cmd;
	char	*test_path;
	int		i;

	if (ast->cmd == NULL)
		return (0);
	path = extract_path();
	if (!path)
		return (printf("minihell: path not existing\n"), 1);
	i = -1;
	cmd = ft_strjoin("/", ast->cmd[0]);
	while (path[++i])
	{
		test_path = ft_strjoin(path[i], cmd);
		if (!access(test_path, R_OK))
		{
			ast->cmd_path = test_path;
			return (0);
		}
	}
	return (printf("%s: command not found\n", ast->cmd[0]), 1);
}
