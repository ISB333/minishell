/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_numeric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:44:57 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/26 16:26:52 by aheitz           ###   ########.fr       */
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
