/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:48:42 by yjama             #+#    #+#             */
/*   Updated: 2021/09/11 12:59:48 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(const char *input, char c)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (input[i] != 0)
	{
		if (input[i] == c)
			in_word = 0;
		if (input[i] != c && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		i++;
	}
	return (count);
}

int	ft_count_letters(const char *input, char c)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != c)
		i++;
	return (i);
}

void	ft_memleak(char **array, int curr)
{
	int	i;

	i = 0;
	while (i < curr)
		free(array[i++]);
	free(array);
}

char	**ft_array(char const *s, int words, char c, char **splitted)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		len = ft_count_letters(s, c);
		splitted[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!(splitted[i]))
		{
			ft_memleak(splitted, i);
			return (NULL);
		}
		j = 0;
		while (j < len)
			splitted[i][j++] = *s++;
		splitted[i][j] = '\0';
		i++;
	}
	splitted[i] = NULL;
	return (splitted);
}

char	**ft_split(char	const *s, char c)
{
	char	**array;
	int		words;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array = ft_array(s, words, c, array);
	return (array);
}
