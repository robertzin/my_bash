#include "minishell.h"

int	ft_if_key(char c)
{
	if (c == '_' || isalnum(c))
		return (1);
	return (0);
}

int	ft_skip_spaces(char *str, int *i)
{
	while (isspace(str[*i]))
		++(*i);
	return (*i);
}

char	*ft_gap(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	//free(tmp2);
	//free(tmp3);
	//free(str);
	return (tmp);
}

char	*ft_slash(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	//free(tmp2);
	//free(str);
	++(*i);
	return (tmp);
}

char	*ft_double_gap(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\"'
			|| str[*i + 1] == '$' || str[*i + 1] == '\\'))
			str = ft_slash(str, i);
		if (str[*i] == '\"')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	//free(tmp2);
	//free(tmp3);
	//free(str);
	return (tmp);
}

char	*ft_dollar(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*key;
	char	*env;
	char	*end;

	j = *i;
	while (str[++(*i)])
	{
		if (!ft_if_key(str[*i]))
			break ;
	}
	if (*i == j + 1)
		return (str);
	tmp = ft_substr(str, 0, j);
	key = ft_substr(str, j + 1, *i - j - 1);
	ft_skip_spaces(str, i);
	j = *i;
	while (str[++(*i)])
		;
	end = ft_strdup(str + j);
	env = getenv(key);
	if (env)
		tmp = ft_strjoin(tmp, env);
	tmp = ft_strjoin(tmp, " ");
	tmp = ft_strjoin(tmp, end);
	free(key);
	// free(env);
	free(end);
	return (tmp);
}

void parser(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		// if (str[i] == '\'')
		// 	str = ft_gap(str, &i);
		// if (str[i] == '\\')
		// 	str = ft_slash(str, &i);
		// if (str[i] == '\"')
		// 	str = ft_double_gap(str, &i);
		if (str[i] == '$')
			str = ft_dollar(str, &i);
	}
	printf("%s\n", str);
	free(str);
}

int main()
{
	char	*input;

	// input = ft_strdup("input'");
	// parser(input);

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break;
		else
		{
			add_history(input); //adding the previous input into history
			parser(input);
		}
	}
	return (0);
}
