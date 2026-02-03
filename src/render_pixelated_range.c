/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixelated_range.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by juhana            #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file render_pixelated_range.c
 * @brief Renders pixelated preview for a chunk of rows
 *
 * Exposes:
 * - render_pixelated_range()
 */

#include "minirt.h"

static void	write_pixel_block(t_app *app, unsigned int x, unsigned int y,
				t_color c, unsigned int scale)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < scale && y + i < app->img->height)
	{
		j = 0;
		while (j < scale && x + j < app->img->width)
		{
			mlx_put_pixel(app->img, x + j, y + i, color_hex_from_color(c));
			j++;
		}
		i++;
	}
}

static t_color	get_pixelated_color(t_app *app, unsigned int x,
				unsigned int y)
{
	t_thread_data	data;
	t_ray			ray;
	t_color			color;

	data.app = app;
	data.x = x;
	data.y = y;
	data.error = 0;
	ray = ray_for_pixel(app->scene->camera, x, y);
	color = color_at(app->scene, ray, RECURSIONS, &data.error);
	return (color);
}

void	render_pixelated_range(t_app *app, unsigned int start_row,
			unsigned int end_row)
{
	unsigned int	y;
	unsigned int	x;
	unsigned int	scale;
	t_color			color;

	scale = PIXELATE_SCALE;
	y = start_row;
	while (y < end_row && atomic_load(&app->keep_rendering))
	{
		x = 0;
		while (x < app->img->width)
		{
			if (app->go_wait)
				return ;
			color = get_pixelated_color(app, x, y);
			write_pixel_block(app, x, y, color, scale);
			x += scale;
		}
		y += scale;
	}
}
