/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:13:17 by tsaari            #+#    #+#             */
/*   Updated: 2024/09/26 15:14:37 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"



/*int	get_s(int a, int b)
{
	if (a < b)
		return (1);
	else
		return (-1);
}

void	bresenham_line(mlx_image_t *image, t_point s, t_point e, int32_t col)
{
	int	sx;
	int	sy;
	int	e2;

	sx = get_s(s.x, e.x);
	sy = get_s(s.y, e.y);
	while (s.x != e.x || s.y != e.y)
	{
		if (pixel_ok(s.x, s.y) > 0)
			mlx_put_pixel(image, s.x, s.y, col);
		e2 = 2 * s.err;
		if (e2 > -(s.dy))
		{
			s.err -= s.dy;
			s.x += sx;
		}
		if (e2 < s.dx)
		{
			s.err += s.dx;
			s.y += sy;
		}
	}
}
void	set_offset(t_data *map)
{
	t_point	first;
	t_point	last;

	init_points(&first, map->points[0][0], &last, \
	map->points[map->rows - 1][map->cols - 1]);
	first = rotate(first, map);
	last = rotate(last, map);
	map->offset_y = map->origoy - ((first.y + last.y) / 2);
	map->offset_x = map->origox - ((first.x + last.x) / 2);
}

int32_t	get_col(t_point *start, t_point *end, t_data *map)
{
	if (map->col_theme == 1)
	{
		if (end->z >= start->z)
			return (end->col);
		else
			return (start->col);
	}
	else if (map->col_theme == 2)
	{
		if (end->z == 0 && start->z == 0)
			return (COL_LINE2);
		if (end->z < start->z)
			return (start->col2);
		else
			return (end->col2);
	}
	else if (map->col_theme == 3)
		return (COL_BLUE);
	else if (map->col_theme == 4)
		return (COL_SAFFRON);
	else if (map->col_theme == 5)
		return (COL_PINK);
	else
		return (COL_DISCO);
}
*/
