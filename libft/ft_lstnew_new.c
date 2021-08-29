/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 10:37:32 by slynn-ev          #+#    #+#             */
/*   Updated: 2021/07/20 13:52:16 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memdup(void const *content, size_t n)
{
	unsigned long	i;
	char			*b;
	char			*a;

	a = (char *)content;
	b = (char *)malloc(sizeof(char) * n);
	if (!b)
		return (NULL);
	i = 0;
	while (i < n)
	{
		b[i] = a[i];
		i++;
	}
	return ((void *)b);
}

t_list	*ft_lstnew_new(void const *content, size_t content_size)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		return (NULL);
	if (content == NULL)
	{
		tmp->content = NULL;
		tmp->content_size = 0;
		tmp->next = NULL;
		return (tmp);
	}
	tmp->content = ft_memdup(content, content_size);
	tmp->content_size = content_size;
	tmp->next = NULL;
	return (tmp);
}
