/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:43:28 by pikkak            #+#    #+#             */
/*   Updated: 2024/11/02 15:53:26 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/*
Mallocs a copy and copies the string until ' ', ' \n'
or '\0' and returns the copy
if there is content after the path returns error
*/
char	*copy_str(t_data *data, char *line)
{
	int		i;
	char	*ret;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\n')//while there is content other than ' ', ' \n' or '\0'
		i++;
	if (i == 0)
		return (NULL);
	ret = (char *)malloc((i + 1) * sizeof(char));//mallocs the path string
	if (!ret)
		ft_free_data_and_error(data, ERR_MALLOC);
	i = 0;
	while (line[i] != ' ' && line[i] != '\n' && line[i]) //copies the path
	{
		ret[i] = line[i];
		i++;
	}
	ret[i] = '\0';
	line = skip_spaces(&line[i]);//skips the spaces after the path
	if (*line != '\n' && *line!= '\0')// if there is something else in the end returns 
	{
		free(ret);
		ft_free_data_and_error(data, "element not valid, extra characters");
	}
	return (ret);
}
