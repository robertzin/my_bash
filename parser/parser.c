/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:48:58 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/20 15:43:15 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_addarr(char **arr, char *elem)
{
	char	**new_arr;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	new_arr = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
	{
		ft_print_error("malloc error", NULL, 121);
		return (NULL);
	}
	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		free(arr[i]);
		i++;
	}
	free(arr);
	new_arr[i] = ft_strdup(elem);
	new_arr[i + 1] = NULL;
	free(elem);
	return (new_arr);
}

int	ft_rd_pipe_pars(t_base *b, int *i)
{
	int	k;

	k = 0;
	if (b->str_rl[*i] == '<' || b->str_rl[*i] == '>')
	{
		k = ft_redir_parse(b->str_rl, i, b, b->envc);
		if (k < 0)
			return (-1);
	}
	else if (b->str_rl[*i] == '|')
	{
		k = ft_memal_cmd(b);
		if (k < 0)
			return (-1);
		b->count_f++;
	}
	return (0);
}

char	*ft_quotes_dollar(t_base *b, int *i, char *s)
{
	if (b->str_rl[*i] == '\'')
		s = ft_single_quotes(b->str_rl, s, i);
	else if (b->str_rl[*i] == '"')
		s = ft_double_quotes(b->str_rl, s, i, b->envc);
	else if (b->str_rl[*i] == '$')
		s = ft_dollar(b->str_rl, s, i, b->envc);
	return (s);
}

int	ft_word(t_base *b, int *i)
{
	char	*s;
	int		k;

	s = NULL;
	k = 0;
	while (b->str_rl[*i] && (b->str_rl[*i] != ' ' && b->str_rl[*i] != '\t'))
	{
		if (b->str_rl[*i] == '\'' || b->str_rl[*i] == '"' || \
			b->str_rl[*i] == '$')
			s = ft_quotes_dollar(b, i, s);
		else if (b->str_rl[*i] == '<' || b->str_rl[*i] == '>' || \
			b->str_rl[*i] == '|')
		{
			k = ft_rd_pipe_pars(b, i);
			if (k < 0)
				return (-1);
		}
		else
			s = ft_symbol(b->str_rl, s, i);
		(*i)++;
	}
	if (s)
		b->cmd[b->count_cmd - 1].cmd = \
			ft_addarr(b->cmd[b->count_cmd - 1].cmd, s);
	return (0);
}

int	ft_parser(t_base *b)
{
	int	*i;
	int	k;

	i = (int *)malloc(sizeof(int));
	if (!i)
		return(ft_print_error("malloc error", NULL, 121));
	k = ft_init_cmd(b);
	if (!i || k < 0)
		return (-1);
	parser_env(b);
	*i = 0;
	while (b->str_rl[*i] && b->str_rl[*i] != '\n')
	{
		k = ft_word(b, i);
		if (k < 0)
			return (-1);
		while (b->str_rl[*i] == ' ')
			(*i)++;
	}
	free(i);
	return (0);
}
