/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_numeric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:54:48 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/23 13:57:09 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 📋 Description: checks if a character is a numeric digit (0-9).
 * 
 * @param c: the character to check.
 *
 * ⬅️ Return: t_bool, TRUE if the character is a digit, FALSE otherwise.
 */
t_bool	is_numeric(const char c)
{
	return (c >= '0' && c <= '9');
}
