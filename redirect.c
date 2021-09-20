/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharmund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:50:28 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/16 20:50:30 by oharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_returnfd(int fd, int io, int sstd)
{
	close(fd);
	dup2(sstd, io);
	close(sstd);
	return (0);
}

int	ft_redir_op(t_base *b, int num, int fd1, int i)
{
	if (b->cmd[num].rd[i].rdir == 1)
	{
		if (fd1 != 0)
			ft_returnfd(fd1, 1, b->cmd[num].sstdo);
		fd1 = ft_rdir(b, num, i);
	}
	else if (b->cmd[num].rd[i].doub_rdir == 1)
	{
		if (fd1 != 0)
			ft_returnfd(fd1, 1, b->cmd[num].sstdo);
		fd1 = ft_doub_rdir(b, num, i);
	}
	return (fd1);
}

int	ft_redir_ip(t_base *b, int num, int fd2, int i)
{
	if (b->cmd[num].rd[i].rev_rdir == 1)
	{
		if (fd2 != 0)
			ft_returnfd(fd2, 0, b->cmd[num].sstdi);
		fd2 = ft_rev_rdir(b, num, i);
	}
	else if (b->cmd[num].rd[i].db_rev_rdir == 1)
	{
		if (fd2 != 0)
			ft_returnfd(fd2, 0, b->cmd[num].sstdi);
		ft_write_heredoc(b, num, i);
		fd2 = ft_db_rev_rdir(b, num);
	}
	return (fd2);
}

int	ft_redirect(t_base *b, int num)
{
	int	i;
	int	fd1;
	int	fd2;

	i = -1;
	fd1 = 0;
	fd2 = 0;
	while (i++ < b->cmd[num].count)
	{
		if (b->cmd[num].rd[i].rdir == 1 || b->cmd[num].rd[i].doub_rdir == 1)
			fd1 = ft_redir_op(b, num, fd1, i);
		else if (b->cmd[num].rd[i].rev_rdir == 1 || \
			b->cmd[num].rd[i].db_rev_rdir == 1)
			fd2 = ft_redir_ip(b, num, fd2, i);
		if (fd1 < 0 || fd2 < 0)
			return (-1);
	}
	ft_exec(b, num);
	if (b->cmd[num].hdoc == 1)
		unlink(".tmp");
	if (fd1 > 0)
		ft_returnfd(fd1, 1, b->cmd[num].sstdo);
	if (fd2 > 0)
		ft_returnfd(fd2, 0, b->cmd[num].sstdi);
	return (0);
}
