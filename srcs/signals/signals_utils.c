/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:29:06 by isb3              #+#    #+#             */
/*   Updated: 2024/09/29 12:56:36 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_heredoc(const t_action action)
{
	static int	in = FALSE;

	if (action == ENTRANCE)
		in = TRUE;
	else if (action == EXITING)
		in = FALSE;
	else if (action == INTERRUPTION)
		in = INTERRUPTION;
	return (in);
}

int	is_in_execution(const t_action action)
{
	static int	in = FALSE;

	if (action == ENTRANCE)
		in = TRUE;
	else if (action == EXITING)
		in = FALSE;
	else if (action == INTERRUPTION)
		in = INTERRUPTION;
	return (in);
}

int	is_in_open_pipe(const t_action action)
{
	static int	in = FALSE;

	if (action == ENTRANCE)
		in = TRUE;
	else if (action == EXITING)
		in = FALSE;
	else if (action == INTERRUPTION)
		in = INTERRUPTION;
	return (in);
}

void	ignore_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

int	return_(int code, int token)
{
	static int	exit_code = 0;

	if (token == ADD)
		exit_code = code;
	if (token == GET)
		return (exit_code);
	return (0);
}
