/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:08:05 by kkauhane          #+#    #+#             */
/*   Updated: 2024/10/01 16:38:48 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/*
- Check the file type
- Read the file until you find all the elements before the map.
  If you reach the map(1) and all the elements are not found, or if there are extra elements/map doesnt start with 1 return error.
- Check that the elements are correct (the paths are real paths and the rgb values are between 0-255)
- Read the map, checking that there are no extra symbols and count the size of the map(lengt/width) by finding the longest line.
- Change the spaces to '2's
- Check that the map is surrounded by walls on all sides and if there are spaces around them as well
*/

/*
Help function that calls different checks
*/
void	check_file(t_data *data, t_check *check)
{
	read_file(data, check);
	//check paths
	//check
}

/*
Checks that the file type ends with .cub
*/
int	check_file_type(t_data *data, t_check *check)
{
	char			*file_name;
	char			*file_type;
	unsigned int	i;

	i = 0;
	file_type = ".cub";
	file_name = ft_strrchr(data->file, '.');
	if (!file_name)
		return (ERROR);
	while (file_name[i] != '\0' && file_type[i] == file_name[i])
		i++;
	return (file_name[i] - file_type[i]);
}

/*
void	check_map(t_scene *scene)
{
	int	i;
	int	ii;

	i = 0;
	ii = 0;
	while (scene->map[i] != NULL)
	{
		while (scene->map[i][ii] != '\0')
		{
			if (scene->map[i][ii] == 'N' || scene->map[i][ii] == 'S' 
                 ||scene->map[i][ii] == 'E' || scene->map[i][ii] == 'W')
				scene->player_count++;
			else if (scene->map[i][ii] != '0' && scene->map[i][ii] != '1' && scene->map[i][ii] != ' ')
				error_scene("map not valid", scene);
			ii++;
		}
		i++;
		ii = 0;
	}
}*/
