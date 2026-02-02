/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_frame_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:07:04 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/02 21:33:18 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	update_readiness_percent(t_app *app)
{
	double	cur_iter_percent;
	double	iters_ready;
	double	total_iter;

	if (app->current_pixelate_scale == 0)
	{
		app->ready_percent = 100;
		return ;
	}
	cur_iter_percent = (double)app->threads_ready_count / THREADS * 100;
	if (app->pixelate)
	{
		total_iter = log2(PIXELATE_SCALE) + 1;
		iters_ready = total_iter - (log2(app->current_pixelate_scale) + 1);
	}
	else
	{
		total_iter = 1;
		iters_ready = 0;
	}
	app->ready_percent = (((double)iters_ready / total_iter) * 100.0)
		+ (cur_iter_percent / total_iter);
}

static bool	thread_error(t_app *app)
{
	int	i;

	i = -1;
	while (++i < THREADS)
	{
		if (app->threads[i].error)
			return (true);
	}
	return (false);
}

static void	check_for_errors(t_app *app)
{
	if (app->error)
	{
		app->keep_rendering = false;
		exit_and_free_memory(ERROR_UI, app);
	}
	if (app->error || thread_error(app))
	{
		app->keep_rendering = false;
		exit_and_free_memory(ERROR_THREAD_MEMORY, app);
	}
}

static void	update_state(t_app *app, uint64_t current_time)
{
	app->last_frame_time = current_time;
	// if (all_threads_started_new_frame(app))
	// 	app->start_next_frame = false;
	handle_movement(app);
	if (app->right_mouse_down)
		handle_looking_around(app);
	if (app->left_mouse_down)
		move_oject_on_screen(app);
	if (app->data_changed)
	{
		restart_render(app);
		app->data_changed = false;
		app->moving = false;
	}
}

void	per_frame_loop(void *param)
{
	t_app		*app;
	uint64_t	current_time;

	app = (t_app *)param;
	check_for_errors(app);
	current_time = get_time_ms();
	if (all_threads_finished_frame(app))
	{
		display_finished_frame(app);
		app->current_pixelate_scale /= 2;
	}
	update_readiness_percent(app);
	if (app->show_hud)
		print_hud(app);
	if (current_time - app->last_frame_time > TARGET_FRAME_TIME
		|| app->frame_done)
		update_state(app, current_time);
}
