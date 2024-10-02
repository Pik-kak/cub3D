/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:57:40 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/02 17:01:23 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"


int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		ft_error(ERR_ARG);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_error(ERR_MALLOC);
	else
	{
		init_data(data, argv);
		data->m = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
		if (!data->m)
			ft_free_data_and_error(data, ERR_MLX);
		init_window(data);
		mlx_loop_hook(data->m, my_keyhook, data);
		mlx_loop(data->m);
		mlx_terminate(data->m);
	}
	ft_free_data_and_exit(data);
}
