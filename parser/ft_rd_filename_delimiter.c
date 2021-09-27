/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rd_filename_delimiter.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:48:00 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/25 15:05:27 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_filename_part(char *str, int *i, t_base *b)
{
	int	j;
	int	k;

	j = b->count_cmd - 1;
	k = b->cmd[j].count - 1;
	if (str[*i] == '\'')
		b->cmd[j].rd[k].filename = ft_single_quotes(str, \
			b->cmd[j].rd[k].filename, i);
	else if (str[*i] == '"')
		b->cmd[j].rd[k].filename = ft_double_quotes(str, \
			b->cmd[j].rd[k].filename, i, b);
	else if (str[*i] == '$')
	{
		b->cmd[j].rd[k].filename = ft_dollar(str, \
			b->cmd[j].rd[k].filename, i, b);
	}
	else
		b->cmd[j].rd[k].filename = ft_symbol(str, \
				b->cmd[j].rd[k].filename, i);
}

int	ft_filename(char *str, int *i, t_base *b)
{
	while (str[*i] == ' ')
		(*i)++;
	if (!str[*i] || str[*i] == '\n' || str[*i] == '<' || str[*i] == '>' \
			|| str[*i] == '|')
	{
		g_error = 120;
		return (-1);
	}
	while (str[*i] != ' ' && str[*i] && str[*i] != '\n')
	{
		ft_filename_part(str, i, b);
		(*i)++;
	}
	(*i)--;
	return (0);
}

int	ft_delimiter(char *str, int *i, t_base *b)
{
	int	j;

	j = b->count_cmd - 1;
	while (str[*i] == ' ')
		(*i)++;
	if (!str[*i] || str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
	{
		g_error = 121;
		return (-1);
	}
	while (str[*i] != ' ' && str[*i] && str[*i] != '\n')
	{
		b->cmd[j].rd[b->cmd[j].count - 1].delimiter = ft_symbol(str, \
					b->cmd[j].rd[b->cmd[j].count - 1].delimiter, i);
		(*i)++;
	}
	if (!b->cmd[j].rd[b->cmd[j].count - 1].delimiter)
		return (-1);
	if (ft_write_heredoc(b, j, b->cmd[j].count - 1) < 0)
	{
		g_error = 122;
		return (-1);
	}
	(*i)--;
	return (0);
}
