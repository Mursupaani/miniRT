/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:44:06 by anpollan          #+#    #+#             */
/*   Updated: 2026/02/03 13:04:27 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file render_routine.c
 * @brief This file handles thread pool initialization and rendering
 *
 * Exposes:
 * - launch_render()
 * - join_threads() (deprecated, kept for compatibility)
 *
 */
#include "minirt.h"

void	launch_render(t_app *app)
{
	app->pool = create_pool(app, THREADS);
	if (!app->pool)
		exit_and_free_memory(ERROR_THREADS, app);
}

void	join_threads(t_thread_data *thread_data, int thread_count)
{
	int	i;

	if (!thread_data)
		return ;
	i = 0;
	while (i < thread_count)
	{
		pthread_join(thread_data[i].thread_handle, NULL);
		i++;
	}
}
