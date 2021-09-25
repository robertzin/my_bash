/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:20:11 by yjama             #+#    #+#             */
/*   Updated: 2021/07/19 12:15:55 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*ptr;

	ptr = *lst;
	while (ptr)
	{
		tmp = ptr->next;
		if (del)
			(*del)(ptr->content);
		free(ptr);
		ptr = tmp;
	}
	*lst = NULL;
}
