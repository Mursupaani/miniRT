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
#include "MLX42/MLX42.h"
#include "minirt.h"

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
		if (i == THREADS - 1)
			app->threads[i].end_row = app->monitor_height;
		else
			app->threads[i].end_row = (i + 1) * rows_per_thread;
		i++;
	}
	return (0);
}

static void	render_pixel(t_app *app, int x, int y)
{
	uint32_t	color;

	// TODO
	// t_ray *ray = ray_for_pixel(app->scene->camera, x, y);
	// color = color_at_pixel(app->scene, ray);
	// free_ray(ray);
	color = 0xFFFFFFFF;
	if (pixel_fits_image(x, y, app))
		mlx_put_pixel(app->img, x, y, color);
}

void	*render_routine(void *arg)
{
	t_thread_data	*thread_data;
 	int				x;
	int				y;

 	thread_data = (t_thread_data *)arg;
 	y = thread_data->start_row;
 	while (y < thread_data->end_row)
	{
		x = 0;
		while (x < thread_data->app->monitor_width)
		{
			render_pixel(thread_data->app, x, y);
			x++;
		}
		y++;
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

	i = 0;
	while (i < thread_count)
	{
		pthread_join(thread_data[i].thread_handle, NULL);
		i++;
	}
}
