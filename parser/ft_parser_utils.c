/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:47:19 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/26 17:08:25 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cleanarr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_envcpy(char **envp)
{
	int		i;
	char	**envc;

	i = 0;
	while (envp[i])
		i++;
	envc = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envc)
	{
		ft_print_error("malloc error", NULL, 121);
		return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		envc[i] = ft_strdup(envp[i]);
		i++;
	}
	envc[i] = NULL;
	return (envc);
}

char	*ft_getenv(char *s, char **envp)
{
	int		i;
	int		j;
	int		k;
	char	*s1;

	i = 0;
	k = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		s1 = ft_substr(envp[i], 0, j);
		k = ft_strncmp(s, s1, j + 5);
		if (!k)
		{
			j++;
			free(s1);
			return (&envp[i][j]);
		}
		free(s1);
		i++;
	}
	return ("\0");
}

void	ft_free_struct(t_base *b)
{
	if (b->cmd)
	{
		ft_clean_cmd(b->cmd, b->count_cmd);
	}
	if (b->str_rl)
	{
		free(b->str_rl);
	}
}

void	ft_init(t_base *b)
{
	b->count_cmd = 1;
	b->count_f = 0;
	b->exit = 0;
	b->cmd = NULL;
	b->str_rl = NULL;
}
