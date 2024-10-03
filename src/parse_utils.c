/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:28:19 by kkauhane          #+#    #+#             */
/*   Updated: 2024/10/02 11:03:25 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/*
rgb to hexadecimal 
*/


unsigned int rgb_to_hex(int r, int g, int b, int alpha)
{
	return (alpha << 24) | (r << 16) | (g << 8) | b;
}


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