/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_overflow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:49:09 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/23 16:30:14 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 📋 Description: checks if a long long operation resulted in an overflow.
 * 
 * @param previous: the value before the operation.
 * @param current: the value after the operation.
 *
 * ⬅️ Return: t_bool, TRUE if the signs are identical, FALSE otherwise.
 */
t_bool	is_safe_operation(long long previous, long long current)
{
	return ((previous > 0 && current > 0) || (previous < 0 && current < 0));
}
