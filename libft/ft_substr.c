/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:49:12 by yjama             #+#    #+#             */
/*   Updated: 2021/08/28 19:46:47 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned int	k;
	char			*ptr;

	i = 0;
	k = 0;
	if (!s)
		return (0);
	ptr = malloc((len * sizeof(char)) + 1);
	if (!ptr)
		return (NULL);
	if (start <= ft_strlen(s))
	{
		while (i < start)
			i++;
		while (k < len && s[i] != '\0')
		{
			ptr[k] = s[i];
			k++;
			i++;
		}
		ptr[k] = '\0';
	}
	return (ptr);
}
