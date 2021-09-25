#include "minishell.h"

int	ft_check_arg(char *str)
{
	int		i;

	i = 0;
	while (str[i] != 0)
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_exec_exit(t_cmd *cmd)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	ft_putendl_fd("exit", 1);
	if (cmd->cmd && cmd->cmd[i] != NULL)
	{
		while (cmd->cmd[j] != NULL)
			j++;
		if (ft_check_arg(cmd->cmd[i]) == 0)
		{
			ft_exit_error(NULL, cmd->cmd[i], ": numeric argument required");
			exit(255);
		}
		else if (j > 2)
		{
			ft_exit_error("minishell", NULL, "too many arguments");
			return ;
		}
		exit(ft_atoi(cmd->cmd[i]));
	}
	exit(0);
}
