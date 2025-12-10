/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_and_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:48:50 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/09 15:32:58 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_scene_objects(t_object *objects[])
{
	int	i;

	if (!objects)
		return ;
	i = -1;
	// while (objects[++i])
	// {
		// free(objects[i]->color_1);
		// free(objects[i]->color_255);
	// }
	free(objects[i]);
}

void	free_world(t_world *w)
{
	int	i;

	if (!w)
		return ;
	if (w->light)
		free(w->light);
	if (w->objects)
	{
		i = -1;
		while (w->objects[++i])
			free(w->objects[i]);
		free(w->objects);
	}
	if (w->camera)
		free(w->camera);
	free(w);
}

void	free_intersections(t_intersections *xs)
{
	if (xs)
	{
		free(xs->xs);
		free(xs);
	}
}

void	free_app_memory(t_app *app)
{
	if (!app)
		return ;
	if (app->img)
		mlx_delete_image(app->mlx, app->img);
	if (app->mlx)
	{
		mlx_close_window(app->mlx);
		mlx_terminate(app->mlx);
	}
	if (app->scene)
		free_world(app->scene);
	if (app->threads)
		free(app->threads);
	free(app);
}

void	exit_and_free_memory(int exit_code, t_app *app)
{
	if (exit_code == ERROR_NO_INPUT_FILE)
		ft_fprintf(STDERR_FILENO, "Error\nPlease pass .rt file as argument.\n");
	else if (exit_code == ERROR_MLX_INIT)
		ft_fprintf(STDERR_FILENO, "Error\nFailed to initialize MLX\n");
	else if (exit_code == ERROR_MLX_IMG_INIT)
		ft_fprintf(STDERR_FILENO, "Error\nFailed to initialize MLX image\n");
	else if (exit_code == ERROR_INVALID_FILE_TYPE)
		ft_fprintf(STDERR_FILENO, "Error\nInvalid filetype\n");
	else if (exit_code == ERROR_OPEN)
		ft_fprintf(STDERR_FILENO, "Error\nCan't open file\n");
	else if (exit_code == ERROR_WORLD)
		ft_fprintf(STDERR_FILENO, "Error\nCan't create scene\n");
	else if (exit_code == ERROR_PARSING)
		ft_fprintf(STDERR_FILENO, "Error\nFailed to parse file contents\n");
	else if (exit_code == ERROR_THREADS)
		ft_fprintf(STDERR_FILENO, "Error\nThread creation failed\n");
	else if (exit_code != 0)
		ft_fprintf(STDERR_FILENO, "Error\n");
	if (app)
		free_app_memory(app);
	exit(exit_code);
}
