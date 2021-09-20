/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:49:18 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/20 16:01:21 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_unset_oldpwd(t_base *b)
{
	t_cmd	cmd;

	(void)b;
	cmd.cmd = malloc(sizeof(char *) * 3);
	if (!cmd.cmd)
		return (ft_print_error("malloc error", NULL, 121));
	cmd.cmd[0] = "unset";
	cmd.cmd[1] = "OLDPWD";
	cmd.cmd[2] = NULL;
	ft_exec_unset(b, &cmd);
	free(cmd.cmd);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	t_base *b;
	int 	i;

	(void)argc;
	(void)argv;
	(void)envp;
	b = (t_base *)malloc(sizeof(t_base));
	if (!b)
		return(ft_print_error("malloc error", NULL, 121));
	ft_init(b);
	b->envc = ft_doublearray_copy(envp);
	if (!b->envc)
		return(ft_print_error("malloc error", NULL, 121));
	ft_unset_oldpwd(b);
	ft_inc_shlvl(b);
	while (b->exit == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		b->str_rl = readline("minishell$> ");
		if (b->str_rl)
			add_history(b->str_rl);
		i = ft_parser(b);
		if (i < 0)
			return (-1);
		if (b->cmd->cmd[0] != NULL)
			ft_start_exec(b);
		ft_free_struct(b);
		ft_init(b);
	}
	printf("lol\n");
	ft_exec_exit(b->cmd);
	return (0);
}
