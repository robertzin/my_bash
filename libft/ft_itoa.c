/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:11:38 by yjama             #+#    #+#             */
/*   Updated: 2021/07/19 12:16:12 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	int	i;

	i = 0;
	if (n < 0 || n == 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_to_string(char *input, int n, int size)
{
	if (n < 0)
	{
		input[0] = '-';
		n *= -1;
	}
	if (n == 0)
		input[0] = '0';
	input[size] = '\0';
	while (n != 0)
	{
		input[--size] = (n % 10) + '0';
		n /= 10;
	}
	return (input);
}

char	*ft_itoa(int n)
{
	int		digits;
	char	*number;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	digits = ft_count_digits(n);
	number = malloc((digits + 1) * sizeof(char));
	if (!number)
		return (0);
	number = ft_to_string(number, n, digits);
	return (number);
}
