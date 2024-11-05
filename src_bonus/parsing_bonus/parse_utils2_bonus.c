/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:41:22 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/05 14:41:25 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/* ==============================
 *	Mallocs a copy and copies the string until ' ', ' \n'
 * or '\0' and returns the copy
 * if there is content after the path returns error
 * ==============================
 */
char	*copy_str(t_data *data, char *line)
{
	int		i;
	char	*ret;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\n')
		i++;
	if (i == 0)
		return (NULL);
	ret = (char *)malloc((i + 1) * sizeof(char));
	if (!ret)
		ft_free_data_and_error(data, ERR_MALLOC);
	i = 0;
	while (line[i] != ' ' && line[i] != '\n' && line[i])
	{
		ret[i] = line[i];
		i++;
	}
	ret[i] = '\0';
	line = skip_spaces(&line[i]);
	if (*line != '\n' && *line != '\0')
	{
		free(ret);
		ft_free_data_and_error(data, "element not valid, extra characters");
	}
	return (ret);
}

/* ==============================
 * Skips the spaces in the beginning.
 * If there is some content, checks if it corresponds
 * with the element identifiers.
 * Sets the variable value if it is valid.
 * ==============================
 */
void	check_valid_color_value(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (ft_isdigit(str[i++]) != 1)
			ft_free_data_and_error(data,
				"invalid file, invalid colour setting");
	}
}

void	check_amount_of_commas(t_data *data, char *str)
{
	int	commas;

	commas = 0;
	while (*str)
	{
		if (*str == ',')
			commas++;
		str++;
	}
	if (commas != 2)
		ft_free_data_and_error(data, "invalid file, invalid colour line");
}
