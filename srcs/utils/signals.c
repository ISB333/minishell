/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 07:39:30 by isb3              #+#    #+#             */
/*   Updated: 2024/07/13 05:23:02 by isb3             ###   ########.fr       */
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

struct sigaction	g_sa;

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
	g_sa.sa_handler = &handle_sig_c;
	g_sa.sa_flags = SA_RESTART;
	sigemptyset(&g_sa.sa_mask);
	if (sigaction(SIGINT, &g_sa, NULL))
		perror("sigaction");
	g_sa.sa_handler = &handle_sig_q;
	g_sa.sa_flags = SA_RESTART;
	sigemptyset(&g_sa.sa_mask);
	if (sigaction(SIGQUIT, &g_sa, NULL))
		perror("sigaction");
}
