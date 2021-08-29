/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_upd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 19:58:37 by yjama             #+#    #+#             */
/*   Updated: 2021/08/28 19:58:45 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		*free_str(char **strings)
{
	int		a;

	a = 0;
	while (strings[a])
	{
		free(strings[a]);
		a++;
	}
	free(strings);
	return (NULL);
}

static size_t	delimiter(const char *s, char *set)
{
	size_t		i;
	int			b;
	int			a;

	b = 0;
	i = -1;
	while (b != 1 && s[++i] != 0)
	{
		a = 0;
		while (set[a] != 0 && b == 0)
		{
			if (s[i] == set[a])
				b = 1;
			a++;
		}
	}
	return (i);
}

static size_t	string_count(char const *s, char *str)
{
	size_t		a;
	char		*tmp;
	char		*s1;

	if (!(s1 = ft_strdup(s)))
		return (0);
	a = 0;
	tmp = s1;
	while (*s1)
	{
		if (!(s1 = ft_strtrim(s1, str)))
			return (0);
		free(tmp);
		tmp = s1;
		s1 = s1 + delimiter(s1, str);
		a++;
	}
	free(tmp);
	if (a == 0)
		a = 1;
	return (a);
}

static char		**fill(size_t count, char const *s, char *src, char **str)
{
	int		a;
	char	*s1;
	char	*tmp;

	if (!(s1 = ft_strdup(s)))
		return (NULL);
	a = 0;
	tmp = s1;
	while (count--)
	{
		if (!(s1 = ft_strtrim(s1, src)))
			return (NULL);
		free(tmp);
		tmp = s1;
		if (!(str[a] = ft_substr(s1, 0, delimiter(s1, src))))
		{
			free_str(str);
			return (NULL);
		}
		s1 = s1 + delimiter(s1, src);
		a++;
	}
	free(tmp);
	str[a] = NULL;
	return (str);
}

char			**ft_split_upd(char const *s, char *str)
{
	char		**strings;
	size_t		a;
	size_t		count_words;

	a = 0;
	if (!s || !str)
		return (NULL);
	count_words = string_count(s, str);
	if (!(strings = (char**)malloc(sizeof(char*) * (count_words + 1))))
		return (NULL);
	if (!(strings = fill(count_words, s, str, strings)))
		return (NULL);
	return (strings);
}
