#include <minishell.h>

void	ignore_sint(int code)
{
	(void)code;
	global_error = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ignore_sint2(int code)
{
	(void)code;
	global_error = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	ignore_squit2(int code)
{
	(void)code;
	global_error = 131;
	write(1, "Quit: 3", 7);
	write(1, "\n", 1);
}
