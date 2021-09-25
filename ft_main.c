/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:49:18 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/25 13:39:12 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare(t_base **b, int argc, char **envp)
{
	if (argc != 1)
	{
		ft_print_error("too many args", NULL, 121);
		exit(121);
	}
	*b = (t_base *)malloc(sizeof(t_base));
	if (!*b)
		return(1);
	ft_init(*b);
	(*b)->envc = ft_doublearray_copy(envp);
	if (!(*b)->envc)
		return(1);
	ft_unset_oldpwd(*b);
	ft_inc_shlvl(*b);
	global_error = 0;
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	t_base *b;

	(void)argv;
	b = NULL;
	if (prepare(&b, argc, envp) != 0)
		return (ft_print_error("malloc error", NULL, 121));
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ignore_sint);
		b->str_rl = readline("minishell$> ");
		if (b->str_rl)
			add_history(b->str_rl);
		if (ft_parser(b) < 0) // Заменила && на || -> убрал проверку на global_error, потому что это нормально, когда эта ошибка присутствует
			return (-1);
		if (b->cmd->cmd[0] != NULL)
			ft_start_exec(b);
		ft_free_struct(b);
		ft_init(b);
	}
	return (0);
}
