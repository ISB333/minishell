/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:15:10 by aheitz            #+#    #+#             */
/*   Updated: 2024/09/04 16:13:18 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigquit(const int sig);
static void	handle_sigint(const int sig);

void	set_signals(int use_restart)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_handler = &handle_sigint;
	if (use_restart)
		sa_sigint.sa_flags = SA_RESTART;
	else
		sa_sigint.sa_flags = 0;
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
	printf("YEAH 1\n");
	if (is_in_heredoc(CHECK_STATUS))
	{
		printf("YEAH 2\n");
		mem_manager(0, 0, 0, CLEAR_MEMORY);
		exit(128+sig);
	}
	// else
	// {
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	// }
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

int	is_in_heredoc(const t_action action)
{
	static int 	in = FALSE;

	if (action == ENTRANCE)
		in = TRUE;
	else if (action == EXITING)
		in = FALSE;
	else if (action == INTERRUPTION)
		in = INTERRUPTION;
	return (in);
}
