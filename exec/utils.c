/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:50:37 by yjama             #+#    #+#             */
/*   Updated: 2021/09/26 11:50:38 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_add_var(char **array, char *str)
{
	int		i;
	char	**new;

	if (!str)
		return (array);
	i = 0;
	while (array[i] != NULL)
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
	{
		ft_print_error("malloc error", NULL, 121);
		return (NULL);
	}
	i = -1;
	if (array[0] != NULL)
	{
		while (array[++i] != NULL)
			new[i] = ft_strdup(array[i]);
	}
	new[i] = ft_strdup(str);
	new[++i] = NULL;
	ft_doublearray_free(array);
	return (new);
}

int	ft_is_valid(char *str, int one_word)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	if (one_word == 1)
	{
		while (str[i] != '=' && str[i] != '\0')
			i++;
	}
	else
	{
		while (str[i] != '=')
			i++;
	}
	while (str[j] != '\0' && j != i)
	{
		if (!ft_isalnum(str[j]))
			return (1);
		j++;
	}
	return (0);
}

void	ft_sorted_print(char **envc)
{
	int		i;
	int		j;
	int		flag;

	i = -1;
	while (envc[++i] != 0)
	{
		j = -1;
		flag = 0;
		ft_putstr_fd("declare -x ", 1);
		while (envc[i][++j] != '\0')
		{
			ft_putchar_fd(envc[i][j], 1);
			if (envc[i][j] == '=' && flag == 0)
			{
				flag = 1;
				ft_putchar_fd('"', 1);
			}
		}
		if (flag == 1)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
	}
}

char	*ft_goto_norm(int num)
{
	if (num == 0)
		ft_print_error("getcwd error", NULL, 1);
	else
		ft_print_error("malloc error", NULL, 121);
	return (NULL);
}

int	ft_unset_oldpwd(t_base *b)
{
	t_cmd	cmd;

	(void)b;
	cmd.cmd = malloc(sizeof(char *) * 3);
	if (!cmd.cmd)
		return (ft_print_error("malloc error", NULL, 121));
	cmd.cmd[0] = "unset";
	cmd.cmd[1] = "OLDPWD";
	cmd.cmd[2] = NULL;
	ft_exec_unset(b, &cmd);
	free(cmd.cmd);
	return (0);
}
