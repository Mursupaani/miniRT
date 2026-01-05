/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:39:44 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/05 15:49:09 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	signal_threads_to_go_wait(t_app *app)
{
	app->go_back = true;
	wait_for_threads_to_be_ready(app);
	app->go_back = false;
}

void	wait_for_threads_to_be_ready(t_app *app)
{
	int i;

	i = -1;
	while (++i < THREADS)
	{
		if (app->threads[i].ready == false)
		{
			i = -1;
			continue; ;
		}
	}
}

void	restart_render(t_app *app)
{
	app->restart_render = true;
	signal_threads_to_go_wait(app);
	app->restart_render = false;
}
