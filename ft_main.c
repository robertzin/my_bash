/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:49:18 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/25 17:45:02 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_doublearray_copy(char **array)
{
	int		i;
	char	**new;

	i = 0;
	if (!array)
		return (NULL);
	while (array[i] != NULL)
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	ft_doublearray_print(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		ft_putstr_fd(array[i], 1);
		ft_putchar_fd('\n', 1);
	}
}

void	ft_doublearray_free(char **array)
{
	int		i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
		{
			if (array[i])
				free(array[i]);
			i++;
		}
		free(array);
	}
}

int	prepare(t_base **b, int argc, char **envp)
{
	struct termios	t;

	if (argc != 1)
	{
		ft_print_error("too many args", NULL, 121);
		exit(121);
	}
	*b = (t_base *)malloc(sizeof(t_base));
	if (!*b)
		return (1);
	ft_init(*b);
	(*b)->envc = ft_doublearray_copy(envp);
	if (!(*b)->envc)
		return (1);
	ft_unset_oldpwd(*b);
	ft_inc_shlvl(*b);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ignore_sint);
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
	g_error = 0;
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_base	*b;

	(void)argv;
	b = NULL;
	if (prepare(&b, argc, envp) != 0)
		return (ft_print_error("malloc error", NULL, 121));
	while (1)
	{
		b->str_rl = readline("minishell$> ");
		if (b->str_rl == NULL)
			ft_ctrld_exit();
		if (b->str_rl)
			add_history(b->str_rl);
		if (ft_parser(b) >= 0 && b->cmd->cmd[0] != NULL)
			ft_start_exec(b);
		ft_free_struct(b);
		ft_init(b);
	}
	return (0);
}
