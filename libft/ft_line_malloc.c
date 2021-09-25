/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 20:01:26 by yjama             #+#    #+#             */
/*   Updated: 2021/09/25 15:52:24 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_line_malloc(size_t count, size_t size)
{
	size_t			a;
	unsigned char	*b;

	a = (count * size);
	b = malloc(a + 1);
	if (!b)
		return (NULL);
	b[a] = '\0';
	return (b);
}
