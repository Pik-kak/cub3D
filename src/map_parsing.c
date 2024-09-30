/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:08:05 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/30 15:26:59 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
}

int	read_file(t_data *data, t_check *check)
{
	char	*line; 

	//while (line)
	//{
		line = get_next_line(data->fd);
		//if (!line)//if no more lines
			//break ;
	//	if (ft_strrchr(line, '\n'))
	//	{
	//		free(line);
	//		continue;
	//	}
		//if (check_line(line) == 1)
		//{
		//	printf("Line not valid\n");//if there is something extra in the scene file
		//	break ;
		//}
		printf("%s\n", line);
	//}
	free(line);
	close(data->fd);
	return (SUCCESS);
}

void	check_file(t_data *data, t_check *check)
{
	read_file(data, check);
//	if (check->player_count != 1)
//		error_scene("Wrong amount of players", scene);
}*/

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

