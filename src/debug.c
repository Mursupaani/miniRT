/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:56:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/11/19 15:01:07 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_tuple(t_tuple *tuple)
{
	if (!tuple)
	{
		printf("NULL");
		return ;
	}
	printf("--------------------\n");
	if (tuple->w == 0)
		printf("VECTOR: (%.2f, %.2f, %.2f)\n", tuple->x, tuple->y, tuple->z);
	else
		printf("POINT: (%.2f, %.2f, %.2f)\n", tuple->x, tuple->y, tuple->z);
	printf("x:\t\t%f\n", tuple->x);
	printf("y:\t\t%f\n", tuple->y);
	printf("z:\t\t%f\n", tuple->z);
	if (tuple->w == 0)
	{
		printf("w:\t\t%f\n", tuple->w);
		printf("Magnitude:\t%f\n", vector_magnitude(tuple));
	}
	else
	{
		printf("w:\t\t%f\n", tuple->w);
		printf("Magnitude:\tN/A\n");
	}
	printf("--------------------\n");
}

void	print_matrix4(float (*matrix)[4])
{
	int i = 0;

	printf("--------------------\n");
	printf("MATRIX [4][4]:\n");
	while (i < 4)
	{
		int j = 0;
		while (j < 4)
		{
			printf("%.5f", matrix[i][j]);
			if (j < 3)
				printf(",\t");
			j++;
		}
		printf("\n");
		i++;
	}
	printf("--------------------\n");
}

t_proj	*tick(t_env *env, t_proj *proj)
{
	t_proj	*new_proj;

	new_proj = (t_proj *)malloc(sizeof(t_proj));
	new_proj->p = tuple_sum(proj->p, proj->v);
	new_proj->v = tuple_sum(tuple_sum(proj->v, env->g), env->w);
	return (new_proj);
}

void	projectile(t_app *app)
{
	t_proj	*proj;
	t_env	*env;

	proj = malloc(sizeof(t_proj));
	proj->p = new_point(0, 1, 0);
	proj->v = tuple_scale_multiply(vector_normalize(new_vector(1, 1, 0)), 20);
	env = malloc(sizeof(t_env));
	env->g = new_vector(0, -0.1, 0);
	env->w = new_vector(-0.01, 0, 0);
	while (proj->p->y >= 0)
	{
		proj = tick(env, proj);
		print_tuple(proj->p);
		if (pixel_fits_image(proj->p->x, proj->p->y, app))
			mlx_put_pixel(app->img, proj->p->x, proj->p->y, 0xFF0000FF);
	}
	mlx_image_to_window(app->mlx, app->img, 0, 0);
}
