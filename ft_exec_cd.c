#include "minishell.h"

int	ft_cd_error(char *var, char *str)
{
	(void)var;
	global_error = 1;
	if (str != NULL)
	{
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	else
	{
		write(2, "minishell: ", 11);
		write(2, var, ft_strlen(var));
		write(2, ": No such file or directory", 26);
		ft_putchar_fd('\n', 2);
	}
	return (-1);
}

char	*ft_goto(t_main *main)
{
	int		i;
	char	*oldpwd;
	char	buf[PATH_MAX];

	i = -1;
	oldpwd = NULL;
	while (main->env[++i] != NULL)
	{
		if (ft_strncmp(main->env[i], "PWD=", 4) == 0)
		{
			if (!(getcwd(buf, PATH_MAX)))
			{
				global_error = 1;
				ft_putendl_fd("getcwd error\n", 2);
				return (NULL);
			}
			oldpwd = main->env[i];
			main->env[i] = ft_strjoin("PWD=", buf);
			if (main->env[i])
			{
				global_error = 1;
				ft_putendl_fd("malloc error\n", 2);
				return (NULL);
			}
			free(main->pwd);
			main->pwd = ft_strdup(main->env[i]);
			if (!main->env[i])
			{
				global_error = 1;
				ft_putendl_fd("malloc error\n", 2);
				return (NULL);
			}
			return (oldpwd);
		}
	}
	return (oldpwd);
}

int	ft_export_oldpwd(t_main *main, char *oldpwd)
{
	t_cmd	cmd;

	cmd.cmd = malloc(sizeof(char *) * 3);
	if (cmd.cmd)
	{
		cmd.cmd[0] = ft_strdup("export");
		cmd.cmd[1] = ft_strjoin("OLD", oldpwd);
		if (!cmd.cmd[1])
		{
			global_error = 1;
			ft_putendl_fd("malloc error\n", 2);
			return (-1);
		}
		cmd.cmd[2] = NULL;
		ft_exec(main, &cmd);
		ft_doublearray_free(cmd.cmd);
	}
	return (0);
}

int	ft_set_oldpwd(t_main *main, char *oldpwd)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (main->env[++i] != NULL)
	{
		if (ft_strncmp(main->env[i], "OLDPWD=", 7) == 0)
		{
			flag = 1;
			free(main->env[i]);
			main->env[i] = ft_strjoin("OLD", oldpwd);
			if (!main->env[i])
				return (-1);
			break ;
		}
	}
	if (flag == 0)
		ft_export_oldpwd(main, oldpwd);
	free(main->oldpwd);
	main->oldpwd = ft_strdup(main->env[i]);
	free(oldpwd);
	return (0);
}

int	ft_pre_goto(t_main *main, char **oldpwd, int flag)
{
	if (flag == 0)
	{
		if (main->home == NULL)
			return (ft_cd_error(NULL, "minishell: cd: HOME not set"));
		if (chdir(main->home) == -1)
			return (ft_cd_error(main->home, NULL));
		*oldpwd = ft_goto(main);
		if (*oldpwd == NULL)
			return (-2);
	}
	else if (flag == 1)
	{
		if (main->oldpwd == NULL)
			return (ft_cd_error(NULL, "minishell: cd: OLDPWD not set"));
		if (chdir(main->oldpwd + 7) == -1)
			return (ft_cd_error(main->oldpwd + 7, NULL));
		*oldpwd = ft_goto(main);
		if (*oldpwd == NULL)
			return (-2);
		ft_putendl_fd(main->oldpwd + 7, 1);
	}
	return (0);
}

int	ft_exec_cd(t_main *main, t_cmd *cmd)
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
