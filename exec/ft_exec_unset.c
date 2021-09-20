#include "minishell.h"

int	ft_unset_env(char *arg, t_base *main)
{
	if (ft_strcmp(arg, "PWD=") == 0)
	{
		free(main->pwd);
		main->pwd = NULL;
	}
	if (ft_strcmp(arg, "OLDPWD=") == 0)
	{
		free(main->oldpwd);
		main->oldpwd = NULL;
	}
	if (ft_strcmp(arg, "HOME=") == 0)
	{
		free(main->home);
		main->home = NULL;
	}
	if (ft_strcmp(arg, "PATH=") == 0)
	{
		ft_doublearray_free(main->path);
		main->path = NULL;
	}
	return (0);
}

int	ft_unset_arg_done(t_base *main, int pos)
{
	char	**new_env;
	int		j;
	int		k;

	k = 0;
	while (main->envc[k] != NULL)
		k++;
	new_env = malloc(sizeof(char *) * k);
	if (!new_env)
		return (ft_print_error("malloc error", NULL, 121));
	j = -1;
	k = -1;
	while (main->envc[++j] != NULL)
	{
		// printf("j = %d, pos = %d\n", j, pos);
		if (j == pos)
			j++;
		if (main->envc[j] == NULL)
			break ;
		// printf("main->envc[%d] = %s\n", j, main->envc[j]);
		new_env[++k] = ft_strdup(main->envc[j]);
		// printf("strdup\n");
		if (!new_env[k])
			return (ft_print_error("malloc error", NULL, 121));
		if (main->envc[j] == NULL)
			j--;
	}
	ft_doublearray_free(main->envc);
	if (new_env[k] != NULL)
		new_env[++k] = NULL;
	main->envc = new_env;
	return (0);
}

int	ft_unset_arg(t_base *main, char *arg)
{
	int	pos;
	int	len;
	int	ret;

	ret = 0;
	arg = ft_strjoin(arg, "=");
	if (!arg)
		return (ft_print_error("malloc error", NULL, 121));
	ret = ft_unset_env(arg, main);
	len = ft_strlen(arg);
	pos = -1;
	while (main->envc[++pos] != NULL)
	{
		if (ft_strncmp(arg, main->envc[pos], len) == 0)
		{
			ft_unset_arg_done(main, pos);
			break ;
		}
	}
	free(arg);
	return (ret);
}

int	ft_exec_unset(t_base *main, t_cmd *cmd)
{
	int	i;
	int	ret;

	ret = 0;
	if (cmd->cmd[1] == NULL)
		return (1);
	i = -1;
	while (cmd->cmd[++i] != NULL)
	{
		if (ft_isalpha(cmd->cmd[i][0]) || cmd->cmd[i][0] == '_')
			ft_unset_arg(main, cmd->cmd[i]);
		else
			ret = ft_ide_error("unset", cmd->cmd[i]);
	}
	return (ret);
}
