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
#include <stdbool.h>

static int	init_threads(t_app *app)
{
	int	i;
	int	rows_per_thread;
	
	i = 0;
	app->threads = malloc(sizeof(t_thread_data) * THREADS);
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
		app->threads[i].render_done = false;
		app->threads[i].frame_done = false;
		app->threads[i].new_frame_started = false;
		i++;
	}
	return (0);
}

int	write_pixelated_section(unsigned int *x, unsigned int *y, t_thread_data *data, t_color c)
{
	unsigned int i;
	unsigned int j;
	unsigned int local_x;
	unsigned int local_y;

	local_x = *x;
	local_y = *y;
	i = -1;
	while (++i < data->pixelate_scale && local_y < data->end_row)
	{
		j = -1;
		while (++j < data->pixelate_scale && local_x < data->app->img->width)
			mlx_put_pixel(data->app->img, local_x++, local_y, color_hex_from_color(c));
		local_x -= j;
		local_y++;
	}
	*x += j;
	return (i);
}

void	loop_image_by_pixelation_scale(t_thread_data *data)
{
	// unsigned int	x;
	// unsigned int	y;
	// unsigned int	y_offset;
	// t_ray			ray;
	// t_color			color;

	while (data->y < data->end_row && *data->keep_rendering)
	{
		++data->i;
		data->x = 0;
		data->j = -1;
		while (data->x < data->app->img->width)
		{
			if (data->app->go_wait)
			{
				data->render_done = false;
				return ;
			}
			++data->j;
			if (data->i % 2 == 0 && data->j % 2 == 0 && data->pixelate_scale != PIXELATE_SCALE)
			{
				data->x += data->pixelate_scale;
				continue;
			}
			data->ray = ray_for_pixel(data->app->scene->camera, data->x, data->y);
			data->color = color_at(data->app->scene, data->ray, RECURSIONS);
			data->y_offset = write_pixelated_section(&data->x, &data->y, data, data->color);
		}
		data->y += data->y_offset;
	}
}

void	render_pixelated(t_thread_data *data)
{
	data->pixelate_scale = PIXELATE_SCALE;
	while (data->pixelate_scale > 0 && *data->keep_rendering)
	{
		data->i = -1;
		data->y = data->start_row;
		loop_image_by_pixelation_scale(data);
		data->pixelate_scale /= 2;
		if (data->frame_done == false)
			data->frame_done = true;
		if (data->new_frame_started == true)
			data->new_frame_started = false;
		while (*data->keep_rendering)
		{
			if (*data->start_next_frame || data->app->go_wait)
				break ;
			usleep(10);
		}
		data->frame_done = false;
		data->new_frame_started = true;
	}
}

void	render_full_resolution(t_thread_data *data)
{
	unsigned int	x;
	unsigned int	y;
	t_ray			ray;
	t_color			color;

	y = data->start_row;
	while (y < data->end_row && *data->keep_rendering)
	{
		x = 0;
		while (x < data->app->img->width && *data->keep_rendering)
		{
			if (data->app->go_wait)
			{
				data->render_done = false;
				return ;
			}
			ray = ray_for_pixel(data->app->scene->camera, x, y);
			color = color_at(data->app->scene, ray, RECURSIONS);
			mlx_put_pixel(data->app->img, x, y, color_hex_from_color(color));
			x++;
		}
		y++;
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
		if (data->render_done == false)
			data->render_done = true;
		while (*data->keep_rendering)
		{
			if (data->app->restart_render == true)
				break ;
			usleep(50);
		}
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
