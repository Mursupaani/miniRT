/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:56:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/05 17:17:05 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_tuple(t_tuple tuple)
{
	printf("--------------------\n");
	if (tuple.w == 0)
		printf("VECTOR: (%.2f, %.2f, %.2f)\n", tuple.x, tuple.y, tuple.z);
	else
		printf("POINT: (%.2f, %.2f, %.2f)\n", tuple.x, tuple.y, tuple.z);
	printf(" x:\t\t");
	if (tuple.x >= 0)
		printf(" ");
	printf("%f\n", tuple.x);
	printf(" y:\t\t");
	if (tuple.y >= 0)
		printf(" ");
	printf("%f\n", tuple.y);
	printf(" z:\t\t");
	if (tuple.z >= 0)
		printf(" ");
	printf("%f\n", tuple.z);
	if (tuple.w == 0)
	{
		printf(" w:\t\t");
		printf("%f\n", tuple.w);
		printf(" Magnitude:\t %f\n", vector_magnitude(tuple));
	}
	else
	{
		printf(" w:\t\t");
		if (tuple.z >= 0)
			printf(" ");
		printf("%f\n", tuple.w);
		printf(" Magnitude:\tN/A\n");
	}
	printf("--------------------\n");
}

void	print_matrix4(t_matrix4 matrix)
{
	int i = 0;

	printf("--------------------\n");
	printf("MATRIX [4][4]:\n");
	while (i < 4)
	{
		printf(" ");
		int j = 0;
		while (j < 4)
		{
			if (matrix.data[i][j] >= 0)
				printf(" ");
			printf("%.5f", matrix.data[i][j]);
			if (j < 3)
				printf(",\t");
			j++;
		}
		printf("\n");
		i++;
	}
	printf("--------------------\n");
}

void	print_matrix2(t_matrix2 matrix)
{
	int i = 0;

	printf("--------------------\n");
	printf("MATRIX [2][2]:\n");
	while (i < 2)
	{
		int j = 0;
		while (j < 2)
		{
			printf("%.5f", matrix.data[i][j]);
			if (j < 1)
				printf(",\t");
			j++;
		}
		printf("\n");
		i++;
	}
	printf("--------------------\n");
}

void	print_matrix3(t_matrix3 matrix)
{
	int i = 0;

	printf("--------------------\n");
	printf("MATRIX [3][3]:\n");
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			printf("%.5f", matrix.data[i][j]);
			if (j < 2)
				printf(",\t");
			j++;
		}
		printf("\n");
		i++;
	}
	printf("--------------------\n");
}

void	print_color(t_color color)
{
	printf("--------------------\n");
	printf("COLOR:\n");
	printf(" r:\t%f\n g:\t%f\n b:\t%f\n",
			color.r, color.g, color.b);
	printf (" HEX:\t%X\n", color_hex_from_color(color));
	printf("--------------------\n");
}

void	print_color_255(t_color255 color)
{
	printf("--------------------\n");
	printf("COLOR255:\n");
	printf(" r:\t%d\n g:\t%d\n b:\t%d\n",
			color.r, color.g, color.b);
	printf (" HEX:\t%X\n", color_hex_from_color255(color));
	printf("--------------------\n");
}

void	print_point_light(t_light *point_light)
{
	printf("--------------------\n");
	printf("POINT LIGHT:\n");
	printf(" Position:\n");
	print_tuple(point_light->position);
	printf(" Intensity:\n");
	print_color(point_light->intensity);
	printf("--------------------\n");
}

void	print_material(t_material material)
{
	printf("--------------------\n");
	printf("MATERIAL:\n");
	printf(" Ambient:\t%f\n", material.ambient);
	printf(" Diffuse:\t%f\n", material.diffuse);
	printf(" Specular:\t%f\n", material.specular);
	printf(" Shininess:\t%f\n", material.shininess);
	printf ("\n COLOR:\n");
	printf("  r:\t%f\n  g:\t%f\n  b:\t%f\n",
			material.color.r, material.color.g, material.color.b);
	printf ("  HEX:\t%X\n", color_hex_from_color(material.color));
	printf("--------------------\n");
}

t_proj	tick(t_env env, t_proj proj)
{
	t_proj	new_proj;

	new_proj.p = tuple_sum(proj.p, proj.v);
	new_proj.v = tuple_sum(tuple_sum(proj.v, env.g), env.w);
	return (new_proj);
}

void	projectile(t_app *app)
{
	t_proj	proj;
	t_env	env;

	proj.p = point(0, 1, 0);
	proj.v = tuple_scale_multiply(vector_normalize(vector(1, 1, 0)), 20);
	env.g = vector(0, -0.1, 0);
	env.w = vector(-0.01, 0, 0);
	while (proj.p.y >= 0)
	{
		proj = tick(env, proj);
		print_tuple(proj.p);
		if (pixel_fits_image(proj.p.x, proj.p.y, app))
			mlx_put_pixel(app->img, proj.p.x, proj.p.y, 0xFF0000FF);
	}
	mlx_image_to_window(app->mlx, app->img, 0, 0);
}
