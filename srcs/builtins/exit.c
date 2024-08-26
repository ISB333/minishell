/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:50:24 by isb3              #+#    #+#             */
/*   Updated: 2024/08/26 16:26:21 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 🔒 Static function prototypes for internal use -------------------------- 🔒 */

static int	str_to_ll(t_string str, long long *save);

/**
 * 📋 Description: exits the program according to the code provided.
 * 
 * @param cmd: the array of strings containing the exit command and arguments.
 *
 * ⬅️ Return: nothing.
 */
void	exitt(const t_string *cmd)
{
	long long	code;

	printf("exit\n");
	if (cmd[1])
	{
		if (str_to_ll(cmd[1], &code) == EXIT_FAILURE)
			return (error("numeric argument required",
					ft_strjoin("exit: ", cmd[1]), 2),
				mem_manager(0, NULL, 0, CLEAR_MEMORY), exit(2));
		if (!cmd[2])
			return (mem_manager(0, 0, 0, CLEAR_MEMORY), exit(code));
		else
			error("too many arguments", "exit", 1);
	}
	else
		return (mem_manager(0, 0, 0, CLEAR_MEMORY), exit(return_(0, GET)));
}

/**
 * 📋 Description: converts a string to a long long and stores it by pointer.
 * 
 * @param str: the string to convert.
 * @param save: the pointer to store the converted number.
 *
 * ⬅️ Return: int, EXIT_SUCCESS if successful, otherwise EXIT_FAILURE.
 */
static int	str_to_ll(t_string str, long long *save)
{
	long long	result;
	int			sign;

	result = 0;
	sign = POSITIVE;
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
