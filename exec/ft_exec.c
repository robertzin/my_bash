#include "minishell.h"

void	ft_exec(t_base *b, int num)
{
	if (ft_strcmp(b->cmd[num].cmd[0], "echo") == 0)
		ft_exec_echo(&b->cmd[num]);
	else if (ft_strcmp(b->cmd[num].cmd[0], "pwd") == 0)
		ft_exec_pwd();
	else if (ft_strcmp(b->cmd[num].cmd[0], "env") == 0)
		ft_doublearray_print(b->envc);
	else if (ft_strcmp(b->cmd[num].cmd[0], "exit") == 0)
		ft_exec_exit(&b->cmd[num]);
	else if (ft_strcmp(b->cmd[num].cmd[0], "export") == 0)
		ft_exec_export(b, &b->cmd[num]);
	else if (ft_strcmp(b->cmd[num].cmd[0], "cd") == 0)
		ft_exec_cd(b, &b->cmd[num]);
	else if (ft_strcmp(b->cmd[num].cmd[0], "unset") == 0)
		ft_exec_unset(b, &b->cmd[num]);
	else
	{
		if (b->count_f > 0)
			ft_childproc(b, num);
		else
			ft_exec_cmd(b, num);
	}
}
