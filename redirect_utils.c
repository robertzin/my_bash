/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharmund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:50:11 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/16 20:50:13 by oharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_db_rev_rdir(t_base *b, int num)
{
	int	fd;

	fd = 0;
	b->cmd[num].sstdi = dup(0);
	fd = open(".tmp", O_RDONLY);
	if (fd < 0)
	{
		close(b->cmd[num].sstdi);
		return (-1);
	}
	dup2(fd, 0);
	return (fd);
}

int	ft_write_heredoc(t_base *b, int num, int i)
{
	int		fd;
	int		k;
	char	*s;
	int		len;

	k = 1;
	len = ft_strlen(b->cmd[num].rd[i].delimiter);
	fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	b->cmd[num].hdoc = 1;
	while (k != 0)
	{
		s = NULL;
		s = readline("> ");
		k = ft_strcmp(s, b->cmd[num].rd[i].delimiter);
		if (k != 0)
		{
			write(fd, s, ft_strlen(s));
			write(fd, "\n", 1);
		}
		free(s);
	}
	close(fd);
	return (0);
}

int	ft_rev_rdir(t_base *b, int num, int i)
{
	int	fd;

	fd = 0;
	b->cmd[num].sstdi = dup(0);
	fd = open(b->cmd[num].rd[i].filename, O_RDONLY);
	if (fd < 0)
	{
		close(b->cmd[num].sstdi);
		return (-1);
	}
	dup2(fd, 0);
	return (fd);
}

int	ft_doub_rdir(t_base *b, int num, int i)
{
	int	fd;

	fd = 0;
	b->cmd[num].sstdo = dup(1);
	fd = open(b->cmd[num].rd[i].filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		close(b->cmd[num].sstdo);
		return (-1);
	}
	dup2(fd, 1);
	return (fd);
}

int	ft_rdir(t_base *b, int num, int i)
{
	int	fd;

	fd = 0;
	b->cmd[num].sstdo = dup(1);
	fd = open(b->cmd[num].rd[i].filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		close(b->cmd[num].sstdo);
		return (-1);
	}
	dup2(fd, 1);
	return (fd);
}
