/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:39:44 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/05 17:25:13 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "minirt.h"

void	signal_threads_to_go_wait(t_app *app)
{
	app->go_wait = true;
	wait_for_threads_to_be_ready(app);
	app->go_wait = false;
}

void	wait_for_threads_to_be_ready(t_app *app)
{
	int i;

	i = -1;
	while (++i < THREADS)
	{
		if (app->threads[i].ready_for_instuctions == false)
		{
			i = -1;
			continue; ;
		}
	}
}

void	wait_for_threads_to_start_render(t_app *app)
{
	int i;

	i = -1;
	while (++i < THREADS)
	{
		if (app->threads[i].ready_for_instuctions == true)
		{
			i = -1;
			continue; ;
		}
	}
}

void	restart_render(t_app *app)
{
	app->restart_render = false;
	signal_threads_to_go_wait(app);
	app->temp_img_index = !app->temp_img_index;
	app->img = app->temp_img[app->temp_img_index];
	mlx_image_to_window(app->mlx, app->img, 0, 0);
	app->restart_render = true;
	wait_for_threads_to_start_render(app);
	app->restart_render = false;
}
