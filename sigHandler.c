/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigHandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:51:58 by nkieffer          #+#    #+#             */
/*   Updated: 2024/05/30 16:18:32 by nkieffer         ###   ########.fr       */
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

static int	ifCtrlC(/*char *env[]*/)
{
	// char	*rl;
	// char	*prompt;

	write(1, "\n", 1);
	rl_on_new_line();
	// prompt = get_prompt(/*env*/);
	// if (!prompt)
	// 	return (printf("prompt error\n"), 1);
	// rl = readline(prompt);
	// add_history(rl);
	// // printf("%s\n", rl);
	// lexer(rl);
	// // parser();
	// free(prompt);
	// if (!ft_strcmp(rl, "exit\0"))
	// 	return (free(rl), exit(EXIT_SUCCESS), 0);
	// free(rl);
	return (1);
}

int	catchC()
{
	struct sigaction	*action;

	action = malloc(sizeof(struct sigaction));
	action->sa_handler = ifCtrlC;
	action->sa_flags = 0;
	sigemptyset(&action->sa_mask);

	sigaction(SIGINT, action, NULL);
	free(action);
	return (1);
}