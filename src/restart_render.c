/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:39:44 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/08 11:00:16 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	signal_threads_to_go_wait(t_app *app)
{
	app->go_wait = true;
	wait_for_threads_to_be_ready(app);
	app->go_wait = false;
}

// bool	all_threads_ready_for_instructions(t_app *app)
// {
// 	int i;
//
// 	i = -1;
// 	while (++i < THREADS)
// 	{
// 		if (app->threads[i].render_done == false)
// 			return (false);
// 	}
// 	return (true);
// }

void	wait_for_threads_to_be_ready(t_app *app)
{
	int i;

	i = -1;
	while (++i < THREADS)
	{
		if (app->threads[i].render_done == false)
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
		if (app->threads[i].render_done == true)
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
	app->bg_img_index = !app->bg_img_index;
	app->img = app->img_buffers[app->bg_img_index];
	app->restart_render = true;
	wait_for_threads_to_start_render(app);
	app->restart_render = false;
}
