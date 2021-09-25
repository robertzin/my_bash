/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:49:06 by yjama             #+#    #+#             */
/*   Updated: 2020/11/09 11:49:07 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	int			len;
	const char	*ptr;

	i = 0;
	ptr = NULL;
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] == (char)c)
			ptr = &s[i];
		i++;
	}
	if (s[i] == (char)c)
		ptr = &s[i];
	return ((char *)ptr);
}
