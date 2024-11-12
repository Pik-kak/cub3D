/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:03:22 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/08 14:05:15 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_buffer(t_data *data)
{
	data->buffer = ft_calloc(1, 1);
	if (!data->buffer)
		ft_free_data_and_error(data, "malloc error", NULL);
}
