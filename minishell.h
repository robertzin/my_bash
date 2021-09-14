#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <dirent.h>
# include <string.h>
# include <time.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>
# include <ctype.h>
# include <limits.h>

# define QUOTES_ERROR 49
# define MALLOC 50
# define EXECVE 51
# define STAT 52
# define STAT_DIR 53
# define CHDIR_ERROR 54
# define HOME_NOT_SET 55
# define PWD_ERROR 56
# define EXPORT_ERROR 57
# define UNSET_ERROR 58
# define OPEN_ERROR 59
# define DUP_ERROR 60
# define PIPE_ERROR 61
# define FORK_ERROR 62
# define SIGNAL_ERROR 63
# define WAIT_ERROR 64
# define LEXER_ERROR 65
# define OLDPWD_NOT_SET 66
# define LEXER_ERROR_FREE 67
# define EXIT_ERROR 68
# define EXIT_ERROR2 69

typedef struct s_cmd
{
	char	**cmd;
	int		pipe;
	char	**red;
}			t_cmd;

typedef struct s_main
{
	char	**env;
	char	*home;
	char	**path;
	char	*pwd;
	char	*oldpwd;
	t_cmd	*cmd;
}			t_main;

int		global_error;

int		ft_skip_spaces(char *str, int *i);
int		ft_if_key(char c);
char	**ft_array_cpy(char **array);
void	parser(t_main *main, char *str, t_cmd *cmd);
int		parser_env(t_main *main);
char	*ft_find_key(t_main *main, char *key);
char	*ft_key_clear(char *str);

void	ft_doublearray_print(char **array);
void	ft_doublearray_free(char **array);
char	**ft_doublearray_copy(char **array);

void	ft_exec(t_main *main, t_cmd *cmd);
void	ft_exec_pwd(void);
void	ft_exec_env(t_main *main);
int		ft_exec_echo(t_cmd *cmd);
void	ft_exec_exit(t_cmd *cmd);
int		ft_exec_cd(t_main *main, t_cmd *cmd);
int		ft_exec_export(t_main *main, t_cmd *cmd);
int		ft_exec_unset(t_main *main, t_cmd *cmd);

int		is_valid(char *str);
char	**ft_stradd(char **array, char *str);
void	ft_shlvl(t_main *main);

#endif
