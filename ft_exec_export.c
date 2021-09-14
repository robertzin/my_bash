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
		return (NULL);
	i = -1;
	if (array[0] != NULL)
	{
		while (array[++i] != NULL)
			new[i] = ft_strdup(array[i]);
	}
	new[i] = ft_strdup(str);
	if (!new[i])
		return (NULL);
	new[++i] = NULL;
	ft_doublearray_free(array);
	return (new);
}

int	ft_is_valid(char *str)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[j] != '=' && str[j] != '\0')
		j++;
	if (str[j] != '=')
		return (1);
	while (str[++i] != '\0' && j != i)
	{
		if (!ft_isalnum(str[i]))
			return (0);
	}
	return (1);
}

void	ft_sorted_print(char **env)
{
	int		i;
	int		j;
	int		flag;

	i = -1;
	while (env[++i] != 0)
	{
		j = -1;
		flag = 0;
		ft_putstr_fd("declare -x ", 1);
		while (env[i][++j] != '\0')
		{
			ft_putchar_fd(env[i][j], 1);
			if (env[i][j] == '=' && flag == 0)
			{
				flag = 1;
				ft_putchar_fd('"', 1);
			}
		}
		ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
	}
}

void	ft_sorted(char **env)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	k = 0;
	i = -1;
	while (env[++i] != NULL)
	{
		j = i;
		while (j > 0 && env[j - 1][k] >= env[j][k])
		{
			if (ft_strcmp(env[j - 1], env[j]) > 0)
			{
				tmp = env[j];
				env[j] = env[j - 1];
				env[j - 1] = tmp;
			}
			j--;
		}
	}
}

int	ft_change_var(t_main *main, char *var)
{
	int		i;
	int		len;
	char	*search;

	len = 0;
	search = ft_strchr(var, '=');
	if (!search)
		return (1);
	while (var[len] != '=')
		len++;
	search = ft_substr(var, 0, len + 1);
	if (!search)
	{
		global_error = 1;
		ft_putendl_fd("malloc error\n", 2);
		return (1);
	}
	i = -1;
	while (main->env[++i] != NULL)
	{
		if (ft_strncmp(main->env[i], search, len) == 0)
		{
			free(search);
			free(main->env[i]);
			main->env[i] = ft_strdup(var);
			if (!main->env[i])
			{
				global_error = 1;
				ft_putendl_fd("malloc error\n", 2);
				return (1);
			}
			return (1);
		}
	}
	free(search);
	return (0);
}

int	ft_export_var(t_main *main, t_cmd *cmd)
{
	int		i;
	int		flag;
	int		is_it;

	i = 0;
	is_it = 0;
	while (cmd->cmd[++i] != NULL)
	{
		flag = 0;
		if (!ft_isalpha(cmd->cmd[i][0]) && cmd->cmd[i][0] != '_')
		{
			global_error = 1;
			printf("export error\n");
			flag = -1;
		}
		else if (ft_is_valid(cmd->cmd[i]) == 0)
		{
			global_error = 1;
			printf("export error\n");
			flag = -1;
		}
		else if (ft_strncmp(cmd->cmd[i], "_=", 2) != 0 && flag == 0)
		{
			is_it = ft_change_var(main, cmd->cmd[i]);
			if (!is_it)
			{
				main->env = ft_add_var(main->env, cmd->cmd[i]);
				if (!main->env)
				{
					global_error = 1;
					ft_putendl_fd("add var error\n", 2);
					return (-1);
				}
			}
		}
	}
	return (flag);
}

int	ft_exec_export(t_main *main, t_cmd *cmd)
{
	int		ret;
	char	**sorted_env;

	ret = 0;
	if (cmd->cmd[1] == NULL)
	{
		sorted_env = ft_doublearray_copy(main->env);
		if (!sorted_env)
		{
			global_error = 1;
			printf("2d array copy error\n");
			return (-1);
		}
		ft_sorted(sorted_env);
		ft_sorted_print(sorted_env);
		ft_doublearray_free(sorted_env);
	}
	else
		ret = ft_export_var(main, cmd);
	return (ret);
}
