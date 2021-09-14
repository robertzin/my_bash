#include "minishell.h"

int ft_main_home(t_main *main)
{
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	while (main->env[i] != NULL)
	{
		if (ft_strncmp(main->env[i], "HOME=", 5) == 0)
		{
			line = ft_strdup(main->env[i] + 5);
			if (!line)
				return (-1);
		}
		i++;
	}
	main->home = line;
	return (0);
}

int	ft_main_pwd(t_main *main)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (main->env[i] != NULL)
	{
		if (ft_strncmp(main->env[i], "PWD=", 4) == 0)
		{
			line = ft_strdup(main->env[i] + 4);
			if (!line)
				return (-1);
		}
		i++;
	}
	main->pwd = line;
	return (0);
}

int	ft_main_path(t_main *main)
{
	int		i;
	char	**path;

	i = -1;
	path = NULL;
	while (main->env[++i] != NULL)
	{
		if (ft_strncmp(main->env[i], "PATH=", 5) == 0)
		{
			path = ft_split(main->env[i] + 5, ':');
			if (path == NULL)
				return (-1);
		}
	}
	main->path = path;
	return (0);
}

int	parser_env(t_main *main)
{
	if (main->path != NULL)
	{
		ft_doublearray_free(main->path);
		main->path = NULL;
	}
	if (main->pwd)
	{
		free(main->pwd);
		main->pwd = NULL;
	}
	if (main->home)
	{
		free(main->home);
		main->home = NULL;
	}
	ft_main_path(main);
	ft_main_pwd(main);
	ft_main_home(main);
	return (0);
}
