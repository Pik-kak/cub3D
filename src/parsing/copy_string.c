/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:40:50 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/18 14:51:01 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*find_substring(t_data *data, char *pointer, char *line)
{
	int		i;
	char	*ret;

	i = 0;
	while (pointer[i] && pointer[i] != ' ' && pointer[i] != '\n')
		i++;
	if (i == 0)
		return (NULL);
	ret = (char *)malloc((i + 1) * sizeof(char));
	if (!ret)
		ft_free_data_and_error(data, "Malloc error", line);
	i = 0;
	while (pointer[i] != ' ' && pointer[i] != '\n' && pointer[i])
	{
		ret[i] = pointer[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

/* ==============================
 *	Mallocs a copy and copies the string until ' ', ' \n'
 * or '\0' and returns the copy
 * if there is content after the path returns error
 * ==============================
 */
char	*copy_str(t_data *data, char *pointer, char *line)
{
	char	*ret;
	char	*temp;

	ret = find_substring(data, pointer, line);
	if (!ret)
		return (NULL);
	temp = pointer;
	temp = skip_spaces(&temp[ft_strlen(ret)]);
	if (*temp != '\n' && *temp != '\0')
	{
		free(ret);
		ft_free_data_and_error(data, "invalid file, extra characters", line);
	}
	return (ret);
}
