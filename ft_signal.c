#include <minishell.h>

void	ignore_sint(int code)
{
	(void)code;
	global_error = 1;
	write(1, "\n", 1);
	write(1, "minishell$> ", 12);
}

void	ignore_squit(int code)
{
	(void)code;
	write(1, " \b\b \b", 5);
}

void	ignore_sint2(int code)
{
	(void)code;
	global_error = 130;
}

void	ignore_squit2(int code)
{
	(void)code;
	global_error = 131;
}
