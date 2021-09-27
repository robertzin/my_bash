/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_symbol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:47:33 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/26 16:43:13 by yjama            ###   ########.fr       */
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

char	*ft_part_db_quotes(char *s1, char *s, int *j, t_base *b)
{
	while (s1[*j])
	{
		if (s1[*j] == '$')
			s = ft_dollar(s1, s, j, b);
		else
			s = ft_symbol(s1, s, j);
		(*j)++;
	}
	return (s);
}

char	*ft_double_quotes(char *str, char *s, int *i, t_base *b)
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
	{
		free(j);
		ft_print_error("syntax error near unexpected token `\"\'", NULL, 130);
		return (NULL);
	}
	s1 = ft_substr(str, *j, (*i) - (*j));
	*j = 0;
	s = ft_part_db_quotes(s1, s, j, b);
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
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] != '\'')
	{
		ft_print_error("syntax error near unexpected token `\'\'", NULL, 130);
		return (NULL);
	}
	if (!s)
	{
		s = ft_substr(str, j, (*i) - j);
		return (s);
	}
	s1 = ft_substr(str, j, (*i) - j);
	s2 = ft_strdup(s);
	free(s);
	s = ft_strjoin(s2, s1);
	free(s1);
	free(s2);
	return (s);
}
