/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrifer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:38:46 by sabrifer          #+#    #+#             */
/*   Updated: 2024/07/17 11:49:40 by sabrifer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	store_remainder(char **data_read)
{
	char	*remainder;
	char	*pos_nl;
	int		index_nl;

	if (!*data_read)
		return ;
	pos_nl = ft_strchr(*data_read, '\n');
	if (pos_nl)
	{
		index_nl = pos_nl - *data_read;
		remainder = ft_strdup(*data_read + index_nl + 1);
		free(*data_read);
		*data_read = remainder;
	}
	else
		return ;
}

void	store_line(char *data_read, char **line)
{
	char	*pos_nl;
	int		len;
	int		i;

	if (!data_read)
		return ;
	i = 0;
	pos_nl = ft_strchr(data_read, '\n');
	if (pos_nl)
	{
		len = pos_nl - data_read;
		*line = (char *)malloc(sizeof(char) * len + 2);
		while (i <= len)
		{
			(*line)[i] = data_read[i];
			i++;
		}
		(*line)[i] = '\0';
	}
	else
		return ;
}

void	buffer_management(int fd, char **data_read)
{
	char	*buffer;
	char	*joined_str;
	int		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return ;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return ;
	while (!ft_strchr(*data_read, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		joined_str = ft_strjoin(*data_read, buffer);
		free(*data_read);
		*data_read = joined_str;
	}
	free(buffer);
}

char	*get_next_line(int fd)
{
	static char	*data_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!data_read)
		data_read = ft_strdup("");
	buffer_management(fd, &data_read);
	if (data_read[0] == '\0')
	{
		free(data_read);
		data_read = NULL;
		return (NULL);
	}
	line = NULL;
	store_line(data_read, &line);
	if (line)
		store_remainder(&data_read);
	if (!line && data_read)
	{
		line = ft_strdup(data_read);
		free(data_read);
		data_read = NULL;
	}
	return (line);
}
