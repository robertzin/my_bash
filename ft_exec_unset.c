#include "minishell.h"

int	ft_unset_env(char *arg, t_main *main)
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

void	ft_unset_arg_done(t_main *main, int pos)
{
	char	**new_env;
	int		j;
	int		k;

	k = 0;
	while (main->env[k] != NULL)
		k++;
	new_env = malloc(sizeof(char *) * k);
	if (new_env)
	{
		j = -1;
		k = -1;
		while (main->env[++j] != NULL)
		{
			if (j == pos)
				j++;
			new_env[++k] = ft_strdup(main->env[j]);
			if (main->env[j] == NULL)
				j--;
		}
		ft_doublearray_free(main->env);
		if (new_env[k] != NULL)
			new_env[++k] = NULL;
		main->env = new_env;
	}
}

int	ft_unset_arg(t_main *main, char *arg)
{
	int	pos;
	int	len;
	int	ret;

	ret = 0;
	arg = ft_strjoin(arg, "=");
	if (!arg)
	{
		global_error = 1;
		ft_putendl_fd("malloc error", 2);
		return (1);
	}
	ret = ft_unset_env(arg, main);
	len = ft_strlen(arg);
	pos = -1;
	while (main->env[++pos] != NULL)
	{
		if (ft_strncmp(arg, main->env[pos], len) == 0)
		{
			ft_unset_arg_done(main, pos);
			break ;
		}
	}
	free(arg);
	return (ret);
}

int	ft_exec_unset(t_main *main, t_cmd *cmd)
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
			ret = 1;
	}
	return (ret);
}
