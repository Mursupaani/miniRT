/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:29:33 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 20:30:12 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "minirt.h"

static void	free_textures(mlx_texture_t *textures[6])
{
	int	i;

	i = -1;
	while (textures[++i])
	{
		mlx_delete_texture(textures[i]);
		textures[i] = NULL;
	}
}

void	free_object_array(t_object **objs)
{
	int	i;

	if (!objs)
		return ;
	i = -1;
	while (objs[++i])
	{
		if (objs[i]->material.pattern.type == MAP)
			free_textures(objs[i]->material.pattern.uv_pattern.textures);
		if (objs[i]->bump_map.has_bump_map)
			mlx_delete_texture(objs[i]->bump_map.bump_map);
		free(objs[i]);
		objs[i] = NULL;
	}
	free(objs);
	objs = NULL;
}

void	free_world(t_scene *w)
{
	if (!w)
		return ;
	if (w->light)
		free(w->light);
	if (w->objects)
		free_object_array(w->objects);
	if (w->camera)
		free(w->camera);
	free(w);
}

void	free_intersections(t_intersections **xs)
{
	if (xs && *xs)
	{
		if ((*xs)->arr)
			free((*xs)->arr);
		free(*xs);
		*xs = NULL;
	}
}

void	free_app_memory(t_app *app)
{
	if (!app)
		return ;
	join_threads(app->threads, THREADS);
	if (app->img_buffers[0])
		mlx_delete_image(app->mlx, app->img_buffers[0]);
	if (app->img_buffers[1])
		mlx_delete_image(app->mlx, app->img_buffers[1]);
	if (app->hud)
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
