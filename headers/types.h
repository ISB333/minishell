/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:00:59 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/28 16:33:43 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "minishell.h"

// 🔤 String Type Definition ----------------------------------------------- 🔤 */

typedef char	*t_string;

// 🖧 File Descriptor Type Definitions ------------------------------------- 🖧 */

typedef int		t_fd;
typedef int		t_pipe_fd[2];

#endif