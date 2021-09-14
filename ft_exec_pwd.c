#include "minishell.h"

void	ft_exec_pwd(void)
{
	char	buf[PATH_MAX];

	if (!(getcwd(buf, PATH_MAX)))
	{
		global_error = 1;
		ft_putendl_fd("getcwd error", 2);
	}
	else
	{
		ft_putstr_fd(buf, 1);
		ft_putchar_fd('\n', 1);
	}
}
