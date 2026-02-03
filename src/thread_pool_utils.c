/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by juhana            #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file thread_pool_utils.c
 * @brief Helper functions for thread pool
 *
 * Exposes:
 * - submit_jobs()
 * - init_workers()
 */

#include "minirt.h"

bool	init_workers(t_thread_pool *pool)
{
	int	i;

	i = 0;
	while (i < pool->num_threads)
	{
		pool->worker_data[i].thread_id = i;
		pool->worker_data[i].pool = pool;
		if (pthread_create(&pool->workers[i], NULL,
				worker_thread, &pool->worker_data[i]) != 0)
			return (false);
		i++;
	}
	return (true);
}

void	submit_jobs(t_thread_pool *pool, int img_height, int chunk_size)
{
	int	row;
	int	end;

	if (!pool || !pool->queue)
		return ;
	row = 0;
	while (row < img_height)
	{
		end = row + chunk_size;
		if (end > img_height)
			end = img_height;
		if (!enque_job(pool->queue, row, end))
			return ;
		row = row + chunk_size;
	}
}

bool	allocate_pool_resources(t_thread_pool *pool)
{
	pool->queue = create_queue();
	if (!pool->queue)
		return (free(pool), false);
	pool->workers = ft_calloc(pool->num_threads, sizeof(pthread_t));
	pool->worker_data = ft_calloc(pool->num_threads, sizeof(t_worker_data));
	if (!pool->workers || !pool->worker_data)
	{
		destroy_queue(pool->queue);
		free(pool->workers);
		free(pool->worker_data);
		free(pool);
		return (false);
	}
	atomic_init(&pool->active_threads, pool->num_threads);
	return (true);
}
