/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharmund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:49:28 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/16 20:49:30 by oharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_num(char *val, char *num)
{
	char	*s;

	s = NULL;
	*val = '\0';
	val = val - 6;
	s = ft_strdup(val);
	free(val);
	val = ft_strjoin(s, num);
	free(s);
}

void	ft_copy_num(char *val, char *num, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		val[i] = num[i];
		i++;
	}
}

void	ft_inc_shlvl(t_base *b)
{
	int		i;
	char	*val;
	char	*num;
	int		len;

	i = 0;
	val = NULL;
	val = ft_getenv("SHLVL", b->envc);
	len = ft_strlen(val);
	i = ft_atoi(val);
	i++;
	num = ft_itoa(i);
	len = len - ft_strlen(num);
	if (len != 0)
		ft_add_num(val, num);
	else
		ft_copy_num(val, num, ft_strlen(val));
	free(num);
}
