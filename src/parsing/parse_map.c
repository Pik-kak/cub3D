/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:57 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/25 21:48:24 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

//sets player position and direction 
void set_player_position(t_player *player, int dir, int i, int ii)
{
	player->px = ii * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->py = i * BLOCK_SIZE + BLOCK_SIZE / 2;
	if (dir == 'N')
		player->direction = 1.5 * PI;
	if (dir == 'E')
		player->direction = 0;
	if (dir == 'S')
		player->direction = PI / 2;
	if (dir == 'W')
		player->direction = PI;
}

//checks number of players too be 1 

void	check_player(t_data *data)
{
	int	i;
	int	ii;
	int player_found;

	player_found = 0;
	i = 0;
	while (i < data->scene.rows)
	{
		ii = 0;
		while (ii < data->scene.cols)
		{
			if (data->scene.map[i][ii] == 'N' || data->scene.map[i][ii] == 'S' 
                 || data->scene.map[i][ii] == 'E' || data->scene.map[i][ii] == 'W')
			{
				set_player_position(&data->scene.player, data->scene.map[i][ii], i, ii);
				player_found++;
			}
			ii++;
		}
		i++;
	}
	if (player_found != 1)
		ft_free_data_and_error(data, "invalid file, wrong amount of players");
}

//helper function to check that there is no illegal char's in map

int check_map_line(char *line, t_check *check)
{
	int i;

	i = 0;
	if (line[i] != ' ' && line[i] != '1')
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '2' && line[i] != '0' && line[i] != 2 && line[i] != 'N' && line[i] != 'E' && line[i] != 'S' && line[i] != 'W' && line[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

//finds out a number of lines and checks the longest line for allocation

void read_file_for_longest_and_lines(t_data *data, t_check *check)
{
	char	*line;
	char	*temp;
	int		i;
	int		map_found;
	
	i = 0;
	map_found = 0;
	line = NULL;
	while (i < check->cur_file_line)
	{
		line = get_next_line(data->fd);
		if (!line)
			break;
		free(line);
		i++;
	}
	while (1)
	{
		line = get_next_line(data->fd);
		if (!line)
			break;
		if (*line == '\n')
		{
			if (map_found == 1)
			{
				free(line);
				break ;
			}
			check->cur_file_line++;
		}
		else if (check_map_line(line, check) == 0)
		{
			map_found = 1;
			check->map_lines++;	
			if (ft_strlen(line) >= check->longest_line )
			{
				temp = ft_strtrim(line , "\n");
				check->longest_line = ft_strlen(temp);
				free (temp);
			}	
		}
		free(line);
	}
	close(data->fd);
	data->scene.rows = check->map_lines + 10;
	data->scene.cols = check->longest_line + 10;
}

//after checking and etting texttures and colors in parse_textr_col.c this checks that there is no unallowed charachters after that

void check_map_lines(t_data *data, t_check *check)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(data->fd);
		if (!line)
		{
			close(data->fd);
			break;
		}
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		else if (check_map_line(line, check) != 0)
		{
			close(data->fd);
			ft_free_data_and_error(data, "invalid file");
		}
		free(line);
		close(data->fd);
	}
}
