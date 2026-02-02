/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:44:06 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/02 13:36:46 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file render_routine.c
 * @brief This file handles thread creation and rendering the image
 *
 * Exposes:
 * - render_routine()
 * - launch_render()
 * - join_threads()
 *
 */
#include "minirt.h"

static int	init_threads(t_app *app)
{
	int	i;
	int	rows_per_thread;

	i = 0;
	app->threads = ft_calloc(1, sizeof(t_thread_data) * THREADS);
	if (!app->threads)
		return (1);
	rows_per_thread = app->scrn_h / THREADS;
	while (i < THREADS)
	{
		app->threads[i].id = i;
		app->threads[i].start_row = i * rows_per_thread;
		app->threads[i].app = app;
		app->threads[i].keep_rendering = &app->keep_rendering;
		app->threads[i].start_next_frame = &app->start_next_frame;
		if (i == THREADS - 1)
			app->threads[i].end_row = app->scrn_h;
		else
			app->threads[i].end_row = (i + 1) * rows_per_thread;
		app->threads[i].pixelate_scale = PIXELATE_SCALE;
		i++;
	}
	return (0);
}

void	render_full_resolution(t_thread_data *data)
{
	t_color	color;

	data->y = data->start_row;
	while (data->y < data->end_row && *data->keep_rendering)
	{
		data->x = 0;
		while (data->x < data->app->img->width && *data->keep_rendering)
		{
			if (data->app->go_wait)
			{
				data->render_done = false;
				return ;
			}
			color = get_aa_color(data);
			if (data->error)
				return ;
			mlx_put_pixel(
				data->app->img, data->x, data->y, color_hex_from_color(color));
			data->x++;
		}
		data->y++;
	}
	if (data->frame_done == false)
		data->frame_done = true;
}

void	*render_routine(void *arg)
{
	t_thread_data	*data;

	data = (t_thread_data *)arg;
	while (*data->keep_rendering)
	{
		if (data->app->pixelate)
			render_pixelated(data);
		else
			render_full_resolution(data);
		if (data->error)
			return (NULL);
		if (data->render_done == false)
			data->render_done = true;
		while (*data->keep_rendering)
		{
			if (data->app->restart_render == true)
				break ;
			usleep(50);
		}
		data->frame_done = false;
		data->render_done = false;
	}
	return (NULL);
}

void	launch_render(t_app *app)
{
	int	i;

	if (init_threads(app) != 0)
		exit_and_free_memory(ERROR_THREADS, app);
	i = 0;
	while (i < THREADS)
	{
		if (pthread_create(&app->threads[i].thread_handle, NULL, render_routine,
				&app->threads[i]) != 0)
		{
			join_threads(app->threads, i);
			exit_and_free_memory(ERROR_THREADS, app);
		}
		i++;
	}
}

void	join_threads(t_thread_data *thread_data, int thread_count)
{
	int	i;

	if (!thread_data)
		return ;
	i = 0;
	while (i < thread_count)
	{
		pthread_join(thread_data[i].thread_handle, NULL);
		i++;
	}
}
