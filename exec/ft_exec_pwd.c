/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:49:37 by yjama             #+#    #+#             */
/*   Updated: 2021/09/26 11:49:39 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_pwd(void)
{
	char	buf[PATH_MAX];

	if (!(getcwd(buf, PATH_MAX)))
		ft_print_error("getcwd error", NULL, 1);
	else
	{
		ft_putstr_fd(buf, 1);
		ft_putchar_fd('\n', 1);
	}
}
