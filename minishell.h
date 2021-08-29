#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <time.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>
# include <ctype.h>
# include <limits.h>

typedef struct s_main
{
	char	**env;
	char	*home;
	char	**path;
	char	*pwd;
	char	*oldpwd;
}			t_main;

typedef struct s_cmd
{
	char	**cmd;
	int		pipe;
	char	**red;
}			t_cmd;

char	**ft_array_cpy(char **array);
int		ft_skip_spaces(char *str, int *i);
int		ft_if_key(char c);
void	parser(char *str, t_cmd *cmd);
void	ft_doublearray_print(char **array);
void	ft_doublearray_free(char **array);
char	**ft_doublearray_copy(char **array);



void	ft_exec(t_main *main, t_cmd *cmd);
int		ft_exec_cd(t_main *main, t_cmd *cmd);
void	ft_exec_pwd(void);
void	ft_exec_env(t_main *main);
void	ft_exec_echo(t_cmd *cmd);
void	ft_exec_exit(t_cmd *cmd);
int		ft_exec_export(t_main *main, t_cmd *cmd);



#endif
