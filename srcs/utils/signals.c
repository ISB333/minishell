/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 07:39:30 by isb3              #+#    #+#             */
/*   Updated: 2024/07/13 05:32:12 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_(int code, int token)
{
	static int	exit_code = 0;

	if (token == ADD)
		exit_code = code;
	if (token == GET)
		return (exit_code);
	return (0);
}

void	handle_sig_c(int signal)
{
	if (signal == SIGINT)
	{
		printf(BLUE "\n%s" DEF, get_prompt());
		fflush(stdout);
	}
}

void	handle_sig_q(int signal)
{
	(void)signal;
	return ;
}

void	signals_handler(void)
{
	struct sigaction	sa_c;
	struct sigaction	sa_q;

	sa_c.sa_handler = &handle_sig_c;
	sa_c.sa_flags = SA_RESTART;
	sigemptyset(&sa_c.sa_mask);
	if (sigaction(SIGINT, &sa_c, NULL))
		perror("sigaction");
	sa_q.sa_handler = &handle_sig_q;
	sa_q.sa_flags = SA_RESTART;
	sigemptyset(&sa_q.sa_mask);
	if (sigaction(SIGQUIT, &sa_q, NULL))
		perror("sigaction");
}
