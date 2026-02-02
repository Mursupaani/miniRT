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
	int	i;

	i = -1;
	while (++i < THREADS)
	{
		if (app->threads[i].new_frame_started == false)
		{
			i = -1;
			return (false);
		}
	}
	return (true);
}

bool	all_threads_finished_frame(t_app *app)
{
	int	i;

	i = -1;
	while (++i < THREADS)
	{
		if (app->threads[i].frame_done == false)
		{
			i = -1;
			return (false);
		}
	}
	return (true);
}

void	copy_image_data_to_new_buffer(
		struct mlx_image *from, struct mlx_image *to, size_t img_buffer_size)
{
	ft_memcpy(to->pixels, from->pixels, img_buffer_size);
}

void	empty_image_buffer(struct mlx_image *img, size_t img_buffer_size)
{
	size_t	i;

	i = -1;
	while (++i < img_buffer_size)
		img->pixels[i] = 0;
}

void	display_finished_frame(t_app *app)
{
	app->img_buffers[!app->bg_img_index]->instances->enabled = false;
	app->img_buffers[app->bg_img_index]->instances->enabled = true;
	app->bg_img_index = !app->bg_img_index;
	if (app->moving == false)
		copy_image_data_to_new_buffer(
			app->img, app->img_buffers[app->bg_img_index], app->img_buffer_size);
	app->img = app->img_buffers[app->bg_img_index];
	app->start_next_frame = true;
}
