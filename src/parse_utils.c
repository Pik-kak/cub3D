/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:28:19 by kkauhane          #+#    #+#             */
/*   Updated: 2024/10/01 16:28:40 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/*
Skips spaces 
*/
char *skip_spaces(char *line)
{
	int		i;
	char	*pointer;

	i  = 0;
	while (line[i] == ' ')
		i++;
	pointer = &line[i];
	return (pointer);
}