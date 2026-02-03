/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_with_pool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by juhana            #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file render_with_pool.c
 * @brief Submits rendering jobs to thread pool
 *
 * Exposes:
 * - render_with_pool()
 */

#include "minirt.h"

void	render_with_pool(t_app *app, int chunk_size)
{
	if (!app || !app->pool)
		return ;
	submit_jobs(app->pool, app->scrn_h, chunk_size);
	wait_completion(app->pool->queue);
}
