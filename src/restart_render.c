/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:39:44 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/02 21:16:33 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	wait_for_threads_to_be_ready(t_app *app)
{
	int	i;

	i = -1;
	while (++i < THREADS)
	{
		if (app->threads[i].render_done == false)
		{
			usleep(100);
			i = -1;
		}
	}
}

static void	signal_threads_to_go_wait(t_app *app)
{
	app->go_wait = true;
	wait_for_threads_to_be_ready(app);
	app->go_wait = false;
}

static void	wait_for_threads_to_start_render(t_app *app)
{
	int	i;

	i = -1;
	while (++i < THREADS)
	{
		if (app->threads[i].render_done == true)
		{
			usleep(100);
			i = -1;
		}
	}
}

void	restart_render(t_app *app)
{
	app->restart_render = false;
	signal_threads_to_go_wait(app);
	if (app->go_wait == false)
	{
		app->current_pixelate_scale = PIXELATE_SCALE;
		app->ready_percent = 0;
		app->restart_render = true;
		wait_for_threads_to_start_render(app);
		app->restart_render = false;
	}
}
