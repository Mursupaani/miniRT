/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_finished_frame.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:59:42 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/02 21:18:08 by anpollan         ###   ########.fr       */
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
	app->threads_ready_count = 0;
	app->frame_done = true;
	while (++i < THREADS)
	{
		if (app->threads[i].frame_done == false)
			app->frame_done = false;
		else
			app->threads_ready_count++;
	}
	return (app->frame_done);
}

void	display_finished_frame(t_app *app)
{
	app->img_buffers[!app->bg_img_index]->instances->enabled = false;
	app->img_buffers[app->bg_img_index]->instances->enabled = true;
	app->bg_img_index = !app->bg_img_index;
	if (app->moving == false)
		ft_memcpy(
			app->img_buffers[app->bg_img_index]->pixels,
			app->img->pixels,
			app->img_buffer_size);
	app->img = app->img_buffers[app->bg_img_index];
}
