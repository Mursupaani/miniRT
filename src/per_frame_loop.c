/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_frame_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:07:04 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/02 21:13:33 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	update_readiness_percent(t_app *app)
{
	int	threads_ready_with_current_percent;
	int	iterations_ready;
	int	total_iterations;

	if (app->current_pixelate_scale == 0)
	{
		app->ready_percent = 100;
		return ;
	}
	total_iterations = log2(PIXELATE_SCALE);
	iterations_ready = total_iterations - log2(app->current_pixelate_scale);
	threads_ready_with_current_percent = app->threads_ready_count / THREADS;
	app->ready_percent = iterations_ready / total_iterations
		+ (threads_ready_with_current_percent * (1 / total_iterations));
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
		app->current_pixelate_scale /= 2;
		display_finished_frame(app);
	}
	update_readiness_percent(app);
	if (app->show_hud)
		print_hud(app);
	if (current_time - app->last_frame_time > TARGET_FRAME_TIME
		|| app->frame_done)
		update_state(app, current_time);
}
