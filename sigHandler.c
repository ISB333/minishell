/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigHandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:51:58 by nkieffer          #+#    #+#             */
/*   Updated: 2024/06/18 10:25:00 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	catchBackslash(void)
{
	struct sigaction	*action;

	action = malloc(sizeof(struct sigaction));
	action->sa_handler = SIG_IGN;
	action->sa_flags = 0;
	sigemptyset(&action->sa_mask);

	sigaction(SIGQUIT, action, NULL);
	free(action);
	return (1);
}

// static int	ifCtrlC(/*char *env[]*/)
// {
// 	// char	*rl;
// 	// char	*prompt;

// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	ft_do_all();
// 	// prompt = get_prompt();
// 	// if (!prompt)
// 	// 	return (printf("prompt error\n"), 1);
// 	return (1);
// }

int	catchC()
{
	struct sigaction	*action;

	action = malloc(sizeof(struct sigaction));
	// action->sa_handler = ifCtrlC;
	action->sa_flags = 0;
	sigemptyset(&action->sa_mask);

	sigaction(SIGINT, action, NULL);
	free(action);
	return (1);
}