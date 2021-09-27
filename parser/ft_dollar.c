/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharmund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 21:45:21 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/25 21:45:26 by oharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_val(char *s, char *key, char **envp)
{
	char	*s1;

	s1 = NULL;
	s1 = ft_strdup(s);
	free(s);
	s = ft_strjoin(s1, ft_getenv(key, envp));
	free(s1);
	return (s);
}

char	*ft_qmark(char *s)
{
	char	*s1;
	char	*s2;

	s1 = NULL;
	s2 = NULL;
	if (s)
	{
		s1 = ft_strdup(s);
		free(s);
		s2 = ft_itoa(g_error);
		s = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
	}
	else
		s = ft_itoa(g_error);
	return (s);
}

char	*ft_part_dollar(char *s, char *key, char **envc)
{
	if (s)
		s = ft_add_val(s, key, envc);
	else
		s = ft_strdup(ft_getenv(key, envc));
	free(key);
	return (s);
}

char	*ft_dollar(char *str, char *s, int *i, t_base *b)
{
	char	*key;
	int		j;

	if (!str[(*i) + 1] || str[(*i) + 1] == ' ' || str[(*i) + 1] == '\n' \
		|| str[(*i) + 1] == '<' || str[(*i) + 1] == '>' || str[(*i) + 1] == '|')
	{
		s = ft_symbol(str, s, i);
		return (s);
	}
	j = ++(*i);
	if (str[*i] == '?')
	{
		s = ft_qmark(s);
		return (s);
	}
	while (str[*i] && (str[*i] != ' ' && str[*i] != '\'' && \
		str[*i] != '"' && str[*i] != '<' && str[*i] != '>' && str[*i] != '|'))
		(*i)++;
	key = ft_substr(str, j, (*i) - j);
	(*i)--;
	return (ft_part_dollar(s, key, b->envc));
}
