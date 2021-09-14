#include "minishell.h"

int	ft_exec_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (cmd->cmd && cmd->cmd[i])
	{
		if (ft_strcmp(cmd->cmd[i], "-n") == 0)
		{
			flag = 1;
			if (cmd->cmd[++i] == NULL)
				ft_putstr_fd("", 1);
		}
		while (cmd->cmd[i] != NULL)
		{
			ft_putstr_fd(cmd->cmd[i], 1);
			if (cmd->cmd[++i] != NULL)
				ft_putchar_fd(' ', 1);
		}
	}
	if (flag == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}