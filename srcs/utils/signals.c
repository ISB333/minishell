/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 07:39:30 by isb3              #+#    #+#             */
/*   Updated: 2024/08/30 16:25:46 by aheitz           ###   ########.fr       */
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
