/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:55:21 by adesille          #+#    #+#             */
/*   Updated: 2024/05/22 13:33:00 by nkieffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	1. Heredoc
	2. Pipex
	3. Parsing
	4. Error_management
	5. Execute
*/

int main()
{
	char	*prompt;
	prompt = "\0";
	while (ft_strncmp(prompt, "exit\0", 5) != 0)
	{
		prompt = readline("Prompt > ");
		printf("%s\n", prompt);
	}
	printf("%zu\n", ft_strlen("abcd"));
	return (0);
}