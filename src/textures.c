/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:48:31 by kkauhane          #+#    #+#             */
/*   Updated: 2024/10/10 15:50:11 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*void	get_textures(t_data *data)
{
	data->textrs = ft_calloc(1, sizeof(struct s_textures));
	data->textrs->floor = mlx_load_png("./textures/grass.png");
	data->textrs->wall = mlx_load_png("./textures/hedge.png");
	data->textrs->collec = mlx_load_png("./textures/mushrooms.png");
	data->textrs->player = mlx_load_png("./textures/pippin.png");
	data->textrs->exit = mlx_load_png("./textures/hole.png");
}

void	get_images(t_data *data)
{
	data->imag = ft_calloc(1, sizeof(t_images));
	data->imag->floor = mlx_texture_to_image(data->mlx, data->textrs->floor);
	data->imag->wall = mlx_texture_to_image(data->mlx, data->textrs->wall);
	data->imag->collec = mlx_texture_to_image(data->mlx, data->textrs->collec);
	data->imag->player = mlx_texture_to_image(data->mlx, data->textrs->player);
	data->imag->exit = mlx_texture_to_image(data->mlx, data->textrs->exit);
	mlx_delete_texture(data->textrs->floor);
	mlx_delete_texture(data->textrs->wall);
	mlx_delete_texture(data->textrs->collec);
	mlx_delete_texture(data->textrs->player);
	mlx_delete_texture(data->textrs->exit);
}*/