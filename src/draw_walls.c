/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:59:45 by kkauhane          #+#    #+#             */
/*   Updated: 2024/10/16 16:14:35 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void calculate_measurements(t_data *data, int wall_height, int *start, int *end)
{
	*start = -(wall_height / 2) + (data->s_height / 2); // Calculate the starting and ending points of the wall slice
	if (*start < 0)
		*start = 0;
	*end = (wall_height / 2) + (data->s_height / 2);
	if (*end >= data->s_height)
		*end = data->s_height - 1;
}



float calculate_opacity(int ray, int nbr_of_rays, int start, int end)
{
	float distance_from_center;
	float opac;

	distance_from_center = fabs((float)nbr_of_rays / 2 - (float)ray);
	opac = 1 - (distance_from_center / 1000);
	return opac;
}



void draw_walls(t_data *data, int ray, int nbr_of_rays, int wall_height)
{
	int i;
	int start;
	int end;
	float final_opac;

	i = 0;
	calculate_measurements(data, wall_height, &start, &end);
	while (i < data->s_height)
	{
		mlx_put_pixel(data->image, ray, i, COL_BG);
		if (i < start)
		{
			if (pixel_ok(data, ray, i))
				mlx_put_pixel(data->image, ray, i, adjust_opacity(get_colour(data->scene.ceiling_rgb), 0.8));
		}
		else if (i >= start && i <= end)
		{
			final_opac = calculate_opacity(ray, nbr_of_rays, start, end);
			if (pixel_ok(data, ray, i))
				mlx_put_pixel(data->image, ray, i, adjust_opacity(COL_BLUE, final_opac));
		}
		else
			if (pixel_ok(data, ray, i))
				mlx_put_pixel(data->image, ray, i, adjust_opacity(get_colour(data->scene.floor_rgb), 0.8));
		i++;
	}
}




/*

void calculate_measurements(t_data *data, int wall_height, int *start, int *end)
{
	*start = -(wall_height / 2) + (data->s_height / 2); // Calculate the starting and ending points of the wall slice
	if (*start < 0)
		*start = 0;
	*end = (wall_height / 2) + (data->s_height / 2);
	if (*end >= data->s_height)
		*end = data->s_height - 1;
}
float calculate_opacity(int ray, int nbr_of_rays, int i, int start, int end, float distance)
{
	float distance_from_center;
	float opac;
	float vert_opac;
	float shift;

	shift = 0.4f;
	distance_from_center = fabs((float)nbr_of_rays / 2 - (float)ray);
	opac = fmax(0.0f, 1.0f - (distance_from_center / 1000)); // Ensure opacity does not go below 0

	// Limit the maximum opacity based on distance (further away walls have reduced opacity)
	float max_distance = 1000.0f; // Set a maximum distance threshold
	float distance_factor = fmin(distance / max_distance, 1.0f); // Normalize distance to [0, 1]
	vert_opac = 1.0f - (fabs((float)(i - start - (end - start) * shift) / (end - start)) * 0.5);

	// Combine horizontal and vertical opacity
	return opac * vert_opac * (1.0f - distance_factor); // Reduce opacity further with distance
}

float calculate_opacity(int ray, int nbr_of_rays, int i, int start, int end)
{
	float distance_from_center;
	float opac;
	float vert_opac;

	distance_from_center = fabs((float)nbr_of_rays / 2 - (float)ray);
	opac = 1 - (distance_from_center / 1000);
	vert_opac = 1 - (fabs((float)(i - start) / (end - start)) * 0.5);
	return opac * vert_opac;
}

void draw_walls(t_data *data, int ray, int nbr_of_rays, int wall_height, float distance)
{
	int i;
	int start;
	int end;
	float final_opac;

	i = 0;
	
	calculate_measurements(data, wall_height, &start, &end);
	while (i < data->s_height)
	{
		if (i < start)
		{
			if (pixel_ok(data, ray, i))
				mlx_put_pixel(data->image, ray, i, adjust_opacity(get_colour(data->scene.ceiling_rgb), 0.5));
		}
		else if (i >= start && i <= end)
		{
			final_opac = calculate_opacity(ray, nbr_of_rays, i, start, end);
			if (pixel_ok(data, ray, i))
				mlx_put_pixel(data->image, ray, i, adjust_opacity(COL_BLUE, final_opac));
		}
		else
		{
			if (pixel_ok(data, ray, i))
				mlx_put_pixel(data->image, ray, i, adjust_opacity(get_colour(data->scene.floor_rgb), 0.5));
		}
		i++;
	}
}


void	calculate_measurements(t_data *data, int wall_height, int *start, int *end)
{
	*start = -(wall_height / 2) + (data->s_height / 2);// Calculate the starting and ending points of the wall slice
	if (*start < 0)
		*start = 0;
	*end = (wall_height / 2) + (data->s_height/ 2);
	if (*end >= data->s_height)
		*end = data->s_height - 1;
}

float calculate_opacity(int ray, int nbr_of_rays, int i, int start, int end)
{
	float distance_from_center;
	float opac;
	float vert_opac;
	float shift;
	
	shift = 0.4f; 
	distance_from_center = fabs((float)nbr_of_rays / 2 - (float)ray);
	opac = 1 - (distance_from_center / 1000);
	vert_opac = 1 - (fabs((float)(i - start - (end - start) * shift) / (end - start)) * 0.5);
	return opac * vert_opac;
}
=======
//Util function to get color from an image
uint32_t get_image_color(mlx_image_t *image, int tex_x, int tex_y)
{
	int pixel_index = (tex_y * image->width + tex_x) * 4;// Assuming each pixel is 4 bytes (RGBA)

	uint8_t r = image->pixels[pixel_index];	// Get the pixel color (adjust channels if needed)
	uint8_t g = image->pixels[pixel_index + 1];
	uint8_t b = image->pixels[pixel_index + 2];
	uint8_t a = image->pixels[pixel_index + 3];
	return (r << 24 | g << 16 | b << 8 | a);// Combine the color channels into a single 32-bit value
}

void	draw_texture(t_data *data, int ray, int start, int wall_height, mlx_image_t *image, int i)
{
	int tex_y; // Texture Y coordinate
	static double step;
	double tex_pos;

	step = 1.0 * image->height / wall_height;// Calculate the step size for the texture mapping
	tex_pos = (start - data->s_height / 2 + wall_height / 2) * step;// Calculate the initial texture Y coordinate
	tex_y = (int)tex_pos & (image->height - 1); // Clamp tex_y to image height
	tex_pos += step;
	uint32_t color = get_image_color(image, data->tex_x, tex_y);	// Get the color from the image
	if (pixel_ok(data, ray, i))
		mlx_put_pixel(data->image, ray, i, color); // Put the color on screen
}

void draw_walls(t_data *data, int ray, int nbr_of_rays, int wall_height)
{
	int i;
	int start;
	int end;
	float final_opac;

	i = 0;
	calculate_measurements(data, wall_height, &start, &end);
	while (i < data->s_height)
	{
		final_opac = calculate_opacity(ray, nbr_of_rays, i, start, end);
		if (i < start)
		{
			if (pixel_ok(data, ray, i))
				mlx_put_pixel(data->image, ray, i, adjust_opacity(get_colour(data->scene.ceiling_rgb), final_opac));
		}
		else if (i >= start && i <= end)
		{
			//draw_texture(data, ray, start, wall_height, data->walls->no, i);
			if (pixel_ok(data, ray, i))
				mlx_put_pixel(data->image, ray, i, adjust_opacity(COL_BLUE, final_opac));
		}
		else
		{
			if (pixel_ok(data, ray, i))
				mlx_put_pixel(data->image, ray, i, adjust_opacity(get_colour(data->scene.floor_rgb), final_opac));
		}
		i++;
	}
}




void draw_walls(t_data *data, int ray, int nbr_of_rays, int wall_height)
{
	int i;
	int start;
	int end;
	float opac;
	
	opac = 1 - (fabs((float)nbr_of_rays / 2 - (float)ray) / 1000);
	printf("%f\n", opac);
	i = 0;
	calculate_measurements(data, wall_height, &start, &end);
	while (i < data->s_height)
	{
		if (i < start)
		{
			if (pixel_ok(data, ray, i))
				mlx_put_pixel(data->image, ray, i, get_colour(data->scene.ceiling_rgb));
		}
		else if (i >= start && i <= end)
		{
			if (pixel_ok(data, ray, i))
				mlx_put_pixel(data->image, ray, i, adjust_opacity((COL_BLUE), opac));
		}
		else
		{
			if (pixel_ok(data, ray, i))
				mlx_put_pixel(data->image, ray, i, get_colour(data->scene.floor_rgb));
		}
		i++;
	}
}*/

int	cast_rays(t_data *data, mlx_image_t *image)
{
	int		nbr_of_rays;
	double	ray_angle;
	double	angle_step;
	int		i;
	int		dist;
	int		wall_height;

	nbr_of_rays = data->s_width;//Number of rays corresponds to screen width
	angle_step = PI / 3 / nbr_of_rays;//Divide FOV into equal slices for each ray
	i = 0;
	while(i <= (data->s_width))
	{
		ray_angle = normalize_angle(data->scene.player.direction - (PI / 3 / 2) + (i * angle_step));//Calculate ray angle starting from the left-most point of the FOV
		dist = cast_one_ray(data, ray_angle, data->scene.player.px, data->scene.player.py);
		ray_angle = normalize_angle((data->scene.player.direction - ray_angle));//find distance between the player angle and ray angle
		dist = dist*cos(ray_angle);//multiply the ray distance with the cosin of the new angle
		wall_height = (BLOCK_SIZE * data->s_height) / (dist);
		draw_walls(data, i, nbr_of_rays, wall_height);// Draw the wall slice for this ray
		i++;
	}
	return (SUCCESS);
}

