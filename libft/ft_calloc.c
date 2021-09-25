/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:48:06 by yjama             #+#    #+#             */
/*   Updated: 2021/07/21 23:17:13 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*arr;
	unsigned int	bytes;

	bytes = count * size;
	arr = malloc(bytes);
	if (arr)
		ft_memset(arr, 0, bytes);
	return (arr);
}
