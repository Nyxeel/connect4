/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:13:32 by netrunner         #+#    #+#             */
/*   Updated: 2026/02/11 19:38:37 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

bool	ft_init(int fd, int *j, char **line)
{
	*j = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (false);
	*line = ft_calloc(10000, 1);
	if (!(*line))
		return (false);
	return (true);
}

char	*ft_return(int j, int *i, int *bytes, char **line)
{
	if (j)
	{
		(*line)[j] = '\0';
		return (*line);
	}
	else
	{
		free(*line);
		*line = NULL;
		*i = 0;
		*bytes = 0;
		return (NULL);
	}
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	static int	i = 0;
	static int	bytes = 0;
	char		*line;
	int			j;

	if (!ft_init(fd, &j, &line))
		return (NULL);
	while (1)
	{
		if (i >= bytes)
		{
			i = 0;
			bytes = read(fd, buf, BUFFER_SIZE);
			if (bytes < 0)
				return (free(line), NULL);
			if (bytes == 0)
				break ;

		}
		line[j++] = buf[i++];
		if (j >= 9999)
			return (free(line), NULL);
		if (line[j - 1] == '\n')
			break ;
	}
	return (ft_return(j, &i, &bytes, &line));
}
