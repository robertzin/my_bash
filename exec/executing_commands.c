/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:43:09 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/20 16:03:02 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_arr_path_cmd(t_base *b, int num)
{
	char	**path_arr;

	path_arr = NULL;
	path_arr = ft_parse_path(b);
	path_arr = ft_concat(path_arr, b->cmd[num].cmd[0]);
	return (path_arr);
}

char	**ft_path_cmd(t_base *b, int num)
{
	int		i;
	char	**path_cmd;

	i = 0;
	if (b->cmd[num].cmd[0][0] == '/' || (b->cmd[num].cmd[0][0] == '.' \
			&& b->cmd[num].cmd[0][1] == '/'))
	{
		path_cmd = (char **)malloc(sizeof(char *) * 2);
		if (!path_cmd)
			return (NULL);
		path_cmd[0] = ft_strdup(b->cmd[num].cmd[0]);
		path_cmd[1] = NULL;
	}
	else if (b->cmd[num].cmd[0][0] == '~' && b->cmd[num].cmd[0][1] == '/')
		path_cmd = ft_home_dir(b, num);
	else
		path_cmd = ft_arr_path_cmd(b, num);
	return (path_cmd);
}

char	**ft_home_dir(t_base *b, int num)
{
	char	*val;
	char	**pathname;

	val = NULL;
	pathname = NULL;
	val = ft_getenv("HOME", b->envc);
	pathname = (char **)malloc(sizeof(char *) * 2);
	if (!pathname)
	{
		ft_print_error("malloc error", NULL, 121);
		return (NULL);
	}
	pathname[0] = ft_strjoin(val, &b->cmd[num].cmd[0][1]);
	pathname[1] = NULL;
	return (pathname);
}

void	ft_childproc(t_base *b, int num)
{
	char	**pathname;
	int		i;
	int		k;

	i = 0;
	k = 0;
	pathname = NULL;
	pathname = ft_path_cmd(b, num);
	if (!pathname)
		exit(1);
	while (pathname[i])
	{
		k = execve(pathname[i], b->cmd[num].cmd, b->envc);
		i++;
	}
	if (k < 0)
	{
		ft_print_error("command not found", *b->cmd[num].cmd, 127);
		ft_cleanarr(pathname);
	}
	exit(k);
}

int	ft_exec_cmd(t_base *b, int num)
{
	int	id;
	int	status;

	id = fork();
	if (id == 0)
		ft_childproc(b, num);
	else if (id < 0)
		return (-1);
	else
	{
		signal(SIGQUIT, ignore_squit2);
		signal(SIGINT, ignore_sint2);
		waitpid(id, &status, 0);
		b->err = WEXITSTATUS(status);
		return (0);
	}
	return (0);
}
