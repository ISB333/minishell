/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enumerations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:40:15 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/30 16:27:34 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMERATIONS_H
# define ENUMERATIONS_H

# include "minishell.h"

// 📊 Pointer Types -------------------------------------------------------- 📊 */

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

// 🔢 Boolean values ------------------------------------------------------- 🔢 */

typedef enum e_types
{
	FD,
	NONE
}	t_ptr_type;

typedef enum e_action
{
	SET,
	RESET,
	CHECK,
	ENTRANCE,
	EXITING,
	INTERRUPTION,
	CHECK_STATUS,
	CHECK_SIG
}	t_action;

#endif