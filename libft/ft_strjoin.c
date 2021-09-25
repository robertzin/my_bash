/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:48:50 by yjama             #+#    #+#             */
/*   Updated: 2021/01/05 12:22:11 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		k;
	int		len;
	char	*ptr;

	i = 0;
	k = 0;
	if (!s1 || !s2)
		return (0);
	len = (ft_strlen(s1) + ft_strlen(s2));
	ptr = malloc((len * sizeof(char)) + 1);
	if (ptr)
	{
		while (s1[i] != '\0')
			ptr[k++] = s1[i++];
		i = 0;
		while (s2[i] != '\0')
			ptr[k++] = s2[i++];
		ptr[k] = '\0';
	}
	return (ptr);
}
