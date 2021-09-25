#include "minishell.h"

void	ft_sorted(char **envc)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	k = 0;
	i = -1;
	while (envc[++i] != NULL)
	{
		j = i;
		while (j > 0 && envc[j - 1][k] >= envc[j][k])
		{
			if (ft_strcmp(envc[j - 1], envc[j]) > 0)
			{
				tmp = envc[j];
				envc[j] = envc[j - 1];
				envc[j - 1] = tmp;
			}
			j--;
		}
	}
}

int	ft_check_one_word(t_base *main, char *var)
{
	int		i;
	int		len;
	size_t	j;

	i = -1;
	len = 0;
	while (var[len] != '\0')
		len++;
	while (main->envc[++i] != NULL)
	{
		if (ft_strncmp(main->envc[i], var, len) == 0)
		{
			j = 0;
			while (main->envc[i][j] != '=' && main->envc[i][j] != '\0')
				j++;
			if (j == ft_strlen(var))
			{
				return (1);
			}
		}
	}
	return (0);
}

int	ft_change_var(t_base *main, char *var)
{
	int		i;
	int		j;
	int		len;
	char	*search;

	len = 0;
	search = ft_strchr(var, '=');
	if (!search)
		return (-1);
	while (var[len] != '=')
		len++;
	search = ft_substr(var, 0, len);
	if (!search)
		return (ft_print_error("malloc error", NULL, 121));
	i = -1;
	while (main->envc[++i] != NULL)
	{
		j = 0;
		while (main->envc[i][j] != '=' && main->envc[i][j] != '\0')
			j++;
		if ((ft_strncmp(main->envc[i], search, j) == 0)
			&& (ft_strncmp(main->envc[i], search, ft_strlen(search)) == 0))
		{
			free(search);
			free(main->envc[i]);
			main->envc[i] = ft_strdup(var);
			if (!main->envc[i])
				return (ft_print_error("malloc error", NULL, 121));
			return (1);
		}
	}
	free(search);
	return (0);
}



int	ft_export_var(t_base *main, t_cmd *cmd)
{
	int		i;
	int		flag;
	int		is_it;
	int		one_word;

	i = 0;
	is_it = 0;
	while (cmd->cmd[++i] != NULL)
	{
		one_word = 0;
		flag = 0;
		if (!ft_strchr(cmd->cmd[i], '='))
			one_word = 1;
		if (ft_is_valid(cmd->cmd[i], one_word) != 0)
			flag = ft_ide_error("export", cmd->cmd[i]);
		else if (ft_strncmp(cmd->cmd[i], "_=", 2) != 0 && flag == 0)
		{
			if (one_word == 0)
				is_it = ft_change_var(main, cmd->cmd[i]);
			else
				is_it = ft_check_one_word(main, cmd->cmd[i]);
			if (!is_it)
			{
				main->envc = ft_add_var(main->envc, cmd->cmd[i]);
				if (!main->envc)
					return (ft_print_error("add var error", NULL, 1));
			}
		}
	}
	return (flag);
}

int	ft_exec_export(t_base *main, t_cmd *cmd)
{
	int		ret;
	char	**sorted_env;

	ret = 0;
	if (cmd->cmd[1] == NULL)
	{
		sorted_env = ft_doublearray_copy(main->envc);
		if (!sorted_env)
			return (ft_print_error("2d array copy error", NULL, 1));
		ft_sorted(sorted_env);
		ft_sorted_print(sorted_env);
		ft_doublearray_free(sorted_env);
	}
	else
		ret = ft_export_var(main, cmd);
	return (ret);
}
