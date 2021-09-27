/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:50:23 by yjama             #+#    #+#             */
/*   Updated: 2021/09/26 11:50:24 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_main_home(t_base *main)
{
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	while (main->envc[i] != NULL)
	{
		if (ft_strncmp(main->envc[i], "HOME=", 5) == 0)
		{
			line = ft_strdup(main->envc[i] + 5);
			if (!line)
				return (ft_print_error("malloc error", NULL, 121));
		}
		i++;
	}
	main->home = line;
	return (0);
}

int	ft_main_pwd(t_base *main)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (main->envc[i] != NULL)
	{
		if (ft_strncmp(main->envc[i], "PWD=", 4) == 0)
		{
			line = ft_strdup(main->envc[i] + 4);
			if (!line)
				return (ft_print_error("malloc error", NULL, 121));
		}
		i++;
	}
	main->pwd = line;
	return (0);
}

int	ft_main_oldpwd(t_base *main)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (main->envc[i] != NULL)
	{
		if (ft_strncmp(main->envc[i], "OLDPWD=", 7) == 0)
		{
			line = ft_strdup(main->envc[i] + 7);
			if (!line)
				return (ft_print_error("malloc error", NULL, 121));
		}
		i++;
	}
	main->oldpwd = line;
	return (0);
}

int	ft_main_path(t_base *main)
{
	int		i;
	char	**path;

	i = -1;
	path = NULL;
	while (main->envc[++i] != NULL)
	{
		if (ft_strncmp(main->envc[i], "PATH=", 5) == 0)
		{
			path = ft_split(main->envc[i] + 5, ':');
			if (!path)
				return (ft_print_error("malloc error", NULL, 121));
		}
	}
	main->path = path;
	return (0);
}

int	parser_env(t_base *main)
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
	if (main->oldpwd)
	{
		free(main->oldpwd);
		main->oldpwd = NULL;
	}
	if (main->home)
	{
		free(main->home);
		main->home = NULL;
	}
	ft_main_path(main);
	ft_main_pwd(main);
	ft_main_oldpwd(main);
	ft_main_home(main);
	return (0);
}
