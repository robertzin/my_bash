/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharmund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:46:43 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/16 20:46:46 by oharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_cmd(t_cmd *cmd, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		ft_cleanarr(cmd[i].cmd);
		j = 0;
		while (j < cmd[i].count)
		{
			if (cmd[i].rd[j].filename)
				free(cmd[i].rd[j].filename);
			if (cmd[i].rd[j].delimiter)
				free(cmd[i].rd[j].delimiter);
			j++;
		}
		free(cmd[i].rd);
		i++;
	}
}

t_cmd	*ft_cmdcpy(t_cmd *src, t_cmd *dst, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		dst[i].count = src[i].count;
		dst[i].cmd = ft_envcpy(src[i].cmd);
		if (!dst[i].cmd)
			return (NULL);
		dst[i].rd = (t_redir *)malloc(sizeof(t_redir) * count);
		if (!dst[i].rd)
		{
			ft_cleanarr(dst[i].cmd);
			return (NULL);
		}
		dst[i].rd = ft_rdcpy(src[i].rd, dst[i].rd, src[i].count);
		if (!dst[i].rd)
			return (NULL);
		i++;
	}
	return (dst);
}

int	ft_init_cmd(t_base *b)
{
	if (b->count_cmd == 1)
		b->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!b->cmd)
		return (-1);
	b->cmd[b->count_cmd - 1].cmd = (char **)malloc(sizeof(char *));
	b->cmd[b->count_cmd - 1].rd = (t_redir *)malloc(sizeof(t_redir));
	if (!b->cmd[b->count_cmd - 1].cmd || !b->cmd[b->count_cmd - 1].rd)
		return (-1);
	b->cmd[b->count_cmd - 1].count = 0;
	b->cmd[b->count_cmd - 1].cmd[0] = NULL;
	b->cmd[b->count_cmd - 1].sstdi = -1;
	b->cmd[b->count_cmd - 1].sstdo = -1;
	b->cmd[b->count_cmd - 1].hdoc = 0;
	return (0);
}

int	ft_memal_cmd(t_base *b)
{
	t_cmd	*c;
	int		k;

	k = 0;
	c = (t_cmd *)malloc(sizeof(t_cmd) * (b->count_cmd));
	if (!c)
		return (-1);
	c = ft_cmdcpy(b->cmd, c, b->count_cmd);
	if (!c)
		return (-1);
	ft_clean_cmd(b->cmd, b->count_cmd);
	b->count_cmd++;
	b->cmd = (t_cmd *)malloc(sizeof(t_cmd) * (b->count_cmd));
	if (!b->cmd)
	{
		ft_clean_cmd(c, b->count_cmd - 1);
		return (-1);
	}
	b->cmd = ft_cmdcpy(c, b->cmd, b->count_cmd - 1);
	ft_clean_cmd(c, b->count_cmd - 1);
	if (!b->cmd)
		return (-1);
	k = ft_init_cmd(b);
	return (k);
}
