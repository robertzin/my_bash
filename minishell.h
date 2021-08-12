#ifndef MINISHELL_H
# define MINISHELL_H
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


char *ft_strjoin(char *s1, char *s2);
char *ft_substr(char *s, unsigned int start, size_t len);
int	ft_strlen(char *str);

#endif