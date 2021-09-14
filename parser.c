#include "minishell.h"

char	*ft_dollar(t_main *main, char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*key;
	char	*env;
	char	*end;

	j = *i;
	tmp = NULL;
	while (str[++(*i)])
	{
		if (!ft_if_key(str[*i]))
			break ;
	}
	if (*i == j + 1)
		return (str);
	else
	{
		tmp = ft_substr(str, 0, j);
		key = ft_substr(str, j + 1, *i - j - 1);
		ft_skip_spaces(str, i);
		j = *i;
		while (str[++(*i)])
			;
		end = ft_strdup(str + j);
		if (ft_find_key(main, key) != NULL)
		{
			env = ft_strdup(ft_find_key(main, key));
			env = ft_key_clear(env);
			if (env)
				tmp = ft_strjoin(tmp, env);
			tmp = ft_strjoin(tmp, " ");
			tmp = ft_strjoin(tmp, end);
			free(env);
		}
		free(key);
		free(end);
	}
	return (tmp);
}

int	ft_words_count(char *str, char c)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			in_word = 0;
		if (str[i] != c && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		i++;
	}
	return (count);
}

void parser(t_main *main, char *str, t_cmd *cmd)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		// 	str = ft_gap(str, &i);
		// if (str[i] == '\\')
		// 	str = ft_slash(str, &i);
		// if (str[i] == '\"')
		// 	str = ft_double_gap(str, &i);
		if (str[i] == '$')
			str = ft_dollar(main, str, &i);
	}
	if (str)
		cmd->cmd = ft_split(str, ' ');
	free(str);
}
