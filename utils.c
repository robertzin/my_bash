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

char	**ft_doublearray_copy(char **array)
{
	int		i;
	char	**new;

	i = 0;
	if (!array)
		return (NULL);
	while (array[i] != NULL)
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	ft_doublearray_print(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		ft_putstr_fd(array[i], 1);
		ft_putchar_fd('\n', 1);
	}
}

void	ft_doublearray_free(char **array)
{
	int		i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
		{
			if (array[i])
				free(array[i]);
			i++;
		}
		free(array);
	}
}

char	*ft_find_key(t_main *main, char *key)
{
	int		i;
	int		len;
	char	*search;

	i = 0;
	search = ft_strjoin(key, "=");
	len = ft_strlen(search);
	while (main->env[i] != NULL)
	{
		if (ft_strncmp(main->env[i], search, len) == 0)
			return (main->env[i]);
		i++;
	}
	return (NULL);
}

char	*ft_key_clear(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = NULL;
	while (str[i])
	{
		if (str[i] == '=')
		{
			new_str = ft_strdup(&str[++i]);
			free(str);
			return (new_str);
		}
		i++;
	}
	return (new_str);
}

void	ft_shlvl(t_main *main)
{
	int		i;
	int		lvl;
	char	*str;

	i = -1;
	while (main->env[++i] != NULL)
	{
		if (ft_strncmp("SHLVL=", main->env[i], 6) == 0)
		{
			lvl = ft_atoi(main->env[i] + 6);
			lvl++;
			free(main->env[i]);
			str = ft_itoa(lvl);
			main->env[i] = ft_strjoin("SHLVL=", str);
			free(str);
		}
	}
}
