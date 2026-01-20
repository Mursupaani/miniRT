/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:44:06 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/17 16:31:17 by anpollan         ###   ########.fr       */
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
	rows_per_thread = app->monitor_height / THREADS;
	while (i < THREADS)
	{
		app->threads[i].id = i;
		app->threads[i].start_row = i * rows_per_thread;
		app->threads[i].app = app;
		app->threads[i].keep_rendering = &app->keep_rendering;
		app->threads[i].start_next_frame = &app->start_next_frame;
		if (i == THREADS - 1)
			app->threads[i].end_row = app->monitor_height;
		else
			app->threads[i].end_row = (i + 1) * rows_per_thread;
		app->threads[i].pixelate_scale = PIXELATE_SCALE;
		i++;
	}
	return (0);
}

void	render_full_resolution(t_thread_data *data)
{
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
			ray = ray_for_pixel(data->app->scene->camera, x, y);
			color = color_at(data->app->scene, ray, RECURSIONS, &data->error);
			if (data->error)
				return ;
			mlx_put_pixel(data->app->img, x, y, color_hex_from_color(color));
			x++;
		}
		data->y++;
	}
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
