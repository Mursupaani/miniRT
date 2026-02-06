/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixelated.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:29:31 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/17 16:31:05 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	write_pixelated_section(t_thread_data *data, t_color c)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	local_x;
	uint32_t	local_y;

	local_x = data->x;
	local_y = data->y;
	i = -1;
	while (++i < data->pixelate_scale && local_y < data->end_row)
	{
		j = -1;
		while (++j < data->pixelate_scale && local_x < data->app->img->width)
			mlx_put_pixel(
				data->app->img, local_x++, local_y, color_hex_from_color(c));
		local_x -= j;
		local_y++;
	}
	data->x += j;
	data->y_offset = i;
}

static void	loop_image_by_pixelation_scale(t_thread_data *data, t_camera *c)
{
	while (data->y < data->end_row && *data->keep_rendering)
	{
		++data->i;
		data->x = 0;
		data->j = -1;
		while (data->x < data->app->img->width)
		{
			if (data->app->go_wait)
				return ;
			++data->j;
			if (data->i % 2 == 0 && data->j % 2 == 0
				&& data->pixelate_scale != PIXELATE_SCALE)
			{
				data->x += data->pixelate_scale;
				continue ;
			}
			data->ray = ray_for_pixel(c, data->x, data->y);
			data->color = color_at(
					data->app->scene, data->ray, RECURSIONS, &data->error);
			if (data->error)
				return ;
			write_pixelated_section(data, data->color);
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
		loop_image_by_pixelation_scale(data, data->app->scene->camera);
		data->pixelate_scale /= 2;
		if (data->frame_done == false)
			data->frame_done = true;
		if (data->new_frame_started == true)
			data->new_frame_started = false;
		while (*data->keep_rendering)
		{
			if ((unsigned int)*data->current_pixelate_scale == data->pixelate_scale)
				break ;
			if (data->app->go_wait)
			{
				data->frame_done = false;
				return ;
			}
			usleep(10);
		}
		data->frame_done = false;
		data->new_frame_started = true;
	}
}
