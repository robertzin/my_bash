/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:49:56 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/27 10:13:22 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_repl_fd(t_base *b, int i)
{
	int	j;

	j = 0;
	while (j < b->count_f)
	{
		if (j != i && j != (i - 1))
		{
			close(b->fd[j][0]);
			close(b->fd[j][1]);
		}
		j++;
	}
	if (i)
	{
		close(b->fd[i - 1][1]);
		dup2(b->fd[i - 1][0], 0);
		close(b->fd[i - 1][0]);
	}
	if (i < b->count_f)
	{
		close(b->fd[i][0]);
		dup2(b->fd[i][1], 1);
		close(b->fd[i][1]);
	}
	return (0);
}

void	ft_close_parent_fd(t_base *b)
{
	int	i;

	i = 0;
	while (i < b->count_f)
	{
		close(b->fd[i][0]);
		close(b->fd[i][1]);
		i++;
	}
}

int	ft_chaild_proc_pipe(t_base *b)
{
	int	k;
	int	i;
	int	*pid;

	i = 0;
	pid = (int *)malloc(sizeof(int) * b->count_cmd);
	if (!pid)
		return (-1);
	while (i < b->count_cmd)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			ft_kill_proc(pid, i);
			return (-1);
		}
		else if (pid[i] == 0)
		{
			ft_repl_fd(b, i);
			k = ft_redirect(b, i);
			exit(k);
		}
		i++;
	}
	return (0);
}

int	ft_pipe(t_base *b)
{
	int	i;
	int	status;
	int	k;

	i = 0;
	k = ft_chaild_proc_pipe(b);
	ft_close_parent_fd(b);
	while (i < b->count_cmd)
	{
		waitpid(0, &status, 0);
		g_error = WEXITSTATUS(status);
		if (b->cmd[i].hdoc == 1)
			unlink(".tmp");
		i++;
	}
	return (0);
}

int	ft_start_exec(t_base *b)
{
	int	k;

	k = 0;
	if (b->count_f == 0)
		ft_redirect(b, 0);
	else
	{
		k = ft_pipe_init(b);
		if (k < 0)
			return (-1);
		k = ft_pipe(b);
		if (k < 0)
			return (-1);
		ft_clean_fd(b->fd, b->count_f);
	}
	return (0);
}
