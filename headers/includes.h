/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:23:04 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/19 17:50:04 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include "minishell.h"

// 🐚 Project-specific Header ---------------------------------------------- 🐚 */
# include "./../libft/libft.h"

// 🌐 Standard Library Headers --------------------------------------------- 🌐 */
# include <errno.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// 🗄️ System and POSIX Headers ------------------------------------------- 🗄️ */
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>

// 🔧 Terminal and Input Handling ------------------------------------------ 🔧 */
# include <curses.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <termcap.h>
# include <termios.h>

#endif