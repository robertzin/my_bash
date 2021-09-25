#include "minishell.h"

char	*ft_goto(t_base *main)
{
	int		i;
	char	*oldpwd;
	char	buf[PATH_MAX];

	i = -1;
	oldpwd = NULL;
	while (main->envc[++i] != NULL)
	{
		if (ft_strncmp(main->envc[i], "PWD=", 4) == 0)
		{
			if (!(getcwd(buf, PATH_MAX)))
				return (ft_goto_norm(0));
			oldpwd = main->envc[i];
			main->envc[i] = ft_strjoin("PWD=", buf);
			if (!main->envc[i])
				return (ft_goto_norm(1));
			free(main->pwd);
			main->pwd = ft_strdup(main->envc[i]);
			if (!main->envc[i])
				return (ft_goto_norm(1));
			return (oldpwd);
		}
	}
	return (oldpwd);
}

int	ft_export_oldpwd(t_base *main, char *oldpwd)
{
	t_cmd	cmd;

	cmd.cmd = malloc(sizeof(char *) * 3);
	if (cmd.cmd)
	{
		cmd.cmd[0] = ft_strdup("export");
		cmd.cmd[1] = ft_strjoin("OLD", oldpwd);
		if (!cmd.cmd[1])
			return (ft_print_error("malloc error", NULL, 121));
		cmd.cmd[2] = NULL;
		ft_exec_export(main, &cmd);
		ft_doublearray_free(cmd.cmd);
	}
	return (0);
}

int	ft_set_oldpwd(t_base *main, char *oldpwd)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (main->envc[++i] != NULL)
	{
		if (ft_strncmp(main->envc[i], "OLDPWD=", 7) == 0)
		{
			flag = 1;
			free(main->envc[i]);
			main->envc[i] = ft_strjoin("OLD", oldpwd);
			if (!main->envc[i])
				return (ft_print_error("malloc error", NULL, 121));
			break ;
		}
	}
	if (flag == 0)
		ft_export_oldpwd(main, oldpwd);
	free(main->oldpwd);
	main->oldpwd = ft_strdup(main->envc[i]);
	if (!main->oldpwd)
		return (ft_print_error("malloc error", NULL, 121));
	free(oldpwd);
	return (0);
}

int	ft_pre_goto(t_base *main, char **oldpwd, int flag)
{
	if (flag == 0)
	{
		if (main->home == NULL)
			return (ft_cd_error(NULL, "HOME not set"));
		if (chdir(main->home) == -1)
			return (ft_cd_error(main->home, NULL));
		*oldpwd = ft_goto(main);
		if (*oldpwd == NULL)
			return (-2);
	}
	else if (flag == 1)
	{
		if (main->oldpwd == NULL)
			return (ft_cd_error(NULL, "OLDPWD not set"));
		if (chdir(main->oldpwd) == -1)
			return (ft_cd_error(main->oldpwd, NULL));
		*oldpwd = ft_goto(main);
		if (*oldpwd == NULL)
			return (-2);
		ft_putendl_fd(main->oldpwd + 7, 1);
	}
	return (0);
}

int	ft_exec_cd(t_base *main, t_cmd *cmd)
{
	int		i;
	char	*oldpwd;

	i = 0;
	if (cmd->cmd[1] == NULL || (ft_strcmp(cmd->cmd[1], "--") == 0))
	{
		if (ft_pre_goto(main, &oldpwd, 0) < 0)
			return (-1);
	}
	else if (ft_strcmp(cmd->cmd[1], "-") == 0)
	{
		if (ft_pre_goto(main, &oldpwd, 1) < 0)
			return (-1);
	}
	else
	{
		if (chdir(cmd->cmd[1]) == -1)
			return (ft_cd_error(cmd->cmd[1], NULL));
		oldpwd = ft_goto(main);
		if (oldpwd == NULL)
			return (-1);
	}
	ft_set_oldpwd(main, oldpwd);
	return (0);
}
