#include "minishell.h"

int	ft_ide_error(char *cmd, char *str)
{
	g_error = 1;
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": `", 3);
	write(2, str, ft_strlen(str));
	write(2, "\'", 1);
	write(2, ": not a valid identifier", 24);
	ft_putchar_fd('\n', 2);
	return (-1);
}

void	ft_exit_error(char *minishell, char *args, char *error_str)
{
	g_error = 1;
	if (minishell != NULL)
		ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("exit: ", 2);
	if (args != NULL)
		ft_putstr_fd(args, 2);
	ft_putstr_fd(error_str, 2);
	ft_putchar_fd('\n', 2);
}

int	ft_cd_error(char *var, char *str)
{
	char	*err;

	(void)var;
	g_error = 1;
	err = strerror(errno);
	write(2, "minishell: ", 11);
	write(2, "cd: ", 4);
	if (str != NULL)
	{
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	write(2, var, ft_strlen(var));
	write(2, ": ", 2);
	write(2, err, ft_strlen(err));
	ft_putchar_fd('\n', 2);
	return (-1);
}

int	ft_print_error(char *str, char *cmd, int code)
{
	g_error = code;
	write(2, "minishell: ", 11);
	if (cmd != NULL)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 3);
	}
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (-1);
}
