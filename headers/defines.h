/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:40:59 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/19 17:48:39 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "minishell.h"

// 🎨 Color Codes ---------------------------------------------------------- 🎨 */

# define RED		"\033[0;31m"
# define BLUE		"\033[0;34m"
# define DEF		"\033[0m"

// 🔹 Builtin Command Identifiers ------------------------------------------ 🔹 */

# define CD			301
# define PWD		302
# define EXPORT		303
# define UNSET		304
# define ENV		305
# define ECH		306
# define EXIT		307

// 💾 File Descriptor Management ------------------------------------------- 💾 */

# define DUP_STD	320
# define CLOSE_STD	321

// 🗂️ Utility Operations ------------------------------------------------- 🗂️ */

# define INIT		330
# define ADD		331
# define PRINT		332
# define MODIF		333
# define FIND		334
# define GET		335
# define UPDATE		336
# define HOME		337

#endif