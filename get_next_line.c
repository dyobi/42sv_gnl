/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilkim <kilkim@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:02:30 by kilkim            #+#    #+#             */
/*   Updated: 2020/04/16 17:02:31 by kilkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_read(int fd, char **res)
{
	char	buff[BUFF_SIZE + 1];
	char	*tmp;
	int		count;

	if (read(fd, buff, 0) < 0)
		return (-1);
	while ((count = read(fd, buff, BUFF_SIZE)))
	{
		buff[count] = '\0';
		if (!*res)
			*res = ft_strdup(buff);
		else
		{
			tmp = *res;
			*res = ft_strjoin(*res, buff);
			free(tmp);
		}
		if (ft_strchr(*res, '\n'))
			break ;
	}
	return (count);
}

int		get_next_line(int fd, char **line)
{
	static char	**res = NULL;
	int			count;
	int			index;

	index = 0;
	res = !res ? (char **)malloc(sizeof(char *) * 1024) : res;
	if (fd < 0 || !line || (count = get_read(fd, &res[fd - 3])) < 0)
		return (-1);
	while (res[fd - 3][index] && res[fd - 3][index] != '\n')
		index++;
	*line = ft_strncpy(ft_strnew(index), res[fd - 3], index);
	if (*res[fd - 3] || (**line && *line))
	{
		res[fd - 3] = ft_strcut(res[fd - 3], '\n');
		return (1);
	}
	return (count);
}
