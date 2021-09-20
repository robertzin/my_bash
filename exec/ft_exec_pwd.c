#include "minishell.h"

void	ft_exec_pwd(void)
{
	char	buf[PATH_MAX];

	if (!(getcwd(buf, PATH_MAX)))
		ft_print_error("getcwd error", NULL, 1);
	else
	{
		ft_putstr_fd(buf, 1);
		ft_putchar_fd('\n', 1);
	}
}
