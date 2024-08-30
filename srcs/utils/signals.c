/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 07:39:30 by isb3              #+#    #+#             */
/*   Updated: 2024/08/30 07:49:18 by aheitz           ###   ########.fr       */
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

t_bool	in_heredoc(const t_bool change)
{
	static t_bool	in_heredoc = FALSE;

	if (change)
		in_heredoc = !in_heredoc;
	return (in_heredoc);
}

t_bool	sig_in_heredoc(const t_bool change)
{
	static t_bool	encountered_sig = FALSE;

	if (change)
		encountered_sig = !encountered_sig;
	return (encountered_sig);
}

void	handle_sig_c(int signal)
{
	static t_bool	command_in_execution = TRUE;

	if (in_heredoc(FALSE))
		sig_in_heredoc(TRUE);
	if (!signal)
	{
		if (!command_in_execution)
			command_in_execution = TRUE;
		else
			command_in_execution = FALSE;
		return ;
	}
	return_(128 + SIGINT, ADD);
	write(STDOUT_FILENO, "\n", 1);
	if (command_in_execution && !in_heredoc(FALSE))
		return ;
	else if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sig_q(int signal)
{
	if (in_heredoc(FALSE))	//! BOF BOF
		return ;			//! PAS TRES UTILE
	if (signal)
		write(STDOUT_FILENO, "Quit\n", 6);
	return_(128 + SIGQUIT, ADD);
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
