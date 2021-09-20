/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharmund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:49:46 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/16 20:49:48 by oharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_kill_proc(int *pid, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
}

void	ft_clean_fd(int **fd, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	ft_close_pipefd(int **fd, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < 2)
		{
			close(fd[i][j]);
			j++;
		}
		i++;
	}
}

int	ft_memal_fd(t_base *b)
{
	int	i;

	i = 0;
	b->fd = (int **)malloc(sizeof(int *) * b->count_f);
	if (!b->fd)
		return (-1);
	while (i < b->count_f)
	{
		b->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!b->fd[i])
		{
			ft_clean_fd(b->fd, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_pipe_init(t_base *b)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	k = ft_memal_fd(b);
	if (k < 0)
		return (-1);
	while (i < b->count_f)
	{
		k = pipe(b->fd[i]);
		if (k < 0)
		{
			ft_close_pipefd(b->fd, i);
			ft_clean_fd(b->fd, b->count_f);
			return (-1);
		}
		i++;
	}
	return (0);
}
