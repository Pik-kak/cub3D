/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_color_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:38:44 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/05 14:38:50 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/*
	Gets color from a certain xy-point of the texture
	Assumes each pixel is 4 bytes (RGBA)
	Combines the color channels into a single 32-bit value
*/
uint32_t	get_image_color(t_data *data, mlx_image_t *image,
							int tex_x, int tex_y)
{
	int		pixel_index;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	tex_x = tex_x % image->width;
	tex_y = tex_y % image->height;
	pixel_index = (tex_y * image->width + tex_x) * 4;
	r = image->pixels[pixel_index];
	g = image->pixels[pixel_index + 1];
	b = image->pixels[pixel_index + 2];
	a = image->pixels[pixel_index + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

int	adjust_opacity(int color, float opacity)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	if (opacity > 1.0)
		opacity = 1.0;
	else if (opacity < 0.0)
		opacity = 0.0;
	red = (color >> 24) & 0xFF;
	green = (color >> 16) & 0xFF;
	blue = (color >> 8) & 0xFF;
	alpha = (int)((color & 0xFF) * opacity);
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}

/* ==============================
 * Gets the colours from the map element 
 * ==============================
 */
uint32_t	get_colour(int rgb[3])
{
	uint32_t	colour;
	uint32_t	a;

	a = 255;
	colour = (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | a);
	return (colour);
}

/*=======================
 * Adjusts brightness
 * ======================
 */
uint32_t	darken_color(uint32_t color, double factor)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	r = (uint8_t)(r * factor);
	g = (uint8_t)(g * factor);
	b = (uint8_t)(b * factor);
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}
