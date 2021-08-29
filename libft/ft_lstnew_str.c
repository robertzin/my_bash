/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 12:35:28 by slynn-ev          #+#    #+#             */
/*   Updated: 2021/07/19 12:17:53 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_str(char *content)
{
	t_list	*tmp;
	int		i;
	char	*arr;

	tmp = (t_list *)malloc(sizeof(t_list));
	arr = malloc(sizeof(char) * ft_strlen(content) + 1);
	if (!tmp || !arr)
		return (NULL);
	if (content == NULL)
	{
		tmp->content = NULL;
		tmp->content_size = 0;
		tmp->next = NULL;
		return (tmp);
	}
	i = 0;
	while (content[i])
	{
		arr[i] = content[i];
		i++;
	}
	arr[i] = '\0';
	tmp->content = (void *)arr;
	tmp->next = NULL;
	return (tmp);
}
