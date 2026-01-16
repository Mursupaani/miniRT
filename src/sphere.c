/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 14:54:04 by anpollan          #+#    #+#             */
/*   Updated: 2026/01/16 20:42:19 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	calculate_coefs(t_ray ray, double *a, double *b, double *c)
{
	t_vector	sphere_to_ray;

	sphere_to_ray = tuple_subtract(ray.origin, point(0, 0, 0));
	*a = dot(ray.direction, ray.direction);
	*b = 2 * dot(ray.direction, sphere_to_ray);
	*c = dot(sphere_to_ray, sphere_to_ray) - 1;
}

t_intersections	*intersect_sphere(t_object *sphere, t_ray local_ray)
{
	double			abc[3];
	double			disc;
	t_intersections	*xs;

	calculate_coefs(local_ray, &abc[0], &abc[1], &abc[2]);
	disc = (abc[1] * abc[1]) - (4 * abc[0] * abc[2]);
	if (disc < 0)
		return (NULL);
	xs = malloc(sizeof(t_intersections));
	if (!xs)
		return (NULL);
	xs->arr = malloc(sizeof(t_intersection) * 2);
	if (!xs->arr)
		return (NULL);
	xs->arr[0] = intersection((-abc[1] - sqrt(disc)) / (2 * abc[0]), sphere);
	xs->arr[1] = intersection((-abc[1] + sqrt(disc)) / (2 * abc[0]), sphere);
	xs->count = 2;
	quick_sort_intersections(xs->arr, 0, xs->count - 1);
	return (xs);
}

t_object	*sphere_new(void)
{
	return (object_new(SPHERE));
}

t_object	*sphere_new_args(t_point center, double diameter, t_color255 color)
{
	t_object	*sphere;

	sphere = ft_calloc(1, sizeof(t_object));
	if (!sphere)
		return (NULL);
	sphere->type = SPHERE;
	sphere->center = center;
	sphere->diameter = diameter;
	sphere->height = diameter;
	sphere->material = material();
	sphere->material.color = color_from_color255(color);
	if (tuples_are_equal(point(0, 0, 0), center))
	{
		sphere->transform = matrix4_identity();
		sphere->inverse_transform = sphere->transform;
		sphere->inverse_transpose = matrix4_transpose(
				sphere->inverse_transform);
	}
	else
		set_transform(
			sphere, translation_matrix4(center.x, center.y, center.z));
	return (sphere);
}
