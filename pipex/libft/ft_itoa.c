/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:11:00 by adesille          #+#    #+#             */
/*   Updated: 2023/11/08 12:24:38 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digitcount(int n)
{
	int	temp;
	int	digitlen;

	temp = n;
	digitlen = 1;
	if (temp < 0)
		temp = -temp;
	while (temp >= 10)
	{
		temp /= 10;
		digitlen++;
	}
	return (digitlen);
}

static char	*ft_putnbr_pos(int n, int digitlen)
{
	int		end;
	int		trueend;
	char	*numbers;

	numbers = malloc(digitlen + 1);
	if (numbers == NULL)
		return (NULL);
	end = digitlen - 1;
	trueend = digitlen;
	while (end >= 0)
	{
		numbers[end] = n % 10 + '0';
		n /= 10;
		end--;
	}
	numbers[trueend] = '\0';
	return (numbers);
}

static char	*ft_putnbr_neg(int n, int digitlen)
{
	int		end;
	int		trueend;
	char	*numbers;

	numbers = malloc(digitlen + 1);
	if (numbers == NULL)
		return (NULL);
	end = digitlen - 1;
	trueend = digitlen;
	numbers[0] = '-';
	n = -n;
	while (end > 0)
	{
		numbers[end] = n % 10 + '0';
		n /= 10;
		end--;
	}
	numbers[trueend] = '\0';
	return (numbers);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		digitlen;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	digitlen = digitcount(n);
	if (n < 0)
		result = ft_putnbr_neg(n, digitlen + 1);
	else
		result = ft_putnbr_pos(n, digitlen);
	return (result);
}
