/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharmund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:48:36 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/16 20:48:39 by oharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_redir(t_redir *rd)
{
	rd->rdir = 0;
	rd->doub_rdir = 0;
	rd->rev_rdir = 0;
	rd->db_rev_rdir = 0;
	rd->filename = NULL;
	rd->delimiter = NULL;
}

void	ft_clean_rdstr(t_redir *rd, int i)
{
	i--;
	while (i >= 0)
	{
		if (rd[i].filename)
			free(rd[i].filename);
		if (rd[i].delimiter)
			free(rd[i].delimiter);
		i--;
	}
	free(rd);
}

int	ft_redir_output(t_base *b, int *i, char *str)
{
	(*i)++;
	if (str[*i] == '>')
	{
		(*i)++;
		if (!str[*i] || str[*i] == '\n')
			return (-1);
		b->cmd[b->count_cmd - 1].rd[b->cmd[b->count_cmd - 1].count - 1].doub_rdir = 1; 
	}
	else if (!str[*i] || str[*i] == '\n') 
		return (-1);
	else
		b->cmd[b->count_cmd - 1].rd[b->cmd[b->count_cmd - 1].count - 1].rdir = 1; 
	return (0);
}

int	ft_redir_input(t_base *b, int *i, char *str)
{
	(*i)++;
	if (str[*i] == '<')
	{
		(*i)++;
		if (!str[*i]  || str[*i] == '\n')
			return (-1);
		b->cmd[b->count_cmd - 1].rd[b->cmd[b->count_cmd - 1].count - 1].db_rev_rdir = 1; 
	}
	else if (!str[*i] || str[*i] == '\n') 
		return (-1);
	else
		b->cmd[b->count_cmd - 1].rd[b->cmd[b->count_cmd - 1].count - 1].rev_rdir = 1; 
	return (0);
}

int	ft_redir_parse(char *str, int *i, t_base *b, char **envp)
{
	int k;

	k = ft_memal_redir(b);
	if (k < 0)
		return (-1);
	if (str[*i] == '>')
		k = ft_redir_output(b, i, str);
	else if (str[*i] == '<')
		k = ft_redir_input(b, i, str);
	if (k < 0)
		return (-1);
	if (b->cmd[b->count_cmd - 1].rd[b->cmd[b->count_cmd - 1].count - 1].db_rev_rdir == 1)
		k = ft_delimiter(str, i, b);
	else
		k = ft_filename(str, i, b, envp);
	if (k < 0)
		return (-1);
	return (0);
}
