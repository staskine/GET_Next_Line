/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staskine <staskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:42:10 by staskine          #+#    #+#             */
/*   Updated: 2022/03/01 14:42:19 by staskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	get_result(const int fd, char **string, char **line)
{
	int		index;
	char	*temp;

	index = 0;
	if (string[fd][0] == '\0')
		return (0);
	while (string[fd][index]!= '\n' && string[fd][index] != '\0')
		index++;
	//printf("%d, index", index);
	if (string[fd][index] == '\0')
	{
		*line = ft_strdup(string[fd]);
		free(string[fd]);
		return (0);
	}
	else
	{
		*line = ft_strsub(string[fd], 0, index);
		temp = ft_strdup(string[fd]);
		free(string[fd]);
		string[fd] = ft_strsub(temp, (index + 1), (ft_strlen(temp) - index));
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

int	get_next_line(const int fd, char **line)
{
	static char	*string[FD_SIZE];
	char		buf[BUFF_SIZE + 1];
	char		*temp;
	int			ret;

	if (fd < 0 || line == NULL || fd > FD_SIZE)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[BUFF_SIZE] = '\0';
		//printf("%s, buf\n", buf);
		if (string[fd] == NULL)
		{
			string[fd] = ft_strdup(buf);
			if (string[fd] == NULL)
				return (-1);
			//printf("%s, first if\n", string[fd]);
		}
		else
		{
			temp = ft_strjoin(string[fd], buf);
			if (temp == NULL)
				return (-1);
			string[fd] = ft_strdup(temp);
			free(temp);
			//printf("%s, string[fd] joining\n", string[fd]);
		}
		if (ft_strchr(string[fd], '\n'))
			break;
	}
	//printf("%d", ret);
	return (check_result(ret, fd, string, line));
}