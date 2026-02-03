/**
 * @file job_queue_utils.c
 * @brief Job queue utility functions
 *
 * Exposes:
 * - enque_job()
 * - deque_job()
 * - job_completed()
 * - wait_completion()
 */

#include "minirt.h"

static t_job	*create_job(unsigned int start, unsigned int end)
{
	t_job	*job;

	job = malloc(sizeof(t_job));
	if (!job)
		return (NULL);
	job->start_row = start;
	job->end_row = end;
	job->next = NULL;
	return (job);
}

bool	enque_job(t_job_queue *queue, unsigned int start, unsigned int end)
{
	t_job	*job;

	if (!queue)
		return (false);
	job = create_job(start, end);
	if (!job)
		return (false);
	pthread_mutex_lock(&queue->lock);
	if (queue->tail)
		queue->tail->next = job;
	else
		queue->head = job;
	queue->tail = job;
	atomic_fetch_add(&queue->total_jobs, 1);
	pthread_cond_signal(&queue->work_available);
	pthread_mutex_unlock(&queue->lock);
	return (true);
}

t_job	*deque_job(t_job_queue *queue)
{
	t_job	*job;

	if (!queue)
		return (NULL);
	pthread_mutex_lock(&queue->lock);
	while (!queue->head && !queue->shutdown)
		pthread_cond_wait(&queue->work_available, &queue->lock);
	if (queue->shutdown)
	{
		pthread_mutex_unlock(&queue->lock);
		return (NULL);
	}
	job = queue->head;
	queue->head = job->next;
	if (!queue->head)
		queue->tail = NULL;
	atomic_fetch_add(&queue->active_jobs, 1);
	pthread_mutex_unlock(&queue->lock);
	return (job);
}

void	job_completed(t_job_queue *queue)
{
	int	completed;
	int	total;

	if (!queue)
		return ;
	atomic_fetch_sub(&queue->active_jobs, 1);
	atomic_fetch_add(&queue->completed_jobs, 1);
	pthread_mutex_lock(&queue->lock);
	completed = atomic_load(&queue->completed_jobs);
	total = atomic_load(&queue->total_jobs);
	if (completed >= total)
		pthread_cond_broadcast(&queue->work_done);
	pthread_mutex_unlock(&queue->lock);
}

void	wait_completion(t_job_queue *queue)
{
	int	completed;
	int	total;

	if (!queue)
		return ;
	pthread_mutex_lock(&queue->lock);
	completed = atomic_load(&queue->completed_jobs);
	total = atomic_load(&queue->total_jobs);
	while (completed < total)
	{
		pthread_cond_wait(&queue->work_done, &queue->lock);
		completed = atomic_load(&queue->completed_jobs);
		total = atomic_load(&queue->total_jobs);
	}
	pthread_mutex_unlock(&queue->lock);
}
