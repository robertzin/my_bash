#include "minishell.h"

void	ft_exec(t_main *main, t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		ft_exec_echo(cmd);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		ft_exec_pwd();
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		ft_doublearray_print(main->env);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		ft_exec_exit(cmd);
}
