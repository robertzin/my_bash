#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char*)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char *ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char*)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = 0;
	return (str);
}

// char	*ft_gap(char *str, int i)
// {
// 	int		j;
// 	char	*tmp_a;
// 	char	*tmp_b;
// 	char	*tmp_c;

// 	j = i;
// 	while (str[++i])
// 	{
// 		if (str[i] == '\'')
// 			break;
// 	}
// 	tmp_a = substr()
// }

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
		// else
		// 	putchar(str[i]);
		// if (str[i] == '\'')
		// 	ft_gap(str, i);
	}
	
	// if (str[i] != '\0')
	printf("%s\n", str);
}

int main()
{
    char	*input;
	char	*error;
	char	*rl;

	error = "minishell: xxx: command not found\n";
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