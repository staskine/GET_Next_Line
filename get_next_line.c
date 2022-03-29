/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staskine <staskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:42:10 by staskine          #+#    #+#             */
/*   Updated: 2022/03/03 12:26:23 by staskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	get_result(const int fd, char **string, char **line)
{
	int		index;
	char	*tmp;

	index = 0;
	if (string[fd][0] == '\0')
		return (0);
	while (string[fd][index] != '\n' && string[fd][index] != '\0')
		index++;
	if (string[fd][index] == '\0')
	{
		*line = ft_strdup(string[fd]);
		ft_strdel(&string[fd]);
		return (1);
	}
	else
	{
		*line = ft_strsub(string[fd], 0, index);
		tmp = ft_strdup(string[fd]);
		ft_strdel(&string[fd]);
		string[fd] = ft_strsub(tmp, (index + 1), (ft_strlen(tmp) - index - 1));
		ft_strdel(&tmp);
		return (1);
	}
}

static int	check_result(int ret, const int fd, char **string, char **line)
{
	if (ret < 0)
		return (-1);
	if (string[fd] == NULL)
		return (0);
	else
		return (get_result(fd, string, line));
}

static int	strcompile(char **string, char *buf, int fd)
{
	char	*temp;

	if (string[fd] == NULL)
	{
		string[fd] = ft_strdup(buf);
		if (string[fd] == NULL)
			return (1);
	}
	else
	{
		temp = ft_strjoin(string[fd], buf);
		if (temp == NULL)
			return (1);
		ft_strdel(&string[fd]);
		string[fd] = ft_strdup(temp);
		ft_strdel(&temp);
	}
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	static char	*string[FD_SIZE];
	char		buf[BUFF_SIZE + 1];
	int			ret;

	if (fd < 0 || line == NULL || fd > FD_SIZE)
		return (-1);
	ret = read(fd, buf, BUFF_SIZE);
	if (ret < 0)
		return (-1);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if ((strcompile(string, buf, fd)) == 1)
			return (-1);
		if (ft_strchr(string[fd], '\n'))
			break ;
		ret = read(fd, buf, BUFF_SIZE);
	}
	return (check_result(ret, fd, string, line));
}
