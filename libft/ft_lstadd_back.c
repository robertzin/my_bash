/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:15:51 by yjama             #+#    #+#             */
/*   Updated: 2021/07/19 09:54:52 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (lst && new)
	{
		ptr = (*lst);
		if (ptr == NULL)
		{
			(*lst) = new;
			new->next = NULL;
		}
		else
		{
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = new;
			new->next = NULL;
		}
	}
}
