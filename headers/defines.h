/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:40:59 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/28 16:32:20 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "minishell.h"

// 🎨 Color Codes ---------------------------------------------------------- 🎨 */

# define RED				"\033[0;31m"
# define BLUE				"\033[0;34m"
# define DEF				"\033[0m"

// 🔹 Builtin Command Identifiers ------------------------------------------ 🔹 */

# define CD					301
# define PWD				302
# define EXPORT				303
# define UNSET				304
# define ENV				305
# define ECH				306
# define EXIT				307

// 💾 File Descriptor Management ------------------------------------------- 💾 */

# define DUP_STD			320
# define CLOSE_STD			321

// 🗂️ Utility Operations ------------------------------------------------- 🗂️ */

# define INIT				330
# define ADD				331
# define PRINT				332
# define MODIF				333
# define FIND				334
# define GET				335
# define UPDATE				336
# define HOME				337

// 🌐 Memory Manager ------------------------------------------------- 🌐 */

# define ALLOCATE			350
# define SAVE_FD			351
# define CLOSE_FD			352
# define KILL_ALL_FD		353
# define FREE				354
# define CLEAR_MEMORY		355

// 🔗 Symbolic values ------------------------------------------------------ 🔗 */

# define CHILD				0
# define LAST				-2
# define INVALID			-1
# define NEGATIVE			-1
# define PENULTIMATE		-1
# define EQUAL				0
# define FAILURE			0
# define READ				0
# define SUCCESS			1
# define POSITIVE			1
# define WRITE				1

// 🎛️ Control characters ------------------------------------------------- 🎛️ */

# define CARRIAGE_RETURN	'\r'

#endif