/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:03:22 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/13 12:05:45 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_buffer(t_data *data)
{
	data->buffer = ft_calloc(1, 1);
	if (!data->buffer)
		ft_free_data_and_error(data, "malloc error", NULL);
}
