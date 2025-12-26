/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:56:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/25 18:33:16 by anpollan         ###   ########.fr       */
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
	printf(" MATERIAL:\n");
	printf(" Ambient:\t%f\n", material.ambient);
	printf(" Diffuse:\t%f\n", material.diffuse);
	printf(" Specular:\t%f\n", material.specular);
	printf(" Shininess:\t%f\n", material.shininess);
	printf(" Reflective:\t%f\n", material.reflective);
	printf(" Transparency:\t%f\n", material.transparency);
	printf(" Refract. idx:\t%f\n", material.refractive_index);
	printf ("\n COLOR:\n");
	printf(" r:\t%f\n g:\t%f\n b:\t%f\n",
			material.color.r, material.color.g, material.color.b);
	printf (" HEX:\t%X\n", color_hex_from_color(material.color));
}

void	print_object(t_object *o)
{
	printf("OBJECT:\n");
	if (o->type == SPHERE)
		printf(" TYPE:\tSphere\n\n");
	else if (o->type == PLANE)
		printf(" TYPE:\tPlane\n\n");
	else if (o->type == CYLINDER)
		printf(" TYPE:\tCylinder\n\n");
	else if (o->type == CUBE)
		printf(" TYPE:\tCube\n\n");
	else
		printf(" TYPE:\tundefined\n\n");
	print_material(o->material);
	printf("\n");
	printf(" TRANSFORM ");
	print_matrix4(o->transform);
	printf("\n");
	printf(" INVERSE TRANSFORM ");
	print_matrix4(o->inverse_transform);
	printf("\n");
	printf(" INVERSE TRANSPOSE ");
	print_matrix4(o->inverse_transpose);
	if (o->type == CYLINDER)
	{
		printf("\n");
		printf(" MINIMUM:\t%lf\n", o->minimum);
		printf(" MINIMUM:\t%lf\n", o->maximum);
		printf("\n");
		if (o->closed)
			printf(" CLOSED:\ttrue\n");
		else
			printf(" CLOSED:\tfalse\n");
	}
	printf("\n");
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
		printf("[%d] ", i);
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
	printf("\n UNDER ");
	print_tuple(comps.under_point);
	printf("\n EYE ");
	print_tuple(comps.eyev);
	printf("\n NORMAL ");
	print_tuple(comps.normalv);
	printf("\n REFLECTV ");
	print_tuple(comps.reflectv);
	printf("\n N1: %f\n", comps.n1);
	printf("\n N2: %f\n", comps.n2);
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

void	print_pattern(t_pattern pattern)
{
	printf("--------------------\n");
	printf("PATTERN:\n");
	printf("\n");
	printf("A ");
	print_color(pattern.a);
	printf("\n");
	printf("B ");
	print_color(pattern.b);
}

void	print_uv_points(t_uv_map uv)
{
	printf("--------------------\n");
	printf("UV POINTS:\n");
	printf("\n");
	printf(" U = %lf\t", uv.u);
	printf(" V = %lf\n", uv.v);
}

void	print_uv_pattern(t_uv_ptrn pattern)
{
	printf("--------------------\n");
	printf("UV PATTERN:\n");
	printf("\n");
	printf("A ");
	print_color(pattern.a);
	printf("\n");
	printf("B ");
	print_color(pattern.b);
	printf("\n");
	printf("Width:\t%lf\n", pattern.width);
	printf("Height:\t%lf\n", pattern.height);
}
