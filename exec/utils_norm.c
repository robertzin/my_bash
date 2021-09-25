#include "minishell.h"

void	ft_unset_env_norm(t_base *main, int flag)
{
	if (flag == 0)
	{
		free(main->pwd);
		main->pwd = NULL;
	}
	else if (flag == 1)
	{
		free(main->oldpwd);
		main->oldpwd = NULL;
	}
	else if (flag == 2)
	{
		free(main->home);
		main->home = NULL;
	}
	else if (flag == 3)
	{
		ft_doublearray_free(main->path);
		main->path = NULL;
	}
}

int	ft_export_var_norm(t_base *main, t_cmd *cmd, int one_word, int i)
{
	int		is_it;

	is_it = 0;
	if (one_word == 0)
		is_it = ft_change_var(main, cmd->cmd[i]);
	else
		is_it = ft_check_one_word(main, cmd->cmd[i]);
	if (!is_it)
	{
		main->envc = ft_add_var(main->envc, cmd->cmd[i]);
		if (!main->envc)
			return (ft_print_error("add var error", NULL, 1));
	}
	return (0);
}

char	**ft_unset_arg_done_norm(t_base *main, int pos, int *j, int *k)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * (*k));
	if (!new_env)
	{
		ft_print_error("malloc error", NULL, 121);
		return (NULL);
	}
	(*k) = -1;
	while (main->envc[++(*j)] != NULL)
	{
		if ((*j) == pos)
			(*j)++;
		if (main->envc[(*j)] == NULL)
			break ;
		new_env[++(*k)] = ft_strdup(main->envc[(*j)]);
		if (!new_env[(*k)])
		{
			ft_print_error("malloc error", NULL, 121);
			return (NULL);
		}
		if (main->envc[(*j)] == NULL)
			(*j)--;
	}
	return (new_env);
}
