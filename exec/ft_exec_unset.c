#include "minishell.h"

void	ft_unset_env_norm(t_base *main, int flag)
{
	if (flag == 0)
	{
		free(main->pwd);
		main->pwd = NULL;
	}
	else if (flag == 1)
	{
		free(main->oldpwd);
		main->oldpwd = NULL;
	}
	else if (flag == 2)
	{
		free(main->home);
		main->home = NULL;
	}
	else if (flag == 3)
	{
		ft_doublearray_free(main->path);
		main->path = NULL;
	}
}

int	ft_unset_env(char *arg, t_base *main)
{
	char	*tmp;
	int		flag;

	flag = 0;
	tmp = ft_strjoin(arg, "=");
	if (!tmp)
		return (ft_print_error("malloc error", NULL, 121));
	if (ft_strcmp(tmp, "PWD=") == 0)
		flag = 0;
	if (ft_strcmp(tmp, "OLDPWD=") == 0)
		flag = 1;
	if (ft_strcmp(tmp, "HOME=") == 0)
		flag = 2;
	if (ft_strcmp(tmp, "PATH=") == 0)
		flag = 3;
	ft_unset_env_norm(main, flag);
	free(tmp);
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
		if (j == pos)
			j++;
		if (main->envc[j] == NULL)
			break ;
		new_env[++k] = ft_strdup(main->envc[j]);
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
	size_t	j;
	int		pos;
	int		len;
	int		ret;

	ret = 0;
	ret = ft_unset_env(arg, main);
	len = ft_strlen(arg);
	pos = -1;
	while (main->envc[++pos] != NULL)
	{
		if (ft_strncmp(main->envc[pos], arg, len) == 0)
		{
			j = 0;
			while (main->envc[pos][j] != '=' && main->envc[pos][j] != '\0')
				j++;
			if (j == ft_strlen(arg))
			{
				ft_unset_arg_done(main, pos);
				break ;
			}
		}
	}
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
