/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by juhana            #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file thread_pool.c
 * @brief Thread pool implementation for job processing
 *
 * Exposes:
 * - create_pool()
 * - destroy_pool()
 * - submit_jobs()
 */

#include "minirt.h"

static void	render_worker_chunk(t_worker_data *data,
			unsigned int start, unsigned int end)
{
	if (atomic_load(&data->pool->app->pixelate))
		render_pixelated_range(data->pool->app, start, end);
	else
		render_job_range(data->pool->app, start, end);
}

static void	process_work_chunks(t_worker_data *data, int height)
{
	int	start;
	int	end;

	while (1)
	{
		start = atomic_fetch_add(&data->pool->next_row,
				data->pool->chunk_size);
		if (start >= height)
			break ;
		end = start + data->pool->chunk_size;
		if (end > height)
			end = height;
		render_worker_chunk(data, start, end);
	}
}

static void	*worker_thread_impl(void *arg)
{
	t_worker_data	*data;
	int				height;

	data = (t_worker_data *)arg;
	while (atomic_load(&data->pool->app->keep_rendering))
	{
		atomic_fetch_add(&data->pool->render_in_progress, 1);
		height = data->pool->app->img->height;
		process_work_chunks(data, height);
		atomic_fetch_sub(&data->pool->render_in_progress, 1);
		while (atomic_load(&data->pool->app->keep_rendering)
			&& !data->pool->app->go_wait
			&& !data->pool->app->start_next_frame)
			usleep(100);
		atomic_store(&data->pool->next_row, 0);
	}
	return (NULL);
}

void	*worker_thread(void *arg)
{
	return (worker_thread_impl(arg));
}

t_thread_pool	*create_pool(t_app *app, int num_threads)
{
	t_thread_pool	*pool;

	pool = ft_calloc(1, sizeof(t_thread_pool));
	if (!pool)
		return (NULL);
	pool->num_threads = num_threads;
	pool->app = app;
	pool->chunk_size = 8;
	atomic_store(&pool->next_row, 0);
	atomic_store(&pool->render_in_progress, 0);
	if (!allocate_pool_resources(pool))
		return (NULL);
	if (!init_workers(pool))
		return (destroy_pool(pool), NULL);
	return (pool);
}

static void	join_all_workers(t_thread_pool *pool)
{
	int	i;

	i = 0;
	while (i < pool->num_threads)
	{
		pthread_join(pool->workers[i], NULL);
		i++;
	}
}

void	destroy_pool(t_thread_pool *pool)
{
	if (!pool)
		return ;
	if (pool->queue)
	{
		pthread_mutex_lock(&pool->queue->lock);
		pool->queue->shutdown = true;
		pthread_cond_broadcast(&pool->queue->work_available);
		pthread_mutex_unlock(&pool->queue->lock);
	}
	if (pool->workers)
	{
		join_all_workers(pool);
		free(pool->workers);
	}
	destroy_queue(pool->queue);
	free(pool->worker_data);
	free(pool);
}
