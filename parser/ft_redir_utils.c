/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:48:47 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/26 16:45:50 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_part_rd_copy(t_redir *src, t_redir *dst, int i)
{
	dst[i].rdir = src[i].rdir;
	dst[i].doub_rdir = src[i].doub_rdir;
	dst[i].rev_rdir = src[i].rev_rdir;
	dst[i].db_rev_rdir = src[i].db_rev_rdir;
	if (src[i].filename)
		dst[i].filename = ft_strdup(src[i].filename);
	else
		dst[i].filename = NULL;
	if (src[i].delimiter)
		dst[i].delimiter = ft_strdup(src[i].delimiter);
	else
		dst[i].delimiter = NULL;
}

t_redir	*ft_rdcpy(t_redir *src, t_redir *dst, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_part_rd_copy(src, dst, i);
		if (!dst[i].filename && !dst[i].delimiter)
		{
			ft_clean_rdstr(dst, i);
			return (NULL);
		}
		i++;
	}
	return (dst);
}

int	ft_part_memal_redir(t_base *b)
{
	t_redir	*rd_copy;

	rd_copy = (t_redir *)malloc(sizeof(t_redir) * \
		(b->cmd[b->count_cmd - 1].count));
	if (!rd_copy)
		return (-1);
	rd_copy = ft_rdcpy(b->cmd[b->count_cmd - 1].rd, rd_copy, \
		b->cmd[b->count_cmd - 1].count);
	ft_clean_rdstr(b->cmd[b->count_cmd - 1].rd, b->cmd[b->count_cmd - 1].count);
	b->cmd[b->count_cmd - 1].count++;
	b->cmd[b->count_cmd - 1].rd = (t_redir *)malloc(sizeof(t_redir) * \
		(b->cmd[b->count_cmd - 1].count));
	if (!b->cmd[b->count_cmd - 1].rd)
		return (-1);
	b->cmd[b->count_cmd - 1].rd = ft_rdcpy(rd_copy, \
		b->cmd[b->count_cmd - 1].rd, b->cmd[b->count_cmd - 1].count - 1);
	ft_clean_rdstr(rd_copy, b->cmd[b->count_cmd - 1].count - 1);
	return (0);
}

int	ft_memal_redir(t_base *b)
{
	int	i;

	if (b->cmd[b->count_cmd - 1].count > 0)
	{
		i = ft_part_memal_redir(b);
		if (i < 0)
			return (-1);
	}
	else
	{
		b->cmd[b->count_cmd - 1].count++;
		b->cmd[b->count_cmd - 1].rd = (t_redir *)malloc(sizeof(t_redir) * \
			(b->cmd[b->count_cmd - 1].count));
		if (!b->cmd[b->count_cmd - 1].rd)
			return (-1);
	}
	i = b->cmd[b->count_cmd - 1].count - 1;
	ft_init_redir(&b->cmd[b->count_cmd - 1].rd[i]);
	return (0);
}

void	ft_word_norm(t_base *b, char *s)
{
	if (s)
		b->cmd[b->count_cmd - 1].cmd = \
			ft_addarr(b->cmd[b->count_cmd - 1].cmd, s);
}
