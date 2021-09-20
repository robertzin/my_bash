/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_dollar_symbol.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharmund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:47:33 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/16 20:47:36 by oharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_symbol(char *str, char *s, int *i)
{
	char	c[2];
	char	*s1;

	c[0] = str[*i];
	c[1] = '\0';
	s1 = NULL;
	if (!s)
		s = ft_strdup(c);
	else
	{
		s1 = ft_strdup(s);
		free(s);
		s = ft_strjoin(s1, c);
		free(s1);
	}
	if (!s)
		return (NULL);
	return (s);
}

char	*ft_double_quotes(char *str, char *s, int *i, char **envp)
{
	int		*j;
	char	*s1;

	(*i)++;
	j = (int *)malloc(sizeof(int));
	if (!j)
		return (NULL);
	*j = *i;
	s1 = NULL;
	while (str[*i] && str[*i] != '"')
		(*i)++;
	if (str[*i] != '"')
		return (NULL);
	s1 = ft_substr(str, *j, (*i) - (*j));
	*j = 0;
	while (s1[*j])
	{
		if (s1[*j] == '$')
			s = ft_dollar(s1, s, j, envp);
		else
			s = ft_symbol(s1, s, j);
		(*j)++;
	}
	free(s1);
	return (s);
}

char	*ft_single_quotes(char *str, char *s, int *i)
{
	int		j;
	char	*s1;
	char	*s2;

	(*i)++;
	j = *i;
	s1 = NULL;
	s2 = NULL;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] != '\'')
		return (NULL);
	s1 = ft_substr(str, j, (*i) - j);
	if (!s)
	{
		s = ft_strdup(s1);
		free(s1);
		return (s);
	}
	s2 = ft_strdup(s);
	free(s);
	s = ft_strjoin(s2, s1);
	free(s1);
	free(s2);
	return (s);
}

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

char	*ft_dollar(char *str, char *s, int *i, char **envp)
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
	while (str[*i] && (str[*i] != ' ' && str[*i] != '\'' && \
		str[*i] != '"' && str[*i] != '<' && str[*i] != '>' && str[*i] != '|'))
		(*i)++;
	key = ft_substr(str, j, (*i) - j);
	(*i)--;
	if (s)
		s = ft_add_val(s, key, envp);
	else
		s = ft_strdup(ft_getenv(key, envp));
	free(key);
	return (s);
}
