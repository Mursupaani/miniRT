/**
 * @file job_queue.c
 * @brief Job queue creation and destruction
 *
 * Exposes:
 * - create_queue()
 * - destroy_queue()
 */

#include "minirt.h"

static bool	init_queue_sync(t_job_queue *queue)
{
	if (pthread_mutex_init(&queue->lock, NULL) != 0)
		return (false);
	if (pthread_cond_init(&queue->work_available, NULL) != 0)
	{
		pthread_mutex_destroy(&queue->lock);
		return (false);
	}
	if (pthread_cond_init(&queue->work_done, NULL) != 0)
	{
		pthread_mutex_destroy(&queue->lock);
		pthread_cond_destroy(&queue->work_available);
		return (false);
	}
	return (true);
}

t_job_queue	*create_queue(void)
{
	t_job_queue	*queue;

	queue = ft_calloc(1, sizeof(t_job_queue));
	if (!queue)
		return (NULL);
	queue->head = NULL;
	queue->tail = NULL;
	atomic_init(&queue->active_jobs, 0);
	atomic_init(&queue->total_jobs, 0);
	atomic_init(&queue->completed_jobs, 0);
	queue->shutdown = false;
	if (!init_queue_sync(queue))
	{
		free(queue);
		return (NULL);
	}
	return (queue);
}

void	destroy_queue(t_job_queue *queue)
{
	t_job	*current;
	t_job	*next;

	if (!queue)
		return ;
	current = queue->head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	pthread_mutex_destroy(&queue->lock);
	pthread_cond_destroy(&queue->work_available);
	pthread_cond_destroy(&queue->work_done);
	free(queue);
}
