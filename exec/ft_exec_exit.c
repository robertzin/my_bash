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
	if (cmd->cmd && cmd->cmd[i] != NULL)
	{
		while (cmd->cmd[j] != NULL)
			j++;
		if (ft_check_arg(cmd->cmd[i]) == 0)
			ft_exit_error(cmd->cmd[i], 1);
		else if (j > 2)
		{
			ft_exit_error(NULL, 2);
			return ;
		}
		exit(ft_atoi(cmd->cmd[i]));
	}
	exit(0);
}
