/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:15:10 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/30 18:28:48 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigquit(const int sig);
static void	handle_sigint(const int sig);

void	set_signals(void)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_handler = &handle_sigint;
	sa_sigint.sa_flags = SA_RESTART;
	sigemptyset(&sa_sigint.sa_mask);
	if (sigaction(SIGINT, &sa_sigint, NULL))
		perror("sigaction");
	sa_sigquit.sa_handler = &handle_sigquit;
	sa_sigquit.sa_flags = SA_RESTART;
	sigemptyset(&sa_sigquit.sa_mask);
	if (sigaction(SIGQUIT, &sa_sigquit, NULL))
		perror("sigaction");
}

static void	handle_sigquit(const int sig)
{
	write(STDOUT_FILENO, "Quit\n", 6);
	return_(128 + sig, ADD);
}

static void	handle_sigint(const int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	if (is_in_heredoc(CHECK_STATUS))
	{
		is_in_heredoc(INTERRUPTION);
		rl_done = TRUE;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	if (sig && !is_in_execution(CHECK))
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return_(128 + sig, ADD);
}

t_bool	is_in_execution(const t_action action)
{
	static t_bool	active = FALSE;
	const t_bool	status = active;

	if (action == SET)
		active = TRUE;
	else if (action == RESET)
		active = FALSE;
	return (status);
}

t_bool	is_in_heredoc(const t_action action)
{
	static t_bool	in = FALSE;
	static t_bool	sig = FALSE;
	const t_bool	status = sig;

	if (action == ENTRANCE)
		in = TRUE;
	else if (action == EXITING)
	{
		in = FALSE;
		sig = FALSE;
	}
	else if (action == INTERRUPTION)
		sig = TRUE;
	if (action == CHECK_STATUS)
		return (in);
	return (status);
}
