/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 07:41:47 by adesille          #+#    #+#             */
/*   Updated: 2024/08/27 16:15:05 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 📋 Description: executes the echo command, printing to terminal output.
 * 
 * @param args: the arguments passed with the echo command.
 *
 * ⬅️ Return: nothing.
 */
void	echoo(t_string *args)
{
	t_bool	suppress_newline;

	if (!args)
		return ;
	suppress_newline = FALSE;
	while (*++args && ft_strncmp(*args, "-n", 2) == EQUAL)
	{
		if (is_only_n(*args))
			suppress_newline = TRUE;
		else
			break ;
	}
	while (*args)
	{
		printf("%s", *args);
		if (*++args)
			printf(" ");
	}
	if (!suppress_newline)
		printf("\n");
}

/**
 * 📋 Description: prints the current working directory to terminal output.
 *
 * ⬅️ Return: nothing.
 */
void	pwdd(void)
{
	const t_string	cwd = get_cwdd(NULL, NULL, GET);

	if (cwd)
		printf("%s\n", cwd);
}

/**
 * 📋 Description: changes the current directory based on the provided path.
 * 
 * @param args: the arguments passed with the cd command.
 *
 * ⬅️ Return: int, an integer code indicating success or error.
 */
int	cd(t_string *args)
{
	struct stat	path_stat;
	t_string	directory;

	if ((args[1] && args[2]))
		return (error("too many arguments", "cd", 1));
	if (args[1] && ft_strchr(args[1], '/'))
		directory = ft_substr(args[1], 0, ft_strlen(args[1])
				- ft_strlen(ft_strchr(args[1], '/')));
	else if (args[1])
		directory = ft_strdup(args[1]);
	if (!stat(directory, &path_stat) && !S_ISDIR(path_stat.st_mode))
		return (error("Not a directory", ft_strjoin("cd: ", args[1]), 1));
	if (!args[1] || ft_strcmp(args[1], "~") == EQUAL)
	{
		if (chdir(get_cwdd(NULL, NULL, HOME)))
			return (-1);
		exportt(NULL, ft_strjoin("OLDPWD=", get_cwdd(NULL, NULL, GET)), ADD);
		get_cwdd(NULL, args[1], UPDATE);
		exportt(NULL, ft_strjoin("PWD=", get_cwdd(NULL, NULL, GET)), ADD);
	}
	else
		return (cd_utils(args));
	return (0);
}

/**
 * 📋 Description: directs the command to the appropriate builtin function.
 * 
 * @param cmd_node: the command structure containing the command and arguments.
 * @param builtin_command: the command identifier indicating function to call.
 *
 * ⬅️ Return: nothing.
 */
void	call_builtins(t_ast *cmd_node, const int builtin_command)
{
	if (!cmd_node || !cmd_node->cmd || !*cmd_node->cmd)
		return ;
	if (builtin_command == CD)
		cd(cmd_node->cmd);
	else if (builtin_command == PWD)
		pwdd();
	else if (builtin_command == ECH)
		echoo(cmd_node->cmd);
	else if (builtin_command == EXPORT)
	{
		if (!cmd_node->cmd[1])
			exportt(NULL, NULL, PRINT);
		else
			while (*cmd_node->cmd)
				exportt(NULL, *++cmd_node->cmd, ADD);
	}
	else if (builtin_command == ENV)
		get_envv(NULL, NULL, PRINT);
	else if (builtin_command == EXIT)
		exitt(cmd_node->cmd);
	while (builtin_command == UNSET && *cmd_node->cmd)
	{
		exportt(NULL, *++cmd_node->cmd, UNSET);
		get_envv(NULL, *cmd_node->cmd, UNSET);
	}
}

/**
 * 📋 Description: determines if a command is a shell builtin.
 * 
 * @param ast: the command structure to check.
 *
 * ⬅️ Return: int, the command identifier if it's a builtin, otherwise 0.
 */
int	is_builtin(t_ast *ast)
{
	static const t_string	builtins[]
		= {"cd", "pwd", "export", "unset", "env", "echo", "exit"};
	static const int		builtin_commands[]
		= {CD, PWD, EXPORT, UNSET, ENV, ECH, EXIT};
	size_t					i;

	if (ast && ast->cmd && *ast->cmd)
	{
		i = 0;
		while (i < sizeof(builtins) / sizeof(*builtins))
		{
			if (ft_strcmp(*ast->cmd, builtins[i]) == EQUAL)
				return (builtin_commands[i]);
			++i;
		}
	}
	return (0);
}
