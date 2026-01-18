/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_frame_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:07:04 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/17 19:18:56 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static uint64_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
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

static void	check_if_error_occurred(t_app *app)
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
	check_if_error_occurred(app);
	app->last_frame_time = current_time;
	if (all_threads_started_new_frame(app))
		app->start_next_frame = false;
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
	current_time = get_time_ms();
	if (app->show_hud)
		print_hud(app);
	if (all_threads_finished_frame(app))
		display_finished_frame(app);
	if (current_time - app->last_frame_time > TARGET_FRAME_TIME)
		update_state(app, current_time);
}
