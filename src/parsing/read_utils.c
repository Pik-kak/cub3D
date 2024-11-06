/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:46:39 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/06 15:09:22 by tsaari           ###   ########.fr       */
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

char	*ft_substr_cub(t_data *data, char *s, unsigned int start, size_t len)
{
	char	*ret;
	char	*empty_str;

	if (!s)
		return (0);
	if (len + (size_t)start >= ft_strlen(s))
		len = ft_strlen(s) - start;
	if ((size_t)start >= ft_strlen(s))
	{
		empty_str = ft_strdup("");
		if (!empty_str)
        	return NULL;
		return (empty_str);
	}
	ret = (char *)malloc ((len + 1) * sizeof(char));
	if (!ret)
		return (0);
	s += start;
	len += 1;
	ft_strlcpy(ret, s, len);
	return (ret);
}

static char	*read_file_until_nl(t_data *data, int fd, int br)
{
	char	readed[BUFFER_SIZE + 1];
	char	*temp;

	if (!data->buffer)
		data->buffer = ft_calloc(1, 1);
	if (!data->buffer)
		ft_free_data_and_error(data, "malloc error");
	while (br > 0)
	{
		br = read(fd, readed, BUFFER_SIZE);
		if (br == -1 || (!data->buffer) || (br == 0 && ft_strlen(data->buffer) == 0))
		{
			return (NULL);
		}
		readed[br] = '\0';
		temp = data->buffer;
		data->buffer = ft_strjoin (data->buffer, readed);
		free(temp);
		if (!data->buffer)
		{
			ft_free_data_and_error(data, "malloc error");
			return (NULL);
		}
		if (ft_strchr(data->buffer, '\n'))
			break ;
	}
	return (data->buffer);
}

char	*get_next_line_cub(t_data *data, int fd)
{
	char		*line;
	char		*temp;
	size_t		newline;
	int			br;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	data->buffer = read_file_until_nl(data, fd, 1);
	if (!data->buffer)
	{
		free(data->buffer);
		return (NULL);
	}
	newline = (ft_strchr(data->buffer, '\n') - data->buffer);
	line = ft_substr_cub(data, data->buffer, 0, newline + 1);
	if (!line)
	{
		ft_free(&data->buffer, NULL);
		ft_free_data_and_error(data, ERR_MALLOC);
	}
	temp = data->buffer;
	data->buffer = ft_substr_cub(data, data->buffer, newline + 1, ft_strlen(data->buffer) - newline);
	free(temp);
	if (!temp)
	{
		ft_free(&data->buffer, &line);
		return (NULL);
	}
	return (line);
}
