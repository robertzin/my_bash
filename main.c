#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_main	main;
	t_cmd	cmd;
	char	*input;

	(void)argc;
	(void)argv;
	global_error = 0;
	ft_bzero(&main, sizeof(t_main));
	main.env = ft_doublearray_copy(envp);
	ft_shlvl(&main);
	cmd.cmd = malloc(sizeof(char *) * 3);
	cmd.cmd[0] = "unset";
	cmd.cmd[1] = "OLDPWD";
	cmd.cmd[2] = NULL;
	ft_exec(&main, &cmd);
	free(cmd.cmd);
	while (1)
	{
		input = readline("minishell$ ");
		// rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		if (input)
		{
			add_history(input);
			parser(&main, input, &cmd);
			parser_env(&main);
			if (cmd.cmd[0] != NULL)
			{
				ft_exec(&main, &cmd);
				free(cmd.cmd);
			}
		}
		else
			break;
	}
	ft_doublearray_free(main.env);
	free(input);
	if (main.cmd)
		ft_doublearray_free(main.cmd->cmd);
	ft_doublearray_free(main.path);
	free(main.home);
	free(main.pwd);
	free(main.oldpwd);
	return (0);
}
