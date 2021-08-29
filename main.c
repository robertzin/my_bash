#include "minishell.h"

char	**ft_doublearray_copy(char **array)
{
	int		i;
	char	**new;

	i = 0;
	if (!array)
		return (NULL);
	while (array[i] != NULL)
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	ft_doublearray_print(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		ft_putstr_fd(array[i], 1);
		ft_putchar_fd('\n', 1);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_main	main;
	t_cmd	cmd;
	char	*input;

	(void)argc;
	(void)argv;
	main.env = ft_doublearray_copy(envp);
	while (1)
	{
		input = readline("minishell$ ");
		// rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		if (input)
		{
			add_history(input);
			parser(input, &cmd);
			ft_exec(&main, &cmd);
		}
		else
			break;
	}
	return (0);
}
