/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_whitespace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:45:43 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/26 16:27:03 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 📋 Description: checks if a character is a POSIX whitespace character.
 * 
 * @param c: the character to check.
 *
 * ⬅️ Return: t_bool, TRUE if the character is a whitespace, FALSE otherwise.
 */
t_bool	is_whitespace(const char c)
{
	return (c == SPACE || (c >= TAB && c <= CARRIAGE_RETURN));
}
