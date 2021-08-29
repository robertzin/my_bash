/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:48:36 by yjama             #+#    #+#             */
/*   Updated: 2020/11/09 11:48:37 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*ptr_d;
	char		*ptr_dl;
	const char	*ptr_s;
	const char	*ptr_sl;

	ptr_d = dst;
	ptr_s = src;
	if (!dst && !src)
		return (NULL);
	if (ptr_d < ptr_s)
		while (len--)
			*ptr_d++ = *ptr_s++;
	else
	{
		ptr_sl = ptr_s + (len - 1);
		ptr_dl = ptr_d + (len - 1);
		while (len--)
			*ptr_dl-- = *ptr_sl--;
	}
	return (dst);
}
