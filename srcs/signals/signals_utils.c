/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:29:06 by isb3              #+#    #+#             */
/*   Updated: 2024/09/06 13:29:13 by isb3             ###   ########lyon.fr   */
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
