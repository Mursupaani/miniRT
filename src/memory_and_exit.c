/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_and_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:48:50 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/06 17:58:59 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_app_memory(t_app *app)
{
	if (!app)
		return ;
	if (app->img)
		mlx_delete_image(app->mlx, app->img);
	if (app->mlx)
		mlx_terminate(app->mlx);
}

void	free_memory_and_exit(t_app *app)
{
	free_app_memory(app);
	exit(EXIT_SUCCESS);
}

void	free_memory_and_error_exit(t_app *app)
{
	ft_fprintf(STDERR_FILENO, "Error\n");
	free_memory_and_exit(app);
}
