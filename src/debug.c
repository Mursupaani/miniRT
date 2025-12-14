/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:56:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/11 14:45:05 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_tuple(t_tuple tuple)
{
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
		printf(" %f\n", tuple.w);
		printf(" Magnitude:\t %f\n", vector_magnitude(tuple));
	}
	else
	{
		printf(" w:\t\t");
		if (tuple.z >= 0)
			printf(" ");
		printf("%f\n", tuple.w);
		printf(" Magnitude:\t N/A\n");
	}
}

void	print_ray(t_ray r)
{
	printf("RAY:\n");
	printf(" ORIGIN ");
	print_tuple(r.origin);
	printf("\n");
	printf(" DIRECTION ");
	print_tuple(r.direction);
}

void	print_matrix4(t_matrix4 matrix)
{
	int i = 0;

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
}

void	print_matrix2(t_matrix2 matrix)
{
	int i = 0;

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
}

void	print_matrix3(t_matrix3 matrix)
{
	int i = 0;

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
}

void	print_color(t_color color)
{
	printf("COLOR:\n");
	printf(" r:\t%f\n g:\t%f\n b:\t%f\n",
			color.r, color.g, color.b);
	printf (" HEX:\t%X\n", color_hex_from_color(color));
}

void	print_color_255(t_color255 color)
{
	printf("COLOR255:\n");
	printf(" r:\t%d\n g:\t%d\n b:\t%d\n",
			color.r, color.g, color.b);
	printf (" HEX:\t%X\n", color_hex_from_color255(color));
}

void	print_point_light(t_light *point_light)
{
	printf("POINT LIGHT:\n\n");
	printf("POSITION ");
	print_tuple(point_light->position);
	printf("\n");
	printf("INTENSITY ");
	print_color(point_light->intensity);
}

void	print_material(t_material material)
{
	printf("MATERIAL:\n\n");
	printf(" Ambient:\t%f\n", material.ambient);
	printf(" Diffuse:\t%f\n", material.diffuse);
	printf(" Specular:\t%f\n", material.specular);
	printf(" Shininess:\t%f\n", material.shininess);
	printf ("\n\nCOLOR:\n\n");
	printf(" r:\t%f\n g:\t%f\n b:\t%f\n",
			material.color.r, material.color.g, material.color.b);
	printf ("\nHEX:\t%X\n", color_hex_from_color(material.color));
}

void	print_object(t_object *o)
{
	printf("OBJECT:\n");
	if (o->type == SPHERE)
		printf(" Type:\tSphere\n");
	else if (o->type == PLANE)
		printf(" Type:\tPlane\n");
	else if (o->type == CYLINDER)
		printf(" Type:\tCylinder\n");
	else
		printf(" Type:\tundefined\n");
	printf(" MATERIAL:\n");
	printf("  Ambient:\t%f\n", o->material.ambient);
	printf("  Diffuse:\t%f\n", o->material.diffuse);
	printf("  Specular:\t%f\n", o->material.specular);
	printf("  Shininess:\t%f\n", o->material.shininess);
	printf ("\n  COLOR:\n");
	printf("   r:\t%f\n   g:\t%f\n   b:\t%f\n",
			o->material.color.r, o->material.color.g, o->material.color.b);
	printf ("   HEX:\t%X\n", color_hex_from_color(o->material.color));
	printf("\n");
	printf(" TRANSFORM ");
	print_matrix4(o->transform);
}

void	print_world(t_world *world)
{
	int	i;
	printf("--------------------\n");
	if (world->light)
		print_point_light(world->light);
	i = -1;
	while (world->objects[++i])
	{
		printf("--------------------\n");
		printf("%d ", i);
		print_object(world->objects[i]);
		printf("--------------------\n");
	}
}

void	print_intersections(t_intersections *xs)
{
	if (!xs)
		return ;
	int	i;
	printf("--------------------\n");
	printf("INTERSECTIONS:\n");
	printf(" Count: %d\n", xs->count);
	if (xs->arr)
	{
		i = -1;
		while (++i < xs->count)
		{
			printf("--------------------\n");
			printf("Intersection %d:\n", i);
			printf("t = %f\n",xs->arr[i].t);
			print_object(xs->arr[i].object);
			printf("--------------------\n");
		}
	}
}

void	print_computations(t_computations comps)
{
	printf("--------------------\n");
	printf("COMPUTATIONS:\n\n");
	printf(" ");
	print_tuple(comps.point);
	printf("\n OVER ");
	print_tuple(comps.over_point);
	printf("\n EYE ");
	print_tuple(comps.eyev);
	printf("\n NORMAL ");
	print_tuple(comps.normalv);
	printf("\n INSIDE: ");
	if (comps.inside)
		printf("true\n");
	else
		printf("false\n");
	printf("--------------------\n");
}

void	print_camera(t_camera *camera)
{
	printf("--------------------\n");
	printf("CAMERA:\n");
	printf(" Horizontal size:\t%d\n", camera->hsize);
	printf(" Vertical size:\t\t%d\n", camera->vsize);
	printf(" Field of view:\t\t%f\n", camera->fov);
	printf("\n");
	printf(" TRANSFORMATION ");
	print_matrix4(camera->transform);
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
	proj.v = tuple_scale_multiply(normalize(vector(1, 1, 0)), 20);
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
