/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:43:28 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/13 12:04:57 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* ==============================
 * Skips the spaces in the beginning.
 * If there is some content, checks if it corresponds
 * with the element identifiers.
 * Sets the variable value if it is valid.
 * ==============================
 */
void	check_valid_color_value(t_data *data, char *str, char *line)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (ft_isdigit(str[i++]) != 1)
		{
			free(line);
			ft_free_data_and_error(data,
				"invalid file, invalid colour setting", str);
		}
	}
}

void	check_amount_of_commas(t_data *data, char *str, char *line)
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
	{
		free(line);
		ft_free_data_and_error(data, "invalid file, invalid colour line", str);
	}
}

//sets player position and dir 
static void	set_player_position(t_player *player, int dir, int i, int ii)
{
	player->px = ii * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->py = i * BLOCK_SIZE + BLOCK_SIZE / 2;
	if (dir == 'N')
		player->dir = 1.5 * PI;
	if (dir == 'E')
		player->dir = 0;
	if (dir == 'S')
		player->dir = PI / 2;
	if (dir == 'W')
		player->dir = PI;
}

//checks number of players too be 1 
void	check_player(t_data *data)
{
	int	i;
	int	ii;
	int	player_found;

	player_found = 0;
	i = 0;
	while (i < data->scene.rows)
	{
		ii = 0;
		while (ii < data->scene.cols)
		{
			if (data->scene.map[i][ii] == 'N' || data->scene.map[i][ii] == 'S'
				|| data->scene.map[i][ii] == 'E'
					|| data->scene.map[i][ii] == 'W')
			{
				set_player_position(&data->scene.player,
					data->scene.map[i][ii], i, ii);
				player_found++;
			}
			ii++;
		}
		i++;
	}
	if (player_found != 1)
		ft_free_data_and_error(data, "invalid file, too many players", NULL);
}
