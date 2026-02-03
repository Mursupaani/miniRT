/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:39:44 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/03 13:11:48 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

	// app->bg_img_index = !app->bg_img_index;
	// app->img = app->img_buffers[app->bg_img_index];

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
//

void	wait_for_threads_to_be_ready(t_app *app)
{
	(void)app;
	// Thread pool model: workers are always ready
}

void	signal_threads_to_go_wait(t_app *app)
{
	app->go_wait = true;
	wait_for_threads_to_be_ready(app);
	app->go_wait = false;
}

void	wait_for_threads_to_start_render(t_app *app)
{
	(void)app;
	// Thread pool model: render is triggered on demand
}

void	restart_render(t_app *app)
{
	if (!app || !app->pool)
		return ;
	signal_threads_to_go_wait(app);
	app->start_next_frame = true;
}
