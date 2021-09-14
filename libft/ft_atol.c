/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 10:09:03 by slynn-ev          #+#    #+#             */
/*   Updated: 2021/07/19 14:29:41 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *s)
{
	long	p;
	int		sign;

	sign = 1;
	p = 0;
	while (*s == '\n' || *s == '\t' || *s == '\v'
		|| *s == '\r' || *s == '\f' || *s == ' ')
		s++;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	while (ft_isdigit(*s))
	{
		p = p * 10 + *s - '0';
		s++;
	}
	return (p * sign);
}