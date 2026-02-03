/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_finished_frame.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:59:42 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/17 19:19:47 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	all_threads_started_new_frame(t_app *app)
{
	if (!app->pool)
		return (true);
	return (atomic_load(&app->pool->render_in_progress) > 0);
}

bool	all_threads_finished_frame(t_app *app)
{
	if (!app->pool)
		return (false);
	return (atomic_load(&app->pool->render_in_progress) == 0
		&& atomic_load(&app->pool->next_row) >= (int)app->img->height);
}

void	copy_image_data_to_new_buffer(
		struct mlx_image *from, struct mlx_image *to, size_t pixel_count)
{
	size_t	i;

	i = -1;
	while (++i < pixel_count)
		to->pixels[i] = from->pixels[i];
}

void	empty_image_buffer(struct mlx_image *img, size_t pixel_count)
{
	size_t	i;

	i = -1;
	while (++i < pixel_count)
		img->pixels[i] = 0;
}

void	display_finished_frame(t_app *app)
{
	app->img_buffers[!app->bg_img_index]->instances->enabled = false;
	app->img_buffers[app->bg_img_index]->instances->enabled = true;
	app->bg_img_index = !app->bg_img_index;
	if (app->moving == false)
		copy_image_data_to_new_buffer(
			app->img, app->img_buffers[app->bg_img_index], app->pixel_count);
	app->img = app->img_buffers[app->bg_img_index];
	app->start_next_frame = true;
}
