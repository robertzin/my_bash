/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_commands_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:43:24 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/26 17:13:23 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_concat(char **arr, char *str)
{
	int		i;
	char	**arr_copy;

	i = 0;
	arr_copy = NULL;
	while (arr[i])
		i++;
	arr_copy = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (arr[i])
	{
		arr_copy[i] = ft_strjoin(arr[i], str);
		i++;
	}
	arr_copy[i] = NULL;
	ft_cleanarr(arr);
	return (arr_copy);
}

char	**ft_parse_path(t_base *b, int num)
{
	char	*path;
	char	**path_arr;

	path = ft_getenv("PATH", b->envc);
	if (path[0] == '\0')
	{
		ft_print_error("No such file or directory", *b->cmd[num].cmd, 127);
		exit(g_error);
	}
	path_arr = ft_split(path, ':');
	path_arr = ft_concat(path_arr, "/");
	return (path_arr);
}
