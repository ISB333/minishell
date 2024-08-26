/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:50:24 by isb3              #+#    #+#             */
/*   Updated: 2024/08/26 12:10:21 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoi_ll(const char *nptr)
{
	int			i;
	int			sign;
	long long	nbr;

	sign = 1;
	i = 0;
	nbr = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nbr = (nbr * 10) + ((nptr[i++]) - 48);
	return (nbr * sign);
}

int	format_check_utils(char *s, long long *code)
{
	int	token;

	token = 0;
	while (*s == '-' || *s == '+' || *s == '0')
	{
		token = 1;
		s++;
	}
	if (ft_strlen(s) > 19)
		return (error("numeric argument required", ft_strjoin("exit: ", s), 2));
	if (!token && ft_strcmp(s, "9223372036854775807") > 0)
		return (error("numeric argument required", ft_strjoin("exit: ", s), 2));
	else if (token && ft_strcmp(s, "9223372036854775808") > 0)
		return (error("numeric argument required", ft_strjoin("exit: ", s), 2));
	return (0);
}

int	format_check(char *s, long long *code)
{
	int	i;

	i = 0;
	while (is_del(*s))
		s++;
	if (!ft_strlen(s))
		return (error("numeric argument required", ft_strjoin("exit: ", s), 2));
	if ((s[i] == '-' || s[i] == '+') && s[i + 1])
		i++;
	while (s[i])
	{
		if ((s[i] >= '0' && s[i] <= '9'))
			i++;
		else
			return (error("numeric argument required", ft_strjoin("exit: ", s),
					2));
	}
	return (format_check_utils(s, code));
}

void	exitt(char **cmd)
{
	long long	code;

	printf("exit\n");
	if (cmd[1])
	{
		code = ft_atoi_ll(cmd[1]);
		if (format_check(cmd[1], &code))
			return (mem_manager(0, 0, 0, CLEAR_MEMORY), exit(2));
		if (!cmd[2])
			return (mem_manager(0, 0, 0, CLEAR_MEMORY), exit(code));
		else
			error("too many arguments", "exit", 1);
	}
	else
		return (mem_manager(0, 0, 0, CLEAR_MEMORY), exit(return_(0, GET)));
}
