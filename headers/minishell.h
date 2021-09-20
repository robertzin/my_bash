/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:28:12 by oharmund          #+#    #+#             */
/*   Updated: 2021/09/19 21:48:20 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <time.h>
# include <term.h>
# include <ctype.h>
# include <limits.h>
# include <signal.h>
#include <errno.h>

int	global_error;

typedef struct s_redir
{
	int		rdir;
	int		doub_rdir;
	int		rev_rdir;
	int		db_rev_rdir;
	char	*filename;
	char	*delimiter;
}				t_redir;

typedef struct s_cmd
{
	int		count;
	char	**cmd;
	t_redir	*rd;
	int		sstdi;
	int		sstdo;
	int		hdoc;
}				t_cmd;

typedef struct s_base
{
	int		err;
	char	**envc;
	char	*str_rl;
	t_cmd	*cmd;
	int		count_cmd;
	int		count_f;
	int		**fd;
	char	*home;
	char	**path;
	char	*pwd;
	char	*oldpwd;
	int		exit;
}				t_base;

void	ft_cleanarr(char **arr);
char	**ft_addarr(char **arr, char *elem);
char	**ft_envcpy(char **envp);
char	*ft_symbol(char *str, char *s, int *i);
char	*ft_slash(char *str, char *s, int *i);
char	*ft_getenv(char *s, char **envp);
char	*ft_dollar(char *str, char *s, int *i, char **envp);
char	*ft_single_quotes(char *str, char *s, int *i);
char	*ft_double_quotes(char *str, char *s, int *i, char **envp);
t_redir	*ft_rdcpy(t_redir *src, t_redir *dst, int count);
void	ft_init_redir(t_redir *rd);
int		ft_memal_redir(t_base *b);
int		ft_filename(char *str, int *i, t_base *b, char **envp);
int		ft_delimiter(char *str, int *i, t_base *b);
int		ft_redir_parse(char *str, int *i, t_base *b, char **envp);
int		ft_init_cmd(t_base *b);
t_cmd	*ft_cmdcpy(t_cmd *src, t_cmd *dst, int count);
void	ft_clean_cmd(t_cmd *cmd, int count);
void	ft_free_struct(t_base *b);
int		ft_memal_cmd(t_base *b);
int		ft_addflags(t_base *b);
int		ft_parser(t_base *b);
int		parser_env(t_base *main);
void	ft_init(t_base *b);
char	**ft_concat(char **arr, char *str);
char	**ft_parse_path(t_base *b);
char	**ft_arr_path_cmd(t_base *b, int num);
char	**ft_path_cmd(t_base *b, int num);
int		ft_exec_cmd(t_base *b, int num);
char	**ft_home_dir(t_base *b, int num);
int		ft_redirect(t_base *b, int num);
int		ft_check_arg(char *str);

void	ft_exec(t_base *b, int num);
void	ft_exec_pwd(void);
void	ft_exec_env(t_base *main);
int		ft_exec_echo(t_cmd *cmd);
void	ft_exec_exit(t_cmd *cmd);
int		ft_exec_cd(t_base *main, t_cmd *cmd);
int		ft_exec_export(t_base *main, t_cmd *cmd);
int		ft_exec_unset(t_base *main, t_cmd *cmd);

void	ft_doublearray_print(char **array);
char	**ft_doublearray_copy(char **array);
void	ft_doublearray_free(char **array);

void	ft_clean_rdstr(t_redir *rd, int i);
int		ft_start_exec(t_base *b);
int		ft_pipe(t_base *b);
void	ft_childproc(t_base *b, int num);
void	ft_inc_shlvl(t_base *b);
void	ft_kill_proc(int *pid, int count);
void	ft_clean_fd(int **fd, int count);
void	ft_close_pipefd(int **fd, int count);
int		ft_memal_fd(t_base *b);
int		ft_pipe_init(t_base *b);
int		ft_repl_fd(t_base *b, int i);
void	ft_close_parent_fd(t_base *b);
int		ft_chaild_proc_pipe(t_base *b);
int		ft_pipe(t_base *b);
int		ft_start_exec(t_base *b);
int		ft_db_rev_rdir(t_base *b, int num);
int		ft_write_heredoc(t_base *b, int num, int i);
int		ft_rev_rdir(t_base *b, int num, int i);
int		ft_doub_rdir(t_base *b, int num, int i);
int		ft_rdir(t_base *b, int num, int i);

void	ignore_squit(int code);
void	ignore_sint(int code);
void	ignore_sint2(int code);
void	ignore_squit2(int code);

void	ft_exit_error(char *minishell, char *args, char *error_str);
int		ft_print_error(char *str, char *cmd, int code);
int		ft_ide_error(char *cmd, char *str);
int		ft_cd_error(char *var, char *str);
int		ft_execve_error(char *str);

#endif
