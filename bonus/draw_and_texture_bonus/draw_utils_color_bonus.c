/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_color_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:47:10 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/12 13:50:53 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/*
	Gets color from a certain xy-point of the texture
	Assumes each pixel is 4 bytes (RGBA)
	Combines the color channels into a single 32-bit value
*/
uint32_t	get_img_col(t_data *data, mlx_image_t *image,
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
