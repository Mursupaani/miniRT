/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_and_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:48:50 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/05 10:27:48 by anpollan         ###   ########.fr       */
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

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	// if (scene->ambient_light)
	// {
	// 	free(scene->ambient_light->color_1);
	// 	free(scene->ambient_light->color_255);
	// }
	// if (scene->light)
	// {
		// free(scene->light->position);
		// free(scene->light->color_1);
		// free(scene->light->color_255);
	// }
	if (scene->camera)
		free(scene->camera);
	free(scene);
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
		free_scene(app->scene);
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
	else if (exit_code == ERROR_SCENE)
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
