#include <minishell.h>

void	ignore_sint(int code)
{
	(void)code;
	g_error = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ignore_sint2(int code)
{
	(void)code;
	g_error = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}
