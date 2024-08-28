/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_safe_operation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:47:06 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/28 15:31:53 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 📋 Description: checks if a long long operation resulted in an overflow.
 *
 * @param prev: the value before the operation.
 * @param curr: the value after the operation.
 *
 * ⬅️ Return: t_bool, TRUE if the signs are identical, FALSE otherwise.
 */
t_bool	is_safe_operation(long long prev, long long curr)
{
	return ((!prev) || (prev > 0 && curr > 0) || (prev < 0 && curr < 0));
}
