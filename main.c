#include "minishell.h"

int	ft_if_key(char c)
{
	if (c == '_' || isalnum(c))
		return (1);
	return (0);
}

char	*ft_dollar(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*key;
	char	*env;

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
	env = getenv(key);
	if (env)
		tmp = ft_strjoin(tmp, env);
	return (tmp);
}

void parser(char *str)
{
	int	i;

	i = -1;
	printf("%s\n", str);
	while (str[++i])
	{
		if (str[i] == '$')
			str = ft_dollar(str, &i);
	}
	printf("%s\n", str);
}

int main()
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break;
		else
			parser(input);
		add_history(input); //adding the previous input into history
		free(input);
	}
}