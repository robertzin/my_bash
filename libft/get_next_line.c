/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 09:52:43 by yjama             #+#    #+#             */
/*   Updated: 2021/09/21 14:11:44 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*cleaner(char *need_free, char *reallocate)
{
	char		*new;

	new = ft_strdup(reallocate);
	free(need_free);
	need_free = NULL;
	return (new);
}

char	*remainder_reader(char **remainder, char **n)
{
	char		*ptr_to_n;
	char		*line;

	ptr_to_n = NULL;
	line = ft_line_malloc(0, 0);
	if (*remainder)
	{
		if ((ptr_to_n = ft_strchr(*remainder, '\n')))
		{
			*ptr_to_n = '\0';
			line = cleaner(line, *remainder);
			*remainder = cleaner(*remainder, ++ptr_to_n);
			*n = "Exist";
		}
		else
		{
			line = cleaner(line, *remainder);
			free(*remainder);
			*remainder = NULL;
		}
	}
	return (line);
}

int	reader(int fd, char *buffer, char **line)
{
	size_t			i;
	char			*n;
	static char		*remainder;

	n = NULL;
	*line = remainder_reader(&remainder, &n);
	while (n == NULL && (i = read(fd, buffer, BUFFER_SIZE)) >= 0)
	{
		if (i == 0 && *line[0] != '\0')
		{
			write(1, "  \b\b", 4);
			continue ;
		}
		else if (i == 0 && *line[0] == '\0')
		{
			write(1, "  \b\b", 4);
			return (0);
		}
		buffer[i] = '\0';
		if ((n = ft_strchr(buffer, '\n')) == NULL)
			*line = ft_strjoin_free(*line, buffer);
	}
	return (n == NULL && i == 0 && remainder == NULL) ? 0 : 1;
}

int			get_next_line(int fd, char **line)
{
	char			*buffer;
	int				i;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if ((buffer = ft_line_malloc(BUFFER_SIZE, sizeof(char))) == NULL)
		return (-1);
	i = reader(fd, buffer, line);
	free(buffer);
	buffer = NULL;
	return (i);
}
