/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:46:39 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/05 14:41:30 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	ft_free(char **ptr, char **ptr2)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
	if (ptr2 != NULL && *ptr2 != NULL)
	{
		free(*ptr2);
		*ptr2 = NULL;
	}
}

static char	*read_file_until_nl(t_data *data, int fd, char *buffer, int br)
{
	char	readed[BUFFER_SIZE + 1];
	char	*temp;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	if (!buffer)
		ft_free_data_and_error(data, "malloc error");
	while (br > 0)
	{
		br = read(fd, readed, BUFFER_SIZE);
		if (br == -1 || (!buffer) || (br == 0 && ft_strlen(buffer) == 0))
			return (ft_free(&buffer, NULL), NULL);
		readed[br] = '\0';
		temp = buffer;
		buffer = ft_strjoin (buffer, readed);
		ft_free(&temp, NULL);
		if (!buffer)
		{
			ft_free(&buffer, NULL);
			ft_free_data_and_error(data, "malloc error");
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (buffer);
}

char	*get_next_line_cub(t_data *data, int fd)
{
	char		*line;
	static char	*buffer;
	char		*temp;
	size_t		newline;
	int			br;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file_until_nl(data, fd, buffer, 1);
	if (!buffer)
		return (ft_free(&buffer, NULL), NULL);
	newline = (ft_strchr(buffer, '\n') - buffer);
	line = ft_substr(buffer, 0, newline + 1);
	if (!line)
	{
		ft_free(&buffer, &line);
		ft_free_data_and_error(data, "malloc error");
	}
	temp = buffer;
	buffer = ft_substr(buffer, newline + 1, ft_strlen(buffer) - newline);
	free(temp);
	if (!buffer && !line)
		return (ft_free(&buffer, &line), NULL);
	return (line);
}
