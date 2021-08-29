/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:47:35 by yjama             #+#    #+#             */
/*   Updated: 2021/07/21 23:19:49 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *input)
{
	long	result;
	int		pos;

	result = 0;
	pos = 1;
	while (*input == '\n' || *input == '\t' || *input == '\v'
		|| *input == '\r' || *input == '\f' || *input == ' ')
		input++;
	if (*input == '-' || *input == '+')
	{
		if (*input == '-')
			pos *= -1;
		input++;
	}
	while (*input >= '0' && *input <= '9')
	{
		result = result * 10 + (*input - '0');
		input++;
		if (result > 2147483648 && pos == -1)
			return (0);
		else if (result > 2147483647 && pos == 1)
			return (-1);
	}
	return (result * pos);
}
