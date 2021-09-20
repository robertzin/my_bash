/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rd_filename_delimiter.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharmund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:48:00 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/16 20:48:03 by oharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_filename_part(char *str, int *i, t_base *b, char **envp)
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
			b->cmd[j].rd[k].filename, i, envp);
	else if (str[*i] == '$')
	{
		b->cmd[j].rd[k].filename = ft_dollar(str, \
			b->cmd[j].rd[k].filename, i, envp);
	}
	else
		b->cmd[j].rd[k].filename = ft_symbol(str, \
				b->cmd[j].rd[k].filename, i);
}

int	ft_filename(char *str, int *i, t_base *b, char **envp)
{
	while (str[*i] == ' ')
		(*i)++;
	if (!str[*i] || str[*i] == '\n' || str[*i] == '<' || str[*i] == '>')
		return (-1);
	while (str[*i] != ' ' && str[*i] && str[*i] != '\n')
	{
		ft_filename_part(str, i, b, envp);
		(*i)++;
	}
	(*i)--;
	return (0);
}

int	ft_delimiter(char *str, int *i, t_base *b)
{
	int	j;
	int	k;

	j = b->count_cmd - 1;
	k = b->cmd[j].count - 1;
	while (str[*i] == ' ')
		(*i)++;
	if (!str[*i] || str[*i] == '\n' || str[*i] == '<' || str[*i] == '>')
		return (-1);
	while (str[*i] != ' ' && str[*i] && str[*i] != '\n')
	{
		b->cmd[j].rd[k].delimiter = ft_symbol(str, \
					b->cmd[j].rd[k].delimiter, i);
		(*i)++;
	}
	(*i)--;
	return (0);
}
