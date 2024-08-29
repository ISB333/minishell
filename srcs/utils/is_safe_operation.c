/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_safe_operation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:47:06 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/29 13:50:13 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 🔒 Static function prototypes for internal use -------------------------- 🔒 */

static t_bool	are_same_sign(const long long x, const long long y);
static t_bool	is_inferior(const long long x, const long long y);

/**
 * 📋 Description: checks if a long long operation did not result in an overflow.
 *
 * @param previous: the value before the operation.
 * @param current: the value after the operation.
 *
 * ⬅️ Return: t_bool, TRUE if did not result in an overflow, FALSE otherwise.
 */
t_bool	is_safe_operation(const long long prev, const long long cur)
{
	return (!prev || (are_same_sign(prev, cur) && is_inferior(prev, cur)));
}

/**
 * 📋 Description: checks if two values have the same sign.
 *
 * @param x: the first value.
 * @param y: the second value.
 *
 * ⬅️ Return: t_bool, TRUE if the signs are identical, FALSE otherwise.
 */
static t_bool	are_same_sign(const long long x, const long long y)
{
	return ((x > 0 && y > 0) || (x < 0 && y < 0));
}

/**
 * 📋 Description: checks if the current value is close to the previous one.
 *
 * @param previous: the first value.
 * @param current: the second value.
 *
 * ⬅️ Return: t_bool, TRUE if value is consistent with sign, FALSE otherwise.
 */
static t_bool	is_inferior(const long long x, const long long y)
{
	return ((x > 0 && y > x) || (x < 0 && y < x));
}
