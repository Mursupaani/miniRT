/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by juhana            #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file render_job.c
 * @brief Renders a chunk of the image for thread pool jobs
 *
 * Exposes:
 * - render_job_range()
 */

#include "minirt.h"

static t_color	get_pixel_color(t_app *app, unsigned int x, unsigned int y,
					atomic_int *error)
{
	t_thread_data	data;
	t_color			color;

	data.app = app;
	data.x = x;
	data.y = y;
	data.error = 0;
	color = get_aa_color(&data);
	atomic_store(error, atomic_load(&data.error));
	return (color);
}

static void	render_single_row(t_app *app, unsigned int y, atomic_int *error)
{
	unsigned int	x;
	t_color			color;

	x = 0;
	while (x < app->img->width && atomic_load(&app->keep_rendering))
	{
		color = get_pixel_color(app, x, y, error);
		if (atomic_load(error))
			return ;
		mlx_put_pixel(app->img, x, y, color_hex_from_color(color));
		x++;
	}
}

void	render_job_range(t_app *app, unsigned int start_row,
			unsigned int end_row)
{
	unsigned int	y;
	atomic_int		error;

	if (!app || !app->img)
		return ;
	atomic_init(&error, 0);
	y = start_row;
	while (y < end_row && atomic_load(&app->keep_rendering))
	{
		render_single_row(app, y, &error);
		if (atomic_load(&error))
			return ;
		y++;
	}
}
