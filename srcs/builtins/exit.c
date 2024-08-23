/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:50:24 by isb3              #+#    #+#             */
/*   Updated: 2024/08/23 17:37:03 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_check_utils(t_ast *ast);
static int	get_code(t_string s, long long *code);
static int	str_to_ll(t_string str, long long *save);

void	exit_check(t_ast *ast)
{
	long long	code;

	if (!ast)
		return ;
	if (!ast->next)
	{
		if (ast->cmd && ft_strcmp(*ast->cmd, "exit") == EQUAL)
		{
			if (ast->cmd[1])
			{
				if (ast->cmd[2])
					error("too many arguments", "exit", 1);
				if (get_code(ast->cmd[1], &code))
					return (mem_manager(0, 0, 0, CLEAR_MEMORY), exit(2));
				if (!ast->cmd[2])
					return (mem_manager(0, 0, 0, CLEAR_MEMORY), exit(code));
			}
			else
				return (mem_manager(0, 0, 0, CLEAR_MEMORY), exit(return_(0, GET)));
		}
	}
	else
		exit_check_utils(ast);
}

static void	exit_check_utils(t_ast *ast)
{
	long long	code;

	ast = get_node_at(ast, LAST);
	if (ast->cmd && ft_strcmp(*ast->cmd, "exit\0") == EQUAL)
	{
		if (!ast->cmd[1])
			return (mem_manager(0, 0, 0, CLEAR_MEMORY), exit(EXIT_SUCCESS));
		if (get_code(ast->cmd[1], &code))
			return (mem_manager(0, 0, 0, CLEAR_MEMORY), exit(2));
		return (mem_manager(0, 0, 0, CLEAR_MEMORY), exit(code));
	}
}

static int	get_code(t_string s, long long *code)
{
	if (!s || !code)
		return (0);
	if (str_to_ll(s, code) == EXIT_FAILURE)
		return (error("numeric argument required", s, 2));
	if (*code > 255)
		*code -= 256;
	else if (*code < 0)
		*code = 256 - -*code;
	return (0);
}

static int	str_to_ll(t_string str, long long *save)
{
	long long	result;
	int			sign;

	result = 0;
	sign = POSTIVE;
	if (!str || !save)
		return (EXIT_FAILURE);
	while (is_whitespace(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = NEGATIVE;
	if (*str)
	{
		while (is_numeric(*str)
			&& is_safe_operation(result, result * 10 + (*str - '0')))
			result = result * 10 + (*str++ - '0');
		if (!*str)
			return (*save = result * sign, EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
