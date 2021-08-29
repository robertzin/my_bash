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
