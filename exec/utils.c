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

void	ft_doublearray_free(char **array)
{
	int		i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
		{
			if (array[i])
				free(array[i]);
			i++;
		}
		free(array);
	}
}

int ft_unset_oldpwd(t_base *b)
{
	t_cmd	cmd;

	(void)b;
	cmd.cmd = malloc(sizeof(char *) * 3);
	if (!cmd.cmd)
		return (ft_print_error("malloc error", NULL, 121));
	cmd.cmd[0] = "unset";
	cmd.cmd[1] = "OLDPWD";
	cmd.cmd[2] = NULL;
	ft_exec_unset(b, &cmd);
	free(cmd.cmd);
	return (0);
}