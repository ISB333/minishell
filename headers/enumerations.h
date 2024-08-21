/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enumerations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:40:15 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/20 16:06:36 by aheitz           ###   ########.fr       */
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

#endif