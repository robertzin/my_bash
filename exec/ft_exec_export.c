#include "minishell.h"

char	**ft_add_var(char **array, char *str)
{
	int		i;
	char	**new;

	// printf("add var\n");
	// printf("str: %s\n", str);
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
	if (!new[i])
		return (NULL);
	new[++i] = NULL;
	ft_doublearray_free(array);
	// ft_doublearray_print(new);
	return (new);
}

int	ft_is_valid(char *str)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	// printf("str: %s\n", str);
	while (str[j] != '=' && str[j] != '\0')
		j++;
	// printf("str[%d]: %c\n", j, str[j]);
	if (str[j] == '=')
		j++;
	while (str[++i] != '\0' && j != i)
	{
		if (!ft_isalnum(str[i]))
			return (1);
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
		ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
	}
}

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

int	ft_change_var(t_base *main, char *var)
{
	int		i;
	int		len;
	char	*search;

	// printf("change var\n");
	len = 0;
	search = ft_strchr(var, '=');
	if (!search)
		return (1);
	while (var[len] != '=')
		len++;
	search = ft_substr(var, 0, len + 1);
	if (!search)
		return (ft_print_error("malloc error", NULL, 121));
	i = -1;
	while (main->envc[++i] != NULL)
	{
		if (ft_strncmp(main->envc[i], search, len) == 0)
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

	i = 0;
	is_it = 0;
	while (cmd->cmd[++i] != NULL)
	{
		flag = 0;
		if (!ft_isalpha(cmd->cmd[i][0]) && cmd->cmd[i][0] != '_')
			flag = ft_ide_error("export", cmd->cmd[i]);
		else if (ft_is_valid(cmd->cmd[i]) != 0)
			flag = ft_ide_error("export", cmd->cmd[i]);
		else if (ft_strncmp(cmd->cmd[i], "_=", 2) != 0 && flag == 0)
		{
			printf("change var\n");
			is_it = ft_change_var(main, cmd->cmd[i]);
			printf("is it: %d\n", is_it);
			if (!is_it)
			{
				printf("add var\n");
				main->envc = ft_add_var(main->envc, cmd->cmd[i]);
				// ft_doublearray_print(main->envc);
				if (!main->envc)
					return (ft_print_error("add var error", NULL, 1));
			}
		}
	}
	printf("retrun flag\n");
	return (flag);
}

int	ft_exec_export(t_base *main, t_cmd *cmd)
{
	int		ret;
	char	**sorted_env;

	ret = 0;
	// printf("export: \n");
	// ft_doublearray_print(cmd->cmd);
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
	// printf("ret: %d\n", ret);
	// printf("export done\n");
	// ft_doublearray_print(main->envc);
	return (ret);
}
