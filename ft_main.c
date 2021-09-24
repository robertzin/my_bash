/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:49:18 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/24 13:20:20 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare(t_base **b, char **envp)
{
	*b = (t_base *)malloc(sizeof(t_base));
	if (!*b)
		return(1);
	ft_init(*b);
	(*b)->envc = ft_doublearray_copy(envp);
	if (!(*b)->envc)
		return(1);
	ft_unset_oldpwd(*b);
	ft_inc_shlvl(*b);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	t_base *b;

	(void)argc;
	(void)argv;
	b = NULL;
	if (argc != 1)
	{
		ft_print_error("too many args", NULL, 121);
		exit(121);
	}
	if (argc != 1 || prepare(&b, envp) != 0)
		return (ft_print_error("malloc error", NULL, 121));
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ignore_sint);
		b->str_rl = readline("minishell$> ");
		if (b->str_rl)
			add_history(b->str_rl);
		if (ft_parser(b) < 0)
			return (-1);
		if (b->cmd->cmd[0] != NULL)
			ft_start_exec(b);
		ft_free_struct(b);
		ft_init(b);
	}
	return (0);
}
