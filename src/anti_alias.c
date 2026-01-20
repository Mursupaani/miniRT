#include "minirt.h"

static t_ray	ray_for_pixel_aa(t_camera *camera, double px, double py)
{
	double		x;
	double		y;
	double		world_x;
	double		world_y;

	x = px * camera->pixel_size;
	y = py * camera->pixel_size;
	world_x = camera->half_width - x;
	world_y = camera->half_height - y;
	return (calculate_ray(camera, world_x, world_y));
}

static t_color	sample_pixel(t_thread_data *data, double px, double py)
{
	t_ray	ray;

	ray = ray_for_pixel_aa(data->app->scene->camera, px, py);
	return (color_at(data->app->scene, ray, RECURSIONS));
}

static void	accumulate_samples(t_thread_data *data, t_color *acc)
{
	double			sub_px;
	double			sub_py;
	double			grid_size;
	unsigned int	sample_idx;

	grid_size = sqrt(AA_SAMPLES);
	sample_idx = data->y_offset * grid_size + data->x_offset;
	sub_px = (data->x_offset + pseudo_random(data->x, data->y,
				sample_idx * 2)) / grid_size;
	sub_py = (data->y_offset + pseudo_random(data->x, data->y,
				sample_idx * 2 + 1)) / grid_size;
	*acc = color_sum(*acc, sample_pixel(data,
			data->x + sub_px, data->y + sub_py));
}

t_color	get_aa_color(t_thread_data *data)
{
	t_color	accumulated;
	double	grid_size;

	accumulated = color(0, 0, 0);
	grid_size = sqrt(AA_SAMPLES);
	data->y_offset = 0;
	while (data->y_offset < grid_size)
	{
		data->x_offset = 0;
		while (data->x_offset < grid_size)
		{
			accumulate_samples(data, &accumulated);
			data->x_offset++;
		}
		data->y_offset++;
	}
	return (color_multiply(accumulated, 1.0 / AA_SAMPLES));
}
